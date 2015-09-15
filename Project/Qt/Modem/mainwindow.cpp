#include <QDebug>
#include <QTimer>
#include <QString>
#include <QChar>
#include <QByteArray>
#include <QTextCursor>
#include <QColor>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "unicodetoascii.h"
#include "serialdialog.h"
#include "dtmf.h"
#include "buffer.h"
#include "atmodem.h"
#include "statemachine.h"
#include "stackenum.h"
#include "eeprom.h"
#include "copy.h"

bool MainWindow::CallReady = false;
bool MainWindow::TimeReady = false;

char MainWindow::chTextSendAfterEvent[ 129 ] = { "\0" };
const char MainWindow::kSendSpacer[] = { " \0" };
const char MainWindow::kReceiveMainReset[] = { "reset\0" };
const char MainWindow::kReceiveMainEnable[] = { "+ligar tudo\0" };
const char MainWindow::kReceiveMainDisable[] = { "+desligar tudo\0" };
const char MainWindow::kReceiveRootNumberEnable[] = { "+root: habilitar\0" };
const char MainWindow::kReceiveRootNumberDisable[] = { "+root: desabilitar\0" };
const char MainWindow::kReceiveSetRtc[] = { "+ajustar: rtc\0" };
// 0 - id, 1 - telefone, 2 - pessoa
const char MainWindow::kReceiveRootNumberAddPhoneBook[] = { "+numero: {num} {snum} {str}\0" };
// 0 - id
const char MainWindow::kReceiveRootNumberDelPhoneBook[] = { "-numero: {num}\0" };
// 0 - telefone
// O texto "Root Number" deve ser idêntico ao texto contido em  MainWindow::kRootName
const char  MainWindow::kSendSetRootPhoneBook[] = { "AT+CPBW=250,\"{pt}\",129,\"Root Number\"\r\n\0" };
const char  MainWindow::kSendClearRootPhoneBook[] = { "AT+CPBW=250,\"000000000\",129,\"\"\r\n\0" };

char MainWindow::chMemoria[];
char MainWindow::chRele[];
char MainWindow::chTimeOn[];
char MainWindow::chTimerOff[];
char MainWindow::chSemana[];
// 0 - memoria, 1 - rele, 2 - timer on, 3 - timer off, 4 - dias da semana
const char MainWindow::kReceiveAddTimer[] = { "+timer: {num} {num} {time} {time} {num}\0" };
const char MainWindow::kReceiveReadTimer[] = { "+ler timer: {num}\0" };
const char MainWindow::kReceiveMakeTimerOn[] = { "+ligar timer: {num}\0" };
const char MainWindow::kReceiveMakeTimerOff[] = { "+desligar timer: {num}\0" };
//const char MainWindow::kReceiveDelTimer[] = { "-timer: {num}\0" };
//const char MainWindow::kReceiveEnableTimer[] = { "+habilitar: {num}\0" };
const char MainWindow::kSendPhoneBookAddEvent[] = { "telefone adicionado\0" };
const char MainWindow::kSendResetEvent[] = { "todos os timers apagados\0" };

const char  MainWindow::kRootName[] = { "Root Number\0" };
const char * MainWindow::pRootName = & MainWindow::kRootName[ 0 ];

const char MainWindow::kSendSignalEvent[] = { "Sinal: \0" };
const char MainWindow::kSendSignalOtimoEvent[] = { "otimo.\0" };
const char MainWindow::kSendSignalBomEvent[] = { "bom.\0" };
const char MainWindow::kSendSignalRuimEvent[] = { "ruim.\0" };
const char MainWindow::kSendRtcSetToEvent[] = { "rtc ajustado para: \0" };
const char MainWindow::kSendPhoneBookFind[] = { "responder\0" };
const char MainWindow::kSendTimerSetEvent[] = { "timer adicionado: \0" };
const char MainWindow::kSendTimerReadEvent[] = { "timer: \0" };
const char MainWindow::kSendTimerReadUserEnabledEvent[] = { "hu \0" };
const char MainWindow::kSendTimerReadGeneralEnabledEvent[] = { "hg \0" };
const char MainWindow::kSendEnableMainSetEvent[] = { "todos os timers habilitados\0" };
const char MainWindow::kSendEnableMainClearEvent[] = { "todos os timers desabilitados\0" };
const char MainWindow::kSendResetEepromEvent[] = { "memoria limpa\0" };

const char MainWindow::kSendTimerMakeOnEvent[]    = { "timer habilitado.\0" };
const char MainWindow::kSendTimerMakeOffEvent[]   = { "timer desabilitado\0" };
const char MainWindow::kSendTimerMakeErrorEvent[] = { "este timer nao existe.\0" };
//const char *MainWindow::pSendMsg[ 4 ];

void MainWindow::PhoneBookAddById ()
{
  AtModem::pDataList[ 0 ] = &MainWindow::Id[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::Phone[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::User[ 0 ];
  AtModem::PhoneBookIdSet ();
}

void MainWindow::SetRootPhoneBook ()
{
  AtModem::pDataTxToModem[ 0 ] = &MainWindow::kSendSetRootPhoneBook[ 0 ];
  AtModem::pDataRxToModem[ 0 ] = '\0';

  AtModem::pDataTxToModem[ 1 ] = '\0';
  AtModem::pDataRxToModem[ 1 ] = '\0';

  AtModem::StateMachineResetAndRun ();
}

void MainWindow::ClearRootPhoneBook ()
{
  AtModem::pDataTxToModem[ 0 ] = &MainWindow::kSendClearRootPhoneBook[ 0 ];
  AtModem::pDataRxToModem[ 0 ] = '\0';

  AtModem::pDataTxToModem[ 1 ] = '\0';
  AtModem::pDataRxToModem[ 1 ] = '\0';

  AtModem::StateMachineResetAndRun ();
}

void MainWindow::PhoneBookFindToSendEvent ()
{
  AtModem::ConstCharToChar ( MainWindow::kSendPhoneBookFind, &MainWindow::SmsUser[ 0 ] );

  AtModem::pDataList[ 0 ] = &MainWindow::SmsUser[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::SmsTelefon[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::SmsUser[ 0 ];
  AtModem::PhoneBookFind ();
}

void MainWindow::SmsSendAfterEvent ()
{
  AtModem::pDataList[ 0 ] = &MainWindow::SmsTelefon[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::chTextSendAfterEvent[ 0 ];
  AtModem::SmsSend();
}


void MainWindow::RtcSet ()
{
  MainWindow::chTextSendAfterEvent[ 0 ] = '\0';
  Copy::Spacer( &MainWindow::kSendSpacer[ 0 ] );
  Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendRtcSetToEvent[ 0 ], &MainWindow::SmsDate[ 0 ], &MainWindow::SmsTime[ 0 ], &MainWindow::TimeZone[ 0 ] );

  AtModem::pDataList[ 0 ] = &MainWindow::SmsDate[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::SmsTime[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::TimeZone[ 0 ];
  AtModem::RtcSet ();
}

void MainWindow::ResetPointers ()
{
  AtModem::ResetPointers ();
  StateMachine::Step();
}


















SerialDialog *gSD;
Dtmf *gDt;

eColor MainWindow::CorAtual = Color::Preto;

char MainWindow::Debug[] = { '\0' };
int MainWindow::DebugDataPointer = 0;
bool MainWindow::DebugInProcess = false;

char MainWindow::Id[];
char MainWindow::IdAdd[];
char MainWindow::Clock[];
char MainWindow::Day[];
char MainWindow::User[];
char MainWindow::UserAdd[];
char MainWindow::Phone[];
char MainWindow::PhoneAdd[];
char MainWindow::Qualidade[];
char MainWindow::Status[];
char MainWindow::Text[];
char MainWindow::Telefone[];
char MainWindow::TimeZone[];

char MainWindow::CallNumber[];
char MainWindow::SinPin[];
char MainWindow::SinNewPin[];
char MainWindow::Host[];
char MainWindow::Site[];
char MainWindow::Port[];
char MainWindow::Query[];
char MainWindow::IdConnect[];
char MainWindow::IdPassword[];
char MainWindow::UserPassword[];
char MainWindow::UserName[];
char MainWindow::SmsText[];
char MainWindow::SmsTelefon[];
char MainWindow::SmsTime[];
char MainWindow::SmsDate[];
char MainWindow::SmsUser[];
char MainWindow::SmsId[];
char MainWindow::SmsStatus[];

Ui::MainWindow *MainWindow::sui;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  MainWindow::sui = ui;

  AtModem::pchSmsNew     = &MainWindow::SmsId[ 0 ];
  AtModem::pchCmtPhone   = &MainWindow::SmsTelefon[ 0 ];
  AtModem::pchCmtDay     = &MainWindow::SmsDate[ 0 ];
  AtModem::pchCmtTime    = &MainWindow::SmsTime[ 0 ];
  AtModem::pchCmtMessage = &MainWindow::SmsText[ 0 ];

  SerialDialog::Rx = &MainWindow::DadoRecebido;
  AtModem::DataSendEvent = &MainWindow::DadoEnviado;
  //AtModem::StatusEvent = &MainWindow::StatusRecebido;
  AtModem::OnEndProcess = &MainWindow::OnEndProcess;
  AtModem::Init ();

  MainWindow::InternetData ();

  ui->leSend->setFocus();
  gSD = new SerialDialog ();

  gDt = new Dtmf ();

  //this->close();
  this->Loop();

  QTimer::singleShot ( 5000, this, SLOT ( ContarTempo () ) );
}

void MainWindow::ContarTempo ()
{
  MainWindow::TimeReady = true;
  QTimer::singleShot ( 5000, this, SLOT ( ContarTempo () ) );
}

void MainWindow::OpenSerialDialog ()
{
  gSD->show ();
}

void MainWindow::showEvent( QShowEvent *ev )
{
  QTimer::singleShot ( 1000, this, SLOT ( OpenSerialDialog () ) );
}

void MainWindow::InternetData ()
{
  QString lqstrText;
  QChar lqchCharacter;
  //bool lblComma;
  int i;

  lqstrText = MainWindow::sui->leUrl->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::Host[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::Host[ i ] = '\0';

  lqstrText = MainWindow::sui->leSite->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::Site[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::Site[ i ] = '\0';

  lqstrText = MainWindow::sui->lePorta->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::Port[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::Port[ i ] = '\0';

  lqstrText = MainWindow::sui->leQueryString->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::Query[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::Query[ i ] = '\0';

  lqstrText = MainWindow::sui->leOperadoraId->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::IdConnect[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::IdConnect[ i ] = '\0';

  lqstrText = MainWindow::sui->leOperadoraPassword->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::IdPassword[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::IdPassword[ i ] = '\0';

  lqstrText = MainWindow::sui->leUserName->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::UserName[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::UserName[ i ] = '\0';

  lqstrText = MainWindow::sui->leUserPassword->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::UserPassword[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::UserPassword[ i ] = '\0';

  lqstrText = MainWindow::sui->leSmsTexto->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::SmsText[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::SmsText[ i ] = '\0';

  lqstrText = MainWindow::sui->leSmsTelefone->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::SmsTelefon[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::SmsTelefon[ i ] = '\0';

  lqstrText = MainWindow::sui->leSmsId->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::SmsId[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::SmsId[ i ] = '\0';

  lqstrText = MainWindow::sui->lePin->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::SinPin[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::SinPin[ i ] = '\0';

  lqstrText = MainWindow::sui->lePinNew->text();
  for ( i = 0; i != lqstrText.length(); i++ )
  {
    lqchCharacter = lqstrText.at ( i );
    MainWindow::SinNewPin[ i ] = lqchCharacter.toLatin1();
  }
  MainWindow::SinNewPin[ i ] = '\0';
}

void MainWindow::OnEndProcess ()
{
  StateMachine::Step();
}

void MainWindow::Loop ()
{
  Event::eEvent e;

  AtModem::StateMachineRun ();

  do
  {
    e = StackEnum::Get();

    if ( e == Event::None )
    {
      if ( ( MainWindow::CallReady == true ) && ( MainWindow::TimeReady == true ) )
      {
        if ( AtModem::FlagTest( kDefFlagRuning ) == false )
        {
          MainWindow::TimeReady   = false;
          AtModem::pDataList[ 0 ] = &MainWindow::Day[ 0 ];
          AtModem::pDataList[ 1 ] = &MainWindow::Clock[ 0 ];
          AtModem::pDataList[ 2 ] = &MainWindow::TimeZone[ 0 ];
          AtModem::RtcGet();
        }
      }
      break;
    }

    MainWindow::StatusRecebido( e );
  }
  while ( true );

  MainWindow::TimeReady = false;
  QTimer::singleShot ( 100, this, SLOT ( Loop () ) );
}

void MainWindow::StatusRecebido ( Event::eEvent aschStatus )
{
  int i = 0;
  int siMemoriaEndereco = 0;
  int siSemanaContador = 0;
  int siHoraMemoriaOn, siHoraMemoriaOff, siHoraRtc;
  int siGeneric = 0;
  char chRtcSemana = 0;
  bool blEstadoAtual;

  if ( aschStatus == Event::EndLine ) return;

  QString toAppend;

  QString lqstrPreviousText = MainWindow::sui->teStatus->toPlainText();
  switch ( aschStatus )
  {
    case Event::EndProcess:
      //StateMachine::Step();
      break;

    case Event::CallReady: /*MainWindow::CallReady = true;*/ toAppend = "Call Ready\n"; break;
    case Event::PowerDown: toAppend = "Normal power down\n"; break;
    case Event::NoCarrier: toAppend = "No carrier\n"; break;
    case Event::NoDialTone: toAppend = "no dial tone\n"; break;
      //case 6: toAppend = "connection failed\n"; break;
    case Event::NoAnswer: toAppend = "no answer\n"; break;
    case Event::Busy: toAppend = "busy\n"; break;
      //case 11: toAppend = "cme error\n"; break;
    case Event::SMSNew://***************************************************************************************************************************************************
      //{ "+CMGR: \"{str}\",\"{snum}\",\"{str}\",\"{time},{time}-{inum}\"\r\n{str}\0" };
      AtModem::pDataList[ 0 ] = AtModem::pchSmsNew;
      AtModem::pDataList[ 1 ] = &MainWindow::SmsStatus[ 0 ];
      AtModem::pDataList[ 2 ] = &MainWindow::SmsTelefon[ 0 ];
      AtModem::pDataList[ 3 ] = &MainWindow::SmsUser[ 0 ];
      AtModem::pDataList[ 4 ] = &MainWindow::SmsDate[ 0 ];
      AtModem::pDataList[ 5 ] = &MainWindow::SmsTime[ 0 ];
      AtModem::pDataList[ 6 ] = &MainWindow::TimeZone[ 0 ];
      AtModem::pDataList[ 7 ] = &MainWindow::SmsText[ 0 ];
      AtModem::pDataList[ 8 ] = &MainWindow::SmsId[ 0 ];
      //{num}\",\"{snum}\",\"{str}\",\"{time},{time}-{inum}\"\r\n{str}
      //AtModem::SmsReadAndDeleteById();
      MainWindow::TimeReady = false;
      AtModem::SmsReadById();
      lqstrPreviousText.append( "Nono SMS id: " );
      lqstrPreviousText.append( MainWindow::Id );
      lqstrPreviousText.append( "\n" );
      break;
    case Event::PowerOn: lqstrPreviousText.append( "Power ON\n" ); break;

    case Event::RTCRead:
      chRtcSemana = AtModem::DayOfWeek ( &MainWindow::Day[ 0 ] );

      siHoraRtc  = MainWindow::Clock[ 0 ] - '0';
      siHoraRtc *= 10;
      siHoraRtc += MainWindow::Clock[ 1 ] - '0';
      siHoraRtc *= 10;
      siHoraRtc += MainWindow::Clock[ 3 ] - '0';
      siHoraRtc *= 10;
      siHoraRtc += MainWindow::Clock[ 4 ] - '0';

      for ( i = 0; i != EEPROM_MEMORY_SIZE; i++ )
      {
        siMemoriaEndereco = i * EEPROM_ZISE;

        if ( ( EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_MAIN ) != '1' ) || ( EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_USER ) != '1' ) )
        {
          continue;
        }

        siHoraMemoriaOn  = EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_ON + 0 ) - '0';
        siHoraMemoriaOn *= 10;
        siHoraMemoriaOn += EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_ON + 1 ) - '0';
        siHoraMemoriaOn *= 10;
        siHoraMemoriaOn += EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_ON + 2 ) - '0';
        siHoraMemoriaOn *= 10;
        siHoraMemoriaOn += EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_ON + 3 ) - '0';

        siHoraMemoriaOff  = EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_OFF + 0 ) - '0';
        siHoraMemoriaOff *= 10;
        siHoraMemoriaOff += EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_OFF + 1 ) - '0';
        siHoraMemoriaOff *= 10;
        siHoraMemoriaOff += EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_OFF + 2 ) - '0';
        siHoraMemoriaOff *= 10;
        siHoraMemoriaOff += EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_OFF + 3 ) - '0';

        if ( ( siHoraMemoriaOn <= siHoraRtc ) && ( siHoraMemoriaOff >= siHoraRtc ) )
        {
          blEstadoAtual = true;
          qDebug () << "ligar rele:" << EEPROM::read ( siMemoriaEndereco + EEPROM_RELAY );
        }
        else
        {
          blEstadoAtual = false;
          qDebug () << "desligar rele:" << EEPROM::read ( siMemoriaEndereco + EEPROM_RELAY );
        }

        if ( blEstadoAtual == true )
        {
          if ( EEPROM::read ( siMemoriaEndereco + EEPROM_LAST_STATUS ) != '1' )
          {
            EEPROM::write ( ( siMemoriaEndereco + EEPROM_LAST_STATUS ), '1' );
//          MainWindow::SetOutput ( EEPROM::read ( siMemoriaEndereco + EEPROM_RELAY ), blEstadoAtual );
          }
        }

        else if ( blEstadoAtual == false )
        {
          if ( EEPROM::read ( siMemoriaEndereco + EEPROM_LAST_STATUS ) != '0' )
          {
            EEPROM::write ( ( siMemoriaEndereco + EEPROM_LAST_STATUS ), '0' );
//          MainWindow::SetOutput ( EEPROM::read ( siMemoriaEndereco + EEPROM_RELAY ), blEstadoAtual );
          }
        }
      }

      lqstrPreviousText.append( "Hora: " );
      lqstrPreviousText.append( MainWindow::Clock );
      lqstrPreviousText.append( "\nDia: " );
      lqstrPreviousText.append( MainWindow::Day );
      lqstrPreviousText.append( " ( dia da semana " );
      lqstrPreviousText.append( AtModem::DayOfWeek ( &MainWindow::Day[ 0 ] ) );
      lqstrPreviousText.append( " )\nTime zone:" );
      lqstrPreviousText.append( MainWindow::TimeZone );
      lqstrPreviousText.append( "\n" );
      break;

    case Event::SMSCompanyRead:
      lqstrPreviousText.append( "Telefone: " );
      lqstrPreviousText.append( MainWindow::SmsTelefon );
      lqstrPreviousText.append( "\nDia: " );
      lqstrPreviousText.append( MainWindow::SmsDate );
      lqstrPreviousText.append( " ( dia da semana " );
      lqstrPreviousText.append( AtModem::DayOfWeek ( &MainWindow::SmsDate[ 0 ] ) );
      lqstrPreviousText.append( " )\nHora: " );
      lqstrPreviousText.append( MainWindow::SmsTime );
      lqstrPreviousText.append( "\nMensagem: " );
      lqstrPreviousText.append( MainWindow::SmsText );
      lqstrPreviousText.append( "\n" );
      break;

    case Event::SignalQuality:
      lqstrPreviousText.append( "Qualidade: " );
      lqstrPreviousText.append( MainWindow::Qualidade );
      lqstrPreviousText.append( "\n" );

      i = 0;
      siGeneric = 0;
      while ( MainWindow::Qualidade[ i ] != '\0' )
      {
        siGeneric *= 10;
        siGeneric += ( MainWindow::Qualidade[ i ] - '0' );
        i += 1;
      }

      MainWindow::chTextSendAfterEvent[ 0 ] = '\0';

      if ( siGeneric <= 9 )
      {
        Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendSignalEvent[ 0 ], &MainWindow::kSendSignalRuimEvent[ 0 ] );
      }

      else if ( siGeneric <= 14 )
      {
        Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendSignalEvent[ 0 ], &MainWindow::kSendSignalBomEvent[ 0 ] );
      }

      else if ( siGeneric <= 30 )
      {
        Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendSignalEvent[ 0 ], &MainWindow::kSendSignalOtimoEvent[ 0 ] );
      }

      else
      {
        return;
      }

      StateMachine::Reset ();
      StateMachine::Add ( &MainWindow::SmsSendAfterEvent );
      StateMachine::Step ();
      break;

    case Event::CarrierNumberCaptured:
      lqstrPreviousText.append( "Id: " );
      lqstrPreviousText.append( MainWindow::SmsId );
      lqstrPreviousText.append( "\nTelefone: " );
      lqstrPreviousText.append( MainWindow::SmsTelefon );
      lqstrPreviousText.append( "\nUsuario: " );
      lqstrPreviousText.append( MainWindow::SmsUser );
      lqstrPreviousText.append( "\n" );
      break;

    case Event::SMSRead:
      lqstrPreviousText.append( "Id: " );
      lqstrPreviousText.append( MainWindow::SmsId );
      lqstrPreviousText.append( "\nTelefone: " );
      lqstrPreviousText.append( MainWindow::SmsTelefon );
      lqstrPreviousText.append( "\nAgenda: " );
      lqstrPreviousText.append( MainWindow::SmsUser );
      lqstrPreviousText.append( "\nDia: " );
      lqstrPreviousText.append( MainWindow::SmsDate );
      lqstrPreviousText.append( " ( dia da semana " );
      lqstrPreviousText.append( AtModem::DayOfWeek ( &MainWindow::SmsDate[ 0 ] ) );
      lqstrPreviousText.append( " )\nHora: " );
      lqstrPreviousText.append( MainWindow::SmsTime );
      lqstrPreviousText.append( "\nMensagem: " );
      lqstrPreviousText.append( MainWindow::SmsText );
      lqstrPreviousText.append( "\n" );

      MainWindow::TimeReady = false;
      AtModem::Checker ( &MainWindow::kReceiveRootNumberEnable[ 0 ],  &MainWindow::SmsText[ 0 ], Event::UserEvent1 );
      AtModem::Checker ( &MainWindow::kReceiveRootNumberDisable[ 0 ], &MainWindow::SmsText[ 0 ], Event::UserEvent2 );
      AtModem::Checker ( &MainWindow::kReceiveSetRtc[ 0 ],            &MainWindow::SmsText[ 0 ], Event::UserEvent3 );


      AtModem::pDataList[ 0 ] = &MainWindow::Id[ 0 ];
      AtModem::pDataList[ 1 ] = &MainWindow::Phone[ 0 ];
      AtModem::pDataList[ 2 ] = &MainWindow::User[ 0 ];
      AtModem::ResetPointers ();
      AtModem::Checker ( &MainWindow::kReceiveRootNumberAddPhoneBook[ 0 ], &MainWindow::SmsText[ 0 ], Event::UserEvent4 );

      AtModem::pDataList[ 0 ] = &MainWindow::Id[ 0 ];
      AtModem::ResetPointers ();
      AtModem::Checker ( &MainWindow::kReceiveRootNumberDelPhoneBook[ 0 ], &MainWindow::SmsText[ 0 ], Event::UserEvent5 );

      // 0 - memoria, 1 - rele, 2 - timer on, 3 - timer off, 4 - dias da semana
      AtModem::pDataList[ 0 ] = &MainWindow::chMemoria[ 0 ];
      AtModem::pDataList[ 1 ] = &MainWindow::chRele[ 0 ];
      AtModem::pDataList[ 2 ] = &MainWindow::chTimeOn[ 0 ];
      AtModem::pDataList[ 3 ] = &MainWindow::chTimerOff[ 0 ];
      AtModem::pDataList[ 4 ] = &MainWindow::chSemana[ 0 ];
      AtModem::ResetPointers ();
      AtModem::Checker ( &MainWindow::kReceiveAddTimer[ 0 ], &MainWindow::SmsText[ 0 ], Event::UserEvent6 );

      AtModem::Checker ( &MainWindow::kReceiveMainDisable[ 0 ], &MainWindow::SmsText[ 0 ], Event::UserEvent7 );
      AtModem::Checker ( &MainWindow::kReceiveMainEnable[ 0 ], &MainWindow::SmsText[ 0 ], Event::UserEvent8 );
      AtModem::Checker ( &MainWindow::kReceiveMainReset[ 0 ], &MainWindow::SmsText[ 0 ], Event::UserEvent9 );

      AtModem::Checker ( &MainWindow::kReceiveMakeTimerOn[ 0 ], &MainWindow::SmsText[ 0 ], Event::UserEvent10 );
      AtModem::Checker ( &MainWindow::kReceiveMakeTimerOff[ 0 ], &MainWindow::SmsText[ 0 ], Event::UserEvent11 );

      AtModem::pDataList[ 0 ] = &MainWindow::chMemoria[ 0 ];
      AtModem::Checker ( &MainWindow::kReceiveReadTimer[ 0 ], &MainWindow::SmsText[ 0 ], Event::UserEvent12 );
      break;

    case Event::SMSReadByStatus:
      AtModem::pDataList[ 0 ] = &MainWindow::SmsId[ 0 ];
      AtModem::pDataList[ 1 ] = &MainWindow::SmsStatus[ 0 ];
      AtModem::pDataList[ 2 ] = &MainWindow::SmsTelefon[ 0 ];
      AtModem::pDataList[ 3 ] = &MainWindow::SmsUser[ 0 ];
      AtModem::pDataList[ 4 ] = &MainWindow::SmsDate[ 0 ];
      AtModem::pDataList[ 5 ] = &MainWindow::SmsTime[ 0 ];
      AtModem::pDataList[ 6 ] = &MainWindow::SmsText[ 0 ];
      AtModem::ResetPointers ();

      lqstrPreviousText.append( "Status: " );
      lqstrPreviousText.append( MainWindow::SmsStatus );
      lqstrPreviousText.append( "\nTelefone: " );
      lqstrPreviousText.append( MainWindow::SmsTelefon );
      lqstrPreviousText.append( "\nAgenda: " );
      lqstrPreviousText.append( MainWindow::SmsUser );
      lqstrPreviousText.append( "\nDia: " );
      lqstrPreviousText.append( MainWindow::SmsDate );
      lqstrPreviousText.append( " ( dia da semana " );
      lqstrPreviousText.append( AtModem::DayOfWeek ( &MainWindow::SmsDate[ 0 ] ) );
      lqstrPreviousText.append( " )\nHora: " );
      lqstrPreviousText.append( MainWindow::SmsTime );
      lqstrPreviousText.append( "\nMensagem: " );
      lqstrPreviousText.append( MainWindow::SmsText );
      lqstrPreviousText.append( "\n" );
      break;

      #ifdef I_NEED_CALL_FUNCTIONS
        case Event::Ring:
          toAppend = "Ring...\n";

          #ifdef ENABLE_AUTO_CALLER_NUMBER
            AtModem::pDataList[ 0 ] = &MainWindow::Day[ 0 ];
            AtModem::pDataList[ 1 ] = &MainWindow::Clock[ 0 ];
            AtModem::pDataList[ 2 ] = &MainWindow::TimeZone[ 0 ];
            AtModem::CallGetNumber();
          #endif

          break;
        #endif

    case Event::SimReady:
      lqstrPreviousText.append( "SIM - Ok\n" );
      break;

    #ifdef I_NEED_PHONEBOOK_FUNCTIONS
      case Event::PhoneBookFind:
        lqstrPreviousText.append( "\n" );
        lqstrPreviousText.append( MainWindow::SmsId );
        lqstrPreviousText.append( "\n" );
        lqstrPreviousText.append( MainWindow::SmsTelefon );
        lqstrPreviousText.append( "\n" );
        lqstrPreviousText.append( MainWindow::SmsUser );
        lqstrPreviousText.append( "\n" );

        StateMachine::Reset ();
        StateMachine::Add ( &MainWindow::SmsSendAfterEvent );
        StateMachine::Add ( &MainWindow::StateDeleteSms );
        StateMachine::Step ();
      break;
    #endif

    case Event::SimPin:
      MainWindow::InternetData();
      AtModem::pDataList[ 0 ] = &MainWindow::SinPin[ 0 ];
      AtModem::SimEnterPin();
      lqstrPreviousText.append( "SIM - PIN solicitado\n" );
      break;

    case Event::EnginneringData:
      lqstrPreviousText.append( "\n" );
      lqstrPreviousText.append( MainWindow::Day );
      lqstrPreviousText.append( "\n" );
      lqstrPreviousText.append( MainWindow::Clock );
      lqstrPreviousText.append( "\n" );
      lqstrPreviousText.append( MainWindow::Text );
      lqstrPreviousText.append( "\n" );
      lqstrPreviousText.append( MainWindow::Host );
      lqstrPreviousText.append( "\n" );
      break;

    // root enable
    case Event::UserEvent1:
      if ( MainWindow::SmsUser[ 0 ] == '\0' )
      {
        StateMachine::Reset();
        StateMachine::Add ( &MainWindow::StateSetRootPhoneBook );
        StateMachine::Add ( &MainWindow::StateDeleteSms );
        StateMachine::Step ();
      }
      else
      {
        AtModem::pDataList[ 0 ] = &MainWindow::SmsId[ 0 ];
        //AtModem::pDataList[ 0 ] = AtModem::pchSmsNew;
        //AtModem::SmsDeleteById();
      }
      break;

    // root disable
    case Event::UserEvent2:
      if ( Buffer::Compare( &MainWindow::SmsUser[ 0 ], &MainWindow::kRootName[ 0 ] ) == true )
      {
        StateMachine::Reset();
        StateMachine::Add ( &MainWindow::StateClearRootPhoneBook );
        StateMachine::Add ( &MainWindow::StateDeleteSms );
        StateMachine::Step ();
      }
      else
      {
        AtModem::pDataList[ 0 ] = &MainWindow::SmsId[ 0 ];
        //AtModem::SmsDeleteById();
      }
      break;

    // set rtc
    case Event::UserEvent3:
      StateMachine::Reset();
      StateMachine::Add ( &MainWindow::RtcSet );
      StateMachine::Add ( &MainWindow::PhoneBookFindToSendEvent );
      StateMachine::Step ();
      break;

    // add phonebook id
    case Event::UserEvent4:

      // enviou o sms de confirmação
      MainWindow::chTextSendAfterEvent[ 0 ] = '\0';
      Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendPhoneBookAddEvent[ 0 ] );

      StateMachine::Reset();
      StateMachine::Add ( &MainWindow::PhoneBookAddById );
      StateMachine::Add ( &MainWindow::PhoneBookFindToSendEvent );
      StateMachine::Step ();
      break;

    // del phonebook id
    case Event::UserEvent5:
      AtModem::pDataList[ 0 ] = &MainWindow::Id[ 0 ];
      AtModem::PhoneBookClearId ();

      // enviou o sms de confirmação
      //MainWindow::pSendMsg[ 0 ] = &MainWindow::kSendPhoneBookAddEvent[ 0 ];
      //MainWindow::pSendMsg[ 1 ] = '\0';
      //MainWindow::PhoneBookFindToSendEvent ();
      break;

    // add timer
    case Event::UserEvent6:
      siMemoriaEndereco = 0;
      siSemanaContador  = 0;

      while ( MainWindow::chMemoria[ siSemanaContador ] != '\0' )
      {
        siMemoriaEndereco = ( siMemoriaEndereco * 10 ) + ( MainWindow::chMemoria[ siSemanaContador ] - '0' );
        siSemanaContador += 1;
      }

      siMemoriaEndereco *= EEPROM_ZISE;

      // habilitado principal
      EEPROM::write ( siMemoriaEndereco + EEPROM_ENABLE_MAIN, '1' );

      // habilitado usuário
      EEPROM::write ( siMemoriaEndereco + EEPROM_ENABLE_USER, '1' );

      // ultimo estado
      EEPROM::write ( siMemoriaEndereco + EEPROM_LAST_STATUS, 'x' );

      // rele
      EEPROM::write ( siMemoriaEndereco + EEPROM_RELAY, MainWindow::chRele[ 0 ] - '0' );

      // timer on
      EEPROM::write ( siMemoriaEndereco + EEPROM_TIMER_ON + 0, MainWindow::chTimeOn[ 0 ] );
      EEPROM::write ( siMemoriaEndereco + EEPROM_TIMER_ON + 1, MainWindow::chTimeOn[ 1 ] );
      EEPROM::write ( siMemoriaEndereco + EEPROM_TIMER_ON + 2, MainWindow::chTimeOn[ 3 ] );
      EEPROM::write ( siMemoriaEndereco + EEPROM_TIMER_ON + 3, MainWindow::chTimeOn[ 4 ] );

      // timer off
      EEPROM::write ( siMemoriaEndereco + EEPROM_TIMER_OFF + 0, MainWindow::chTimerOff[ 0 ] );
      EEPROM::write ( siMemoriaEndereco + EEPROM_TIMER_OFF + 1, MainWindow::chTimerOff[ 1 ] );
      EEPROM::write ( siMemoriaEndereco + EEPROM_TIMER_OFF + 2, MainWindow::chTimerOff[ 3 ] );
      EEPROM::write ( siMemoriaEndereco + EEPROM_TIMER_OFF + 3, MainWindow::chTimerOff[ 4 ] );

      // dias da semana
      EEPROM::write ( siMemoriaEndereco + EEPROM_SUNDAY, '0' );
      EEPROM::write ( siMemoriaEndereco + EEPROM_MONDAY, '0' );
      EEPROM::write ( siMemoriaEndereco + EEPROM_TUESDAY, '0' );
      EEPROM::write ( siMemoriaEndereco + EEPROM_WEDNESDAY, '0' );
      EEPROM::write ( siMemoriaEndereco + EEPROM_THURSDAY, '0' );
      EEPROM::write ( siMemoriaEndereco + EEPROM_FRIDAY, '0' );
      EEPROM::write ( siMemoriaEndereco + EEPROM_SATURDAY, '0' );

      siSemanaContador = 0;
      while ( MainWindow::chSemana[ siSemanaContador ] != '\0' )
      {
        EEPROM::write ( siMemoriaEndereco + ( MainWindow::chSemana[ siSemanaContador ] - ( '1' - EEPROM_SUNDAY ) ), '1' );
        siSemanaContador += 1;
      }

      lqstrPreviousText.append( "Timer recebido!\n" );
      lqstrPreviousText.append( MainWindow::chMemoria );
      lqstrPreviousText.append( "\n" );
      lqstrPreviousText.append( MainWindow::chRele );
      lqstrPreviousText.append( "\n" );
      lqstrPreviousText.append( MainWindow::chTimeOn );
      lqstrPreviousText.append( "\n" );
      lqstrPreviousText.append( MainWindow::chTimerOff );
      lqstrPreviousText.append( "\n" );
      lqstrPreviousText.append( MainWindow::chSemana );

      MainWindow::chTextSendAfterEvent[ 0 ] = '\0';
      Copy::Spacer( &MainWindow::kSendSpacer[ 0 ] );
      Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendTimerSetEvent[ 0 ], &MainWindow::chMemoria[ 0 ], &MainWindow::chRele[ 0 ], &MainWindow::chTimeOn[ 0 ], &MainWindow::chTimerOff[ 0 ], &MainWindow::chSemana[ 0 ] );

      StateMachine::Reset();
      StateMachine::Add ( &MainWindow::PhoneBookFindToSendEvent );
      StateMachine::Step ();
      break;

    // desliga tudo
    case Event::UserEvent7:
      for ( i = 0; i != EEPROM_MEMORY_SIZE; i++ )
      {
        siMemoriaEndereco = i * EEPROM_ZISE;
        qDebug () << "endereço: " << siMemoriaEndereco;

        if ( EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_MAIN ) != 'x' )
        {
//        MainWindow::SetOutput ( EEPROM::read ( siMemoriaEndereco + EEPROM_RELAY ), false );
          EEPROM::write ( ( siMemoriaEndereco + EEPROM_ENABLE_MAIN ), '0' );
        }
      }

      // enviou o sms de confirmação
      MainWindow::chTextSendAfterEvent[ 0 ] = '\0';
      Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendEnableMainClearEvent[ 0 ] );

      StateMachine::Reset();
      StateMachine::Add ( &MainWindow::PhoneBookFindToSendEvent );
      StateMachine::Step ();
      break;

    // liga tudo
    case Event::UserEvent8:
      for ( i = 0; i != EEPROM_MEMORY_SIZE; i++ )
      {
        siMemoriaEndereco = i * EEPROM_ZISE;
        //qDebug () << "endereço: " << siMemoriaEndereco;
        qDebug () << "endereço main enable: " << siMemoriaEndereco + EEPROM_ENABLE_MAIN;

        if ( EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_MAIN ) != 'x' )
        {
          EEPROM::write ( ( siMemoriaEndereco + EEPROM_ENABLE_MAIN ), '1' );
        }
      }

      // enviou o sms de confirmação
      MainWindow::chTextSendAfterEvent[ 0 ] = '\0';
      Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendEnableMainSetEvent[ 0 ] );

      StateMachine::Reset();
      StateMachine::Add ( &MainWindow::PhoneBookFindToSendEvent );
      StateMachine::Step ();
      break;

    // reset
    case Event::UserEvent9:
      for ( i = 0; i != EEPROM_MEMORY_SIZE; i++ )
      {
        siMemoriaEndereco = i * EEPROM_ZISE;

        //qDebug () << "endereço: " << siMemoriaEndereco;
        qDebug () << "endereço main enable: " << siMemoriaEndereco + EEPROM_ENABLE_MAIN;

        EEPROM::write ( ( siMemoriaEndereco + EEPROM_ENABLE_MAIN ), 'x' );
        EEPROM::write ( ( siMemoriaEndereco + EEPROM_ENABLE_USER ), 'x' );
      }
      // enviou o sms de confirmação
      MainWindow::chTextSendAfterEvent[ 0 ] = '\0';
      Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendResetEvent[ 0 ] );

      StateMachine::Reset();
      StateMachine::Add ( &MainWindow::PhoneBookFindToSendEvent );
      StateMachine::Step ();
      break;

    // liagr timer
    case Event::UserEvent10:
      siMemoriaEndereco = 0;
      siSemanaContador  = 0;

      while ( MainWindow::chMemoria[ siSemanaContador ] != '\0' )
      {
        siMemoriaEndereco = ( siMemoriaEndereco * 10 ) + ( MainWindow::chMemoria[ siSemanaContador ] - '0' );
        siSemanaContador += 1;
      }

      siMemoriaEndereco *= EEPROM_ZISE;

      MainWindow::chTextSendAfterEvent[ 0 ] = '\0';
      // habilitado usuário
      if ( ( EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_MAIN ) == 'x' ) || ( EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_USER ) == 'x' ) )
      {
        // enviou o sms de confirmação
        Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendTimerMakeErrorEvent[ 0 ] );
      }

      else
      {
        EEPROM::write ( siMemoriaEndereco + EEPROM_ENABLE_USER, '1' );

        // enviou o sms de confirmação
        Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendTimerMakeOnEvent[ 0 ] );
      }

      StateMachine::Reset();
      StateMachine::Add ( &MainWindow::PhoneBookFindToSendEvent );
      StateMachine::Step ();
      break;

    // desligar timer
    case Event::UserEvent11:
      siMemoriaEndereco = 0;
      siSemanaContador  = 0;

      while ( MainWindow::chMemoria[ siSemanaContador ] != '\0' )
      {
        siMemoriaEndereco = ( siMemoriaEndereco * 10 ) + ( MainWindow::chMemoria[ siSemanaContador ] - '0' );
        siSemanaContador += 1;
      }

      siMemoriaEndereco *= EEPROM_ZISE;

      // habilitado usuário
      MainWindow::chTextSendAfterEvent[ 0 ] = '\0';

      if ( ( EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_MAIN ) == 'x' ) || ( EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_USER ) == 'x' ) )
      {
        // enviou o sms de confirmação
        Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendTimerMakeErrorEvent[ 0 ] );
      }

      else
      {
        EEPROM::write ( siMemoriaEndereco + EEPROM_ENABLE_USER, '0' );
        Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendTimerMakeOffEvent[ 0 ] );
      }

      StateMachine::Reset();
      StateMachine::Add ( &MainWindow::PhoneBookFindToSendEvent );
      StateMachine::Step ();
      break;

    case Event::UserEvent12:
      while ( MainWindow::chMemoria[ siSemanaContador ] != '\0' )
      {
        siMemoriaEndereco = ( siMemoriaEndereco * 10 ) + ( MainWindow::chMemoria[ siSemanaContador ] - '0' );
        siSemanaContador += 1;
      }

      siMemoriaEndereco *= EEPROM_ZISE;

      MainWindow::chRele[  0 ] = EEPROM::read ( siMemoriaEndereco + EEPROM_RELAY ) + '0';
      MainWindow::chRele[  1 ] = ' ';
      MainWindow::chRele[  2 ] = 'm';
      MainWindow::chRele[  3 ] = ':';
      MainWindow::chRele[  4 ] = EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_MAIN );
      MainWindow::chRele[  5 ] = ' ';
      MainWindow::chRele[  6 ] = 'u';
      MainWindow::chRele[  7 ] = ':';
      MainWindow::chRele[  8 ] = EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_USER );
      MainWindow::chRele[  9 ] = ' ';
      MainWindow::chRele[ 10 ] = '\0';

      if ( ( EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_MAIN ) != 'x' ) && EEPROM::read ( siMemoriaEndereco + EEPROM_ENABLE_USER ) != 'x' )
      {
        MainWindow::chTimeOn[ 0 ] = EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_ON + 0 );
        MainWindow::chTimeOn[ 1 ] = EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_ON + 1 );
        MainWindow::chTimeOn[ 2 ] = ':';
        MainWindow::chTimeOn[ 3 ] = EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_ON + 2 );
        MainWindow::chTimeOn[ 4 ] = EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_ON + 3 );
        MainWindow::chTimeOn[ 5 ] = '\0';

        MainWindow::chTimerOff[ 0 ] = EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_OFF + 0 );
        MainWindow::chTimerOff[ 1 ] = EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_OFF + 1 );
        MainWindow::chTimerOff[ 2 ] = ':';
        MainWindow::chTimerOff[ 3 ] = EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_OFF + 2 );
        MainWindow::chTimerOff[ 4 ] = EEPROM::read ( siMemoriaEndereco + EEPROM_TIMER_OFF + 3 );
        MainWindow::chTimerOff[ 5 ] = '\0';

        MainWindow::chSemana[ 0 ] = ( EEPROM::read ( siMemoriaEndereco + EEPROM_SUNDAY ) == '1' ) ? '1' : ' ';
        MainWindow::chSemana[ 1 ] = ( EEPROM::read ( siMemoriaEndereco + EEPROM_MONDAY ) == '1' ) ? '2' : ' ';
        MainWindow::chSemana[ 2 ] = ( EEPROM::read ( siMemoriaEndereco + EEPROM_TUESDAY ) == '1' ) ? '3' : ' ';
        MainWindow::chSemana[ 3 ] = ( EEPROM::read ( siMemoriaEndereco + EEPROM_WEDNESDAY ) == '1' ) ? '4' : ' ';
        MainWindow::chSemana[ 4 ] = ( EEPROM::read ( siMemoriaEndereco + EEPROM_THURSDAY ) == '1' ) ? '5' : ' ';
        MainWindow::chSemana[ 5 ] = ( EEPROM::read ( siMemoriaEndereco + EEPROM_FRIDAY ) == '1' ) ? '6' : ' ';
        MainWindow::chSemana[ 6 ] = ( EEPROM::read ( siMemoriaEndereco + EEPROM_SATURDAY ) == '1' ) ? '7' : ' ';
        MainWindow::chSemana[ 7 ] = '\0';
      }

      else
      {
        MainWindow::chTimeOn[ 0 ]   = '\0';
        MainWindow::chTimerOff[ 0 ] = '\0';
        MainWindow::chSemana[ 0 ]   = '\0';
      }

      MainWindow::chTextSendAfterEvent[ 0 ] = '\0';
      Copy::Spacer( &MainWindow::kSendSpacer[ 0 ] );
      Copy::Data ( &MainWindow::chTextSendAfterEvent[ 0 ], &MainWindow::kSendTimerReadEvent[ 0 ], &MainWindow::chRele[ 0 ], &MainWindow::chTimeOn[ 0 ], &MainWindow::chTimerOff[ 0 ], &MainWindow::chSemana[ 0 ] );

      StateMachine::Reset();
      StateMachine::Add ( &MainWindow::PhoneBookFindToSendEvent );
      StateMachine::Step ();
      break;

    default: toAppend = "";
  }
  lqstrPreviousText.append( toAppend );
  MainWindow::sui->teStatus->setPlainText( lqstrPreviousText );

  QTextCursor C = MainWindow::sui->teStatus->textCursor();
  C.movePosition(QTextCursor::End);
  MainWindow::sui->teStatus->setTextCursor( C );
}

void MainWindow::StateSetRootPhoneBook ()
{
  AtModem::pDataList[ 0 ] = &MainWindow::SmsTelefon[ 0 ];
  MainWindow::SetRootPhoneBook ();
}

void MainWindow::StateClearRootPhoneBook ()
{
  MainWindow::ClearRootPhoneBook ();
}

void MainWindow::StateDeleteSms ()
{
  AtModem::pDataList[ 0 ] = AtModem::pchSmsNew;
  AtModem::SmsDeleteById();
}

void MainWindow::DadoRecebido ( char achDado )
{
  switch ( MainWindow::CorAtual )
  {
    case Color::Preto:
      MainWindow::sui->teSerialTx->setTextColor( QColor ( 255, 0, 0 ) );
      MainWindow::CorAtual = Color::Vermelho;
      break;

    case Color::Azul:
      MainWindow::sui->teSerialTx->setTextColor( QColor ( 255, 0, 0 ) );
      MainWindow::CorAtual = Color::Vermelho;
      break;

    case Color::Vermelho:
      break;
  }

  if ( achDado == '\r' )
  {
    MainWindow::sui->teSerialTx->insertPlainText( "\\r" );
  }

  else if ( achDado == '\n' )
  {
    MainWindow::sui->teSerialTx->insertPlainText( "\\n\r\n" );
  }

  else
  {
    if ( achDado == '<' )
    {
      QString t = QString ( "&lt;" );
      MainWindow::sui->teSerialTx->insertPlainText( t );
    }
    else
    {
      QString t = QString ( achDado );
      MainWindow::sui->teSerialTx->insertPlainText( t );
    }
  }

  QTextCursor C = MainWindow::sui->teSerialTx->textCursor();
  C.movePosition(QTextCursor::End);
  MainWindow::sui->teSerialTx->setTextCursor( C );

  AtModem::Get( achDado );
}

void MainWindow::DadoEnviado ( char achDado )
{
  switch ( MainWindow::CorAtual )
  {
    case Color::Preto:
      MainWindow::sui->teSerialTx->setTextColor( QColor ( 0, 0, 255 ) );
      MainWindow::CorAtual = Color::Azul;
      break;

    case Color::Vermelho:
      MainWindow::sui->teSerialTx->setTextColor( QColor ( 0, 0, 255 ) );
      MainWindow::CorAtual = Color::Azul;
      break;

    case Color::Azul:
      break;
  }

  if ( achDado == '\r' )
  {
    MainWindow::sui->teSerialTx->insertPlainText( "\\r" );
  }

  else if ( achDado == '\n' )
  {
    MainWindow::sui->teSerialTx->insertPlainText( "\\n\n" );
  }

  else
  {
    if ( achDado == '<' )
    {
      QString t = QString ( "&lt;" );
      MainWindow::sui->teSerialTx->insertPlainText( t );
    }
    else
    {
      QString t = QString ( achDado );
      MainWindow::sui->teSerialTx->insertPlainText( t );
    }
  }

  QTextCursor C = MainWindow::sui->teSerialTx->textCursor();
  C.movePosition(QTextCursor::End);
  MainWindow::sui->teSerialTx->setTextCursor( C );

  if ( SerialDialog::Tx != '\0' )
  {
    SerialDialog::Tx ( achDado );
  }
}

MainWindow::~MainWindow()
{
  gSD->serialDisconect ();
  delete ui;
}

void MainWindow::on_actionSair_triggered()
{
    this->close();
}

void MainWindow::on_actionSerial_triggered()
{
    gSD->exec ();
}

void MainWindow::on_pbSend_clicked()
{
  QTextCursor C = MainWindow::sui->teSerialTx->textCursor();
  C.movePosition(QTextCursor::End);
  MainWindow::sui->teSerialTx->setTextCursor( C );

  QString lqstrPreviousText = MainWindow::sui->leSend->text();

  if ( lqstrPreviousText.contains( "\\r\\n" ) == true )
  {
    lqstrPreviousText.replace( "\r", "" );
    lqstrPreviousText.replace( "\n", "" );

    lqstrPreviousText.replace( "\\r", "\r" );
    lqstrPreviousText.replace( "\\n", "\n" );
  }

  else if ( lqstrPreviousText.contains( "\\n\\r" ) == true )
  {
    lqstrPreviousText.replace( "\r", "" );
    lqstrPreviousText.replace( "\n", "" );

    lqstrPreviousText.replace( "\\n\\r", "\r\n" );
  }

  else if ( lqstrPreviousText.contains( "\\n" ) == true )
  {
    lqstrPreviousText.replace( "\\n", "\r\n" );
  }

  else if ( lqstrPreviousText.contains( "\\r" ) == true )
  {
    lqstrPreviousText.replace( "\\r", "\r\n" );
  }

  else
  {
    lqstrPreviousText.append( "\r\n" );
  }

  QByteArray text = lqstrPreviousText.toLocal8Bit();
  char *data = new char[text.size()];
  strcpy(data, text.data());

  for ( int i = 0; i != text.size(); i++ )
  {
    MainWindow::DadoEnviado ( data[ i ] );
  }
}

void MainWindow::on_btClear_clicked()
{
  MainWindow::Debug[ 0 ] = '\0';
  MainWindow::DebugDataPointer = 0;

  ui->teSerialTx->clear();
  ui->leSend->setFocus();
}

void MainWindow::on_pbDebug_clicked()
{
  QString lqstrPreviousText = MainWindow::sui->leSend->text();

  if ( lqstrPreviousText.contains( "+CCLK" ) )
  {
    AtModem::pDataList[ 0 ] = &MainWindow::Day[ 0 ];
    AtModem::pDataList[ 1 ] = &MainWindow::Clock[ 0 ];
    AtModem::pDataList[ 2 ] = &MainWindow::TimeZone[ 0 ];
  }

  else if ( lqstrPreviousText.contains( "+CMGR" ) )
  {
    AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::pDataList[ 1 ] = &MainWindow::SmsTelefon[ 0 ];
    AtModem::pDataList[ 2 ] = &MainWindow::SmsUser[ 0 ];
    AtModem::pDataList[ 3 ] = &MainWindow::SmsDate[ 0 ];
    AtModem::pDataList[ 4 ] = &MainWindow::SmsTime[ 0 ];
    AtModem::pDataList[ 5 ] = &MainWindow::TimeZone[ 0 ];
    AtModem::pDataList[ 6 ] = &MainWindow::SmsText[ 0 ];
  }

  AtModem::ResetPointers ();

  lqstrPreviousText.replace( "\\r", "\r" );
  lqstrPreviousText.replace( "\\n", "\n" );

  QByteArray text = lqstrPreviousText.toLatin1();
  char *data = new char[text.size()];
  strcpy(data, text.data());

  for ( int i = 0; i != text.size(); i++ )
  {
    MainWindow::DadoRecebido ( data[ i ] );
  }
  return;
}

void MainWindow::on_actionGet_SIM_Status_triggered()
{
  #ifdef I_NEED_SIM_PIN_FUNCTIONS
    AtModem::SimStatus ();
  #endif
}

void MainWindow::on_actionEnter_PIN_triggered()
{
  #ifdef I_NEED_SIM_PIN_FUNCTIONS
    MainWindow::InternetData ();
    AtModem::pDataList[ 0 ] = &MainWindow::SinPin[ 0 ];
    AtModem::SimEnterPin ();
  #endif
}

void MainWindow::on_actionGet_signal_quality_triggered()
{
  #ifdef I_NEED_SIM_PIN_FUNCTIONS
    AtModem::pDataList[ 0 ] = &MainWindow::Qualidade[ 0 ];
    AtModem::SignalQuality();
  #endif
}

void MainWindow::on_actionChange_PIN_triggered()
{
  #ifdef I_NEED_SIM_PIN_FUNCTIONS
    MainWindow::InternetData ();
    AtModem::pDataList[ 0 ] = &MainWindow::SinPin[ 0 ];
    AtModem::pDataList[ 1 ] = &MainWindow::SinNewPin[ 0 ];
    MainWindow::InternetData ();
    AtModem::SimChangePin ();
  #endif
}

void MainWindow::on_actionLock_triggered()
{
  #ifdef I_NEED_SIM_PIN_FUNCTIONS
    MainWindow::InternetData ();
    AtModem::pDataList[ 0 ] = &MainWindow::SinPin[ 0 ];
    AtModem::SimLockByPin ();
  #endif
}

void MainWindow::on_actionPIN_Unlock_triggered()
{
  #ifdef I_NEED_SIM_PIN_FUNCTIONS
    MainWindow::InternetData ();
    AtModem::pDataList[ 0 ] = &MainWindow::SinPin[ 0 ];
    AtModem::SimUnlockByPin ();
  #endif
}

void MainWindow::on_actionUse_GET_method_to_connect_a_host_triggered()
{
  #ifdef I_NEED_USE_INTERNET_FUNCTIONS
    MainWindow::InternetData ();
    AtModem::pDataList[ 0 ] = &MainWindow::IdConnect[ 0 ];
    AtModem::pDataList[ 1 ] = &MainWindow::IdConnect[ 0 ];
    AtModem::pDataList[ 2 ] = &MainWindow::IdPassword[ 0 ];
    AtModem::pDataList[ 3 ] = &MainWindow::IdPassword[ 0 ];
    AtModem::pDataList[ 4 ] = &MainWindow::Host[ 0 ];
    AtModem::pDataList[ 5 ] = &MainWindow::Port[ 0 ];
    AtModem::pDataList[ 6 ] = &MainWindow::Site[ 0 ];
    AtModem::pDataList[ 7 ] = &MainWindow::Query[ 0 ];
    AtModem::pDataList[ 8 ] = &MainWindow::Host[ 0 ];
    AtModem::SendDataByGet();
  #endif
}

void MainWindow::on_actionDisconnect_triggered()
{
  #ifdef I_NEED_USE_INTERNET_FUNCTIONS
    AtModem::DisconnectToHost ();
  #endif
}

void MainWindow::on_actionSend_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    MainWindow::InternetData ();
    AtModem::pDataList[ 0 ] = &MainWindow::SmsTelefon[ 0 ];
    AtModem::pDataList[ 1 ] = &MainWindow::SmsText[ 0 ];
    AtModem::SmsSend();
  #endif
}

void MainWindow::on_actionRead_by_id_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    MainWindow::InternetData ();
    AtModem::pDataList[ 0 ] = &MainWindow::SmsId[ 0 ];
    AtModem::pDataList[ 1 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::pDataList[ 2 ] = &MainWindow::SmsTelefon[ 0 ];
    AtModem::pDataList[ 3 ] = &MainWindow::SmsUser[ 0 ];
    AtModem::pDataList[ 4 ] = &MainWindow::SmsDate[ 0 ];
    AtModem::pDataList[ 5 ] = &MainWindow::SmsTime[ 0 ];
    AtModem::pDataList[ 6 ] = &MainWindow::TimeZone[ 0 ];
    AtModem::pDataList[ 7 ] = &MainWindow::SmsText[ 0 ];
    AtModem::SmsReadById();
  #endif
}

void MainWindow::on_actionDelete_by_id_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    MainWindow::InternetData ();
    AtModem::pDataList[ 0 ] = &MainWindow::SmsId[ 0 ];
    AtModem::SmsDeleteById();
  #endif
}

void MainWindow::on_actionRead_and_delete_by_id_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    MainWindow::InternetData ();
    AtModem::pDataList[ 0 ] = &MainWindow::SmsId[ 0 ];
    AtModem::pDataList[ 1 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::pDataList[ 2 ] = &MainWindow::SmsTelefon[ 0 ];
    AtModem::pDataList[ 3 ] = &MainWindow::SmsUser[ 0 ];
    AtModem::pDataList[ 4 ] = &MainWindow::SmsDate[ 0 ];
    AtModem::pDataList[ 5 ] = &MainWindow::SmsTime[ 0 ];
    AtModem::pDataList[ 6 ] = &MainWindow::SmsText[ 0 ];
    AtModem::pDataList[ 7 ] = &MainWindow::SmsId[ 0 ];
    AtModem::SmsReadAndDeleteById();
  #endif
}

void MainWindow::on_actionEcho_ON_triggered()
{
  AtModem::EchoOn();
}

void MainWindow::on_actionEcho_OFF_triggered()
{
  AtModem::EchoOff();
}

void MainWindow::on_actionPower_OFF_triggered()
{
  #ifdef I_NEED_POWER_DOWN_FUNCTIONS
    AtModem::PowerDown ();
  #endif
}

void MainWindow::on_actionCurrent_call_number_triggered()
{
  AtModem::pDataList[ 0 ] = &MainWindow::Day[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::Clock[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::TimeZone[ 0 ];
  AtModem::CallGetNumber ();
}

void MainWindow::on_actionDelete_by_status_DEL_READ_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    const char lcchStatus[] = { "DEL READ\0" };
    AtModem::ConstCharToChar( &lcchStatus[ 0 ], &MainWindow::SmsStatus[ 0 ] );

    AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::SmsDeleteByStatus();
  #endif
}

void MainWindow::on_actionDelete_by_status_DEL_UNREAD_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    const char lcchStatus[] = { "DEL UNREAD\0" };
    AtModem::ConstCharToChar( &lcchStatus[ 0 ], &MainWindow::SmsStatus[ 0 ] );

    AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::SmsDeleteByStatus();
  #endif
}

void MainWindow::on_actionDelete_by_status_DEL_SENT_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    const char lcchStatus[] = { "DEL SENT\0" };
    AtModem::ConstCharToChar( &lcchStatus[ 0 ], &MainWindow::SmsStatus[ 0 ] );

    AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::SmsDeleteByStatus();
  #endif
}

void MainWindow::on_actionDelete_by_status_DEL_UNSENT_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    const char lcchStatus[] = { "DEL UNSENT\0" };
    AtModem::ConstCharToChar( &lcchStatus[ 0 ], &MainWindow::SmsStatus[ 0 ] );

    AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::SmsDeleteByStatus();
  #endif
}

void MainWindow::on_actionDelete_by_status_DEL_INBOX_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    const char lcchStatus[] = { "DEL INBOX\0" };
    AtModem::ConstCharToChar( &lcchStatus[ 0 ], &MainWindow::SmsStatus[ 0 ] );

    AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::SmsDeleteByStatus();
  #endif
}

void MainWindow::on_actionDelete_by_status_DEL_ALL_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    const char lcchStatus[] = { "DEL ALL\0" };
    AtModem::ConstCharToChar( &lcchStatus[ 0 ], &MainWindow::SmsStatus[ 0 ] );

    AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::SmsDeleteByStatus();
  #endif
}

void MainWindow::on_actionRead_by_status_ALL_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    const char lcchStatus[] = { "ALL\0" };
    AtModem::ConstCharToChar( &lcchStatus[ 0 ], &MainWindow::SmsStatus[ 0 ] );

    AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::pDataList[ 1 ] = &MainWindow::SmsId[ 0 ];
    AtModem::pDataList[ 2 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::pDataList[ 3 ] = &MainWindow::SmsTelefon[ 0 ];
    AtModem::pDataList[ 4 ] = &MainWindow::SmsUser[ 0 ];
    AtModem::pDataList[ 5 ] = &MainWindow::SmsDate[ 0 ];
    AtModem::pDataList[ 6 ] = &MainWindow::SmsTime[ 0 ];
    AtModem::pDataList[ 7 ] = &MainWindow::SmsText[ 0 ];
    AtModem::SmsReadByStatus();
  #endif
}

void MainWindow::on_actionRead_by_status_REC_READ_triggered()
{
  #ifdef I_NEED_SMS_FUNCTIONS
    const char lcchStatus[] = { "REC READ\0" };
    AtModem::ConstCharToChar( &lcchStatus[ 0 ], &MainWindow::SmsStatus[ 0 ] );

    AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::pDataList[ 1 ] = &MainWindow::SmsId[ 0 ];
    AtModem::pDataList[ 2 ] = &MainWindow::SmsStatus[ 0 ];
    AtModem::pDataList[ 3 ] = &MainWindow::SmsTelefon[ 0 ];
    AtModem::pDataList[ 4 ] = &MainWindow::SmsUser[ 0 ];
    AtModem::pDataList[ 5 ] = &MainWindow::SmsDate[ 0 ];
    AtModem::pDataList[ 6 ] = &MainWindow::SmsTime[ 0 ];
    AtModem::pDataList[ 7 ] = &MainWindow::SmsText[ 0 ];
    AtModem::SmsReadByStatus();
  #endif
}

void MainWindow::on_actionRead_by_status_REC_UNREAD_triggered()
{
#ifdef I_NEED_SMS_FUNCTIONS
  const char lcchStatus[] = { "REC UNREAD\0" };
  AtModem::ConstCharToChar( &lcchStatus[ 0 ], &MainWindow::SmsStatus[ 0 ] );

  AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::SmsId[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::SmsStatus[ 0 ];
  AtModem::pDataList[ 3 ] = &MainWindow::SmsTelefon[ 0 ];
  AtModem::pDataList[ 4 ] = &MainWindow::SmsUser[ 0 ];
  AtModem::pDataList[ 5 ] = &MainWindow::SmsDate[ 0 ];
  AtModem::pDataList[ 6 ] = &MainWindow::SmsTime[ 0 ];
  AtModem::pDataList[ 7 ] = &MainWindow::SmsText[ 0 ];
  AtModem::SmsReadByStatus();
#endif
}

void MainWindow::on_actionRead_by_status_STO_SEND_triggered()
{
#ifdef I_NEED_SMS_FUNCTIONS
  const char lcchStatus[] = { "STO SENT\0" };
  AtModem::ConstCharToChar( &lcchStatus[ 0 ], &MainWindow::SmsStatus[ 0 ] );

  AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::SmsId[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::SmsStatus[ 0 ];
  AtModem::pDataList[ 3 ] = &MainWindow::SmsTelefon[ 0 ];
  AtModem::pDataList[ 4 ] = &MainWindow::SmsUser[ 0 ];
  AtModem::pDataList[ 5 ] = &MainWindow::SmsDate[ 0 ];
  AtModem::pDataList[ 6 ] = &MainWindow::SmsTime[ 0 ];
  AtModem::pDataList[ 7 ] = &MainWindow::SmsText[ 0 ];
  AtModem::SmsReadByStatus();
#endif
}

void MainWindow::on_actionRead_by_status_STO_UNSENT_triggered()
{
#ifdef I_NEED_SMS_FUNCTIONS
  const char lcchStatus[] = { "STO UNSENT\0" };
  AtModem::ConstCharToChar( &lcchStatus[ 0 ], &MainWindow::SmsStatus[ 0 ] );

  AtModem::pDataList[ 0 ] = &MainWindow::SmsStatus[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::SmsId[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::SmsStatus[ 0 ];
  AtModem::pDataList[ 3 ] = &MainWindow::SmsTelefon[ 0 ];
  AtModem::pDataList[ 4 ] = &MainWindow::SmsUser[ 0 ];
  AtModem::pDataList[ 5 ] = &MainWindow::SmsDate[ 0 ];
  AtModem::pDataList[ 6 ] = &MainWindow::SmsTime[ 0 ];
  AtModem::pDataList[ 7 ] = &MainWindow::SmsText[ 0 ];
  AtModem::SmsReadByStatus();
#endif
}

void MainWindow::on_actionGet_Number_triggered()
{
  AtModem::pDataList[ 0 ] = &MainWindow::SmsId[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::SmsTelefon[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::SmsUser[ 0 ];
  AtModem::CallGetNumber();
}

void MainWindow::on_actionCall_Number_triggered()
{
  MainWindow::InternetData ();
  AtModem::pDataList[ 0 ] = &MainWindow::SmsTelefon[ 0 ];
  AtModem::CallDial();
}

void MainWindow::on_actionHang_Up_triggered()
{
  AtModem::CallHangUp();
}

void MainWindow::on_actionAnswering_triggered()
{
  AtModem::CallAnswering();
}

void MainWindow::on_actionDTMF_triggered()
{
  gDt->show();
}

void MainWindow::on_leSend_returnPressed()
{
  MainWindow::on_pbSend_clicked();
}

void MainWindow::on_actionRead_triggered()
{
  if ( AtModem::FlagTest( kDefFlagRuning ) == true )
  {
    return;
  }

  AtModem::pDataList[ 0 ] = &MainWindow::Day[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::Clock[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::TimeZone[ 0 ];
  AtModem::RtcGet();
}

void MainWindow::on_actionSet_triggered()
{
  AtModem::pDataList[ 0 ] = &MainWindow::Day[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::Clock[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::TimeZone[ 0 ];
  AtModem::RtcSet ();
}

void MainWindow::on_actionGet_GEO_data_GPS_Less_triggered()
{
  AtModem::pDataList[ 0 ] = &MainWindow::Day[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::Clock[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::Text[ 0 ];
  AtModem::pDataList[ 3 ] = &MainWindow::Host[ 0 ];
  AtModem::GetEnginneringData ();
}

void MainWindow::on_actionAgenda_Adicionar_triggered()
{
  MainWindow::InternetData();
  AtModem::pDataList[ 0 ] = &MainWindow::Phone[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::User[ 0 ];
  AtModem::PhoneBookSet ();
}

void MainWindow::on_actionAgenda_Adicionar_com_Id_triggered()
{
  MainWindow::InternetData();
  AtModem::pDataList[ 0 ] = &MainWindow::Id[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::Phone[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::User[ 0 ];
  AtModem::PhoneBookIdSet ();
}

void MainWindow::on_actionAgenda_Apagar_com_Id_triggered()
{
  MainWindow::InternetData();
  AtModem::pDataList[ 0 ] = &MainWindow::Id[ 0 ];
  AtModem::PhoneBookClearId ();
}

void MainWindow::on_actionAgenda_Procurar_triggered()
{
  MainWindow::InternetData();
  AtModem::pDataList[ 0 ] = &MainWindow::SmsText[ 0 ];
  AtModem::pDataList[ 1 ] = &MainWindow::SmsId[ 0 ];
  AtModem::pDataList[ 2 ] = &MainWindow::SmsTelefon[ 0 ];
  AtModem::pDataList[ 3 ] = &MainWindow::SmsUser[ 0 ];
  AtModem::PhoneBookFind ();
}
