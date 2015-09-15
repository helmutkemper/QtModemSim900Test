#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define ENABLE_AUTO_READ_AND_DELETE_SMS
#define ENABLE_AUTO_READ_SMS
#define ENABLE_AUTO_PIN_ENABLE
#define ENABLE_AUTO_CALLER_NUMBER
#define ENABLE_AUTO_SET_RTC

#define kDefDebugSize 1024

#define EEPROM_ENABLE_MAIN  0
#define EEPROM_ENABLE_USER  1
#define EEPROM_LAST_STATUS  2
#define EEPROM_RELAY        3
#define EEPROM_TIMER_ON     4
#define EEPROM_TIMER_OFF    8
#define EEPROM_SUNDAY      12
#define EEPROM_MONDAY      13
#define EEPROM_TUESDAY     14
#define EEPROM_WEDNESDAY   15
#define EEPROM_THURSDAY    16
#define EEPROM_FRIDAY      17
#define EEPROM_SATURDAY    18
#define EEPROM_ZISE        19
#define EEPROM_MEMORY_SIZE 4
/*
  16 x memoria
    -n - memoria
  0 1n - habilitado principal
  1 1n - habilitado usuário
  2 1n - ultimo estado
  3 1n - rele
  4 4n - time on
  8 4n - time off
 12 1n - 1a
 13 1n - 2a
 14 1n - 3a
 15 1n - 4a
 16 1n - 5a
 17 1n - 6a
 18 1n - 7a
*/

#include <QMainWindow>
#include <QCompleter>

#include "atmodem.h"

namespace Color
{
  enum eColor
  {
    Preto,
    Vermelho,
    Azul
  };
}
using namespace Color;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  static bool CallReady;
  static bool TimeReady;
  static const char kSendSpacer[];
  static const char kSendSignalEvent[];
  static const char kSendSignalOtimoEvent[];
  static const char kSendSignalBomEvent[];
  static const char kSendSignalRuimEvent[];
  static const char kReceiveSetRtc[];
  static const char kReceiveRootNumberEnable[];
  static const char kReceiveRootNumberDisable[];
  static const char kReceiveRootNumberAddPhoneBook[];
  static const char kReceiveRootNumberDelPhoneBook[];
  static const char kReceiveMainReset[];
  static const char kReceiveMainEnable[];
  static const char kReceiveMainDisable[];
  static const char kSendSetRootPhoneBook[];
  static const char kSendClearRootPhoneBook[];
  static const char kSendPhoneBookAddEvent[];
  static const char kReceiveAddTimer[];
  static const char kReceiveMakeTimerOn[];
  static const char kReceiveMakeTimerOff[];
  static const char kReceiveReadTimer[];
  static const char kSendTimerReadEvent[];
  static const char kSendTimerReadUserEnabledEvent[];
  static const char kSendTimerReadGeneralEnabledEvent[];
  static const char kRootName[];
  static const char *pRootName;
  static void PhoneBookAddById ();
  static void SetRootPhoneBook ();
  static void ClearRootPhoneBook ();
  static void StateSetRootPhoneBook ();
  static void StateClearRootPhoneBook ();
  static void PhoneBookFindToSendEvent ();
  static void SmsSendAfterEvent ();
  static void StateDeleteSms ();
  static void RtcSet ();
  static void ResetPointers ();
  static char chTextSendAfterEvent[ 129 ];
  static char chMemoria[ 5 ];
  static char chRele[ 20 ];
  static char chTimeOn[ 20 ];
  static char chTimerOff[ 20 ];
  static char chSemana[ 20 ];
  //static const char *pSendMsg[ 4 ];
  static const char kSendTimerSetEvent[];
  static const char kSendEnableMainClearEvent[];
  static const char kSendEnableMainSetEvent[];
  static const char kSendResetEepromEvent[];
  static const char kSendRtcSetToEvent[];
  static const char kSendResetEvent[];
  static const char kSendPhoneBookFind[];
  static const char kSendTimerMakeOnEvent[];
  static const char kSendTimerMakeOffEvent[];
  static const char kSendTimerMakeErrorEvent[];






















  static eColor CorAtual;
  static char Debug[ kDefDebugSize ];
  static int DebugDataPointer;
  static bool DebugInProcess;

  static char Id[ 1024 ]; //novo
  static char IdAdd[ 1024 ]; //novo
  static char Clock[ 1024 ]; //novo
  static char Day[ 1024 ]; //novo
  static char User[ 1024 ]; //novo
  static char UserAdd[ 1024 ]; //novo
  static char Phone[ 1024 ]; //novo
  static char PhoneAdd[ 1024 ]; //novo
  static char Qualidade[ 1024 ]; //novo
  static char Status[ 1024 ]; //novo
  static char Text[ 1024 ]; //novo
  static char Telefone[ 1024 ]; //novo
  static char TimeZone[ 1024 ];

  static char SinPin[ 1024 ];
  static char SinNewPin[ 1024 ];
  static char Host[ 1024 ];
  static char Site[ 1024 ];
  static char Port[ 1024 ];
  static char Query[ 1024 ];
  static char IdConnect[ 1024 ];
  static char IdPassword[ 1024 ];
  static char UserPassword[ 1024 ];
  static char UserName[ 1024 ];
  static char SmsText[ 1024 ];
  static char SmsTelefon[ 1024 ];
  static char SmsId[ 1024 ];
  static char SmsTime[ 1024 ];
  static char SmsDate[ 1024 ];
  static char SmsUser[ 1024 ];
  static char SmsStatus[ 1024 ];
  static char CallNumber[ 1024 ];


  explicit MainWindow(QWidget *parent = 0);
  static void InternetData ();
  //void AppendSerialRx ( char achDado );
  static void StatusRecebido ( Event::eEvent aschStatus );
  static void DadoRecebido ( char achDado );
  static void DadoEnviado ( char achDado );
  static void OnEndProcess ();
  ~MainWindow();

private slots:
  void OpenSerialDialog();
  void ContarTempo ();

  void on_actionSair_triggered();

  void on_actionSerial_triggered();

  void on_pbSend_clicked();

  void on_btClear_clicked();

  void Loop ();

  void on_pbDebug_clicked();

  void on_actionGet_SIM_Status_triggered();

  void on_actionEnter_PIN_triggered();

  void on_actionGet_signal_quality_triggered();

  void on_actionChange_PIN_triggered();

  void on_actionLock_triggered();

  void on_actionPIN_Unlock_triggered();

  void on_actionUse_GET_method_to_connect_a_host_triggered();

  void on_actionDisconnect_triggered();

  void on_actionSend_triggered();

  void on_actionRead_by_id_triggered();

  void on_actionDelete_by_id_triggered();

  void on_actionRead_and_delete_by_id_triggered();

  void on_actionEcho_ON_triggered();

  void on_actionEcho_OFF_triggered();

  void on_actionPower_OFF_triggered();

  void on_actionCurrent_call_number_triggered();

  void on_actionDelete_by_status_DEL_READ_triggered();

  void on_actionDelete_by_status_DEL_UNREAD_triggered();

  void on_actionDelete_by_status_DEL_SENT_triggered();

  void on_actionDelete_by_status_DEL_UNSENT_triggered();

  void on_actionDelete_by_status_DEL_INBOX_triggered();

  void on_actionDelete_by_status_DEL_ALL_triggered();

  void on_actionRead_by_status_ALL_triggered();

  void on_actionRead_by_status_REC_READ_triggered();

  void on_actionRead_by_status_REC_UNREAD_triggered();

  void on_actionRead_by_status_STO_SEND_triggered();

  void on_actionRead_by_status_STO_UNSENT_triggered();

  void on_actionGet_Number_triggered();

  void on_actionCall_Number_triggered();

  void on_actionHang_Up_triggered();

  void on_actionAnswering_triggered();

  void on_actionDTMF_triggered();

  void on_leSend_returnPressed();

  void on_actionRead_triggered();

  void on_actionSet_triggered();

  void on_actionGet_GEO_data_GPS_Less_triggered();

  void on_actionAgenda_Adicionar_triggered();

  void on_actionAgenda_Adicionar_com_Id_triggered();

  void on_actionAgenda_Apagar_com_Id_triggered();

  void on_actionAgenda_Procurar_triggered();

protected:
  void showEvent( QShowEvent *ev );

private:
  static Ui::MainWindow *sui;
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
