#include "atmodem.h"
#include "stackenum.h"

bool AtModem::gblInternetConnect = false;

const char *AtModem::pOriginal;

const char *AtModem::pDataTxToModem[ 13 ];
const char *AtModem::pDataRxToModem[ 13 ];

char *AtModem::pDataList[ 20 ];

int AtModem::siDataListLine = 0;

int AtModem::siDataTxPointerLine = 0;
int AtModem::siDataRxPointerLine = 0;
int AtModem::siContentLength = 0;

char AtModem::schFlags = 0;

Action AtModem::OnEndProcess = '\0';
StatusModem AtModem::StatusEvent = '\0';
ExternalDataModem AtModem::DataReceivedEvent = '\0';
ExternalDataModem AtModem::DataSendEvent = '\0';

const char AtModem::kReceiveCallReady[] = { "Call Ready\r\n\0" };

char *AtModem::pchTmpValue = '\0';
char **AtModem::ppchTmpAddr = '\0';

const char AtModem::kSendEchoOff[] =  { "ATE0\r\n\0" };
const char AtModem::kSendEchoOn[] =  { "ATE1\r\n\0" };
const char AtModem::kReceiveOk[] = { "OK\r\n\0" };
const char AtModem::kReceiveError[] = { "ERROR\r\n\0" };
//const char AtModem::kReceiveCmeError[] = { "+CME ERROR\r\n\0" };

/*
SIM900.print("AT+CLIP=1\r"); // turn on caller ID notification
delay(100);
AT+COPS?\r\n
+COPS: 0,0,"Oi"\r\n
AT+CMGL="ALL"

AT+CPBS="SM"\r\n seleciona salvar no SIM
AT+CPBW=,"99268744",129,"Helmut Kemper"\r\n escreve na agenda - ok
AT+CPBF="hel"\r\n busca na agenda - ok
+CPBF: 1,"99268744",129,"Helmut Kemper"\r\n
para apagar, escreve o nome em branco;mantem o telefone e não deixa fazer busca
com vazio

+CLCC: 1,1,4,0,0,"08199268744",129,"Helmut Kemper"\r\n
+CLCC: 1,1,4,0,0,"08199268744",129,""\r\n


To send the actual DTMF code, you have to call this command for every digit sent.
To send, for instance "*1234#", you have to send:
AT+VTD=*;+VTD=1;+VTD=2;+VTD=3;+VTD=4;+VTD=#

+CMT: "+550310006052","","14/10/29,20:52:00-12"\r\nSaldo atual de bonus: R$8,11. Saldo recarga: R$18,44. Detalhe saldo recarga: *804. Outros saldos de bonus: *805.\r\n
*/

#if defined I_NEED_CALL_FUNCTIONS || defined I_NEED_USE_INTERNET_FUNCTIONS
  //usado em internet e sms
  const char AtModem::kReceiveSmsTextRedyToSend[]	= { "> " };
#endif

const char *AtModem::pError = &AtModem::kReceiveError[ 0 ];

eStep AtModem::EnumStep = Step::Stop;

int AtModem::siGenericCounter = 0;

AtModem::AtModem()
{

}

eEvent AtModem::EnumEvent = Event::None;

void AtModem::Init()
{
  AtModem::EnumEvent              = Event::None;

  AtModem::pchSmsNewOriginal      = AtModem::pchSmsNew;
  AtModem::pchCmtPhoneOriginal    = AtModem::pchCmtPhone;
  AtModem::pchCmtDayOriginal      = AtModem::pchCmtDay;
  AtModem::pchCmtTimeOriginal     = AtModem::pchCmtTime;
  AtModem::pchCmtMessageOriginal  = AtModem::pchCmtMessage;

  StackEnum::Reset();
}

void AtModem::FlagSet ( char achFlag )
{
  char lchFlag = 1 << achFlag;
  AtModem::schFlags |= lchFlag;
}

void AtModem::FlagClear ( char achFlag )
{
  char lchFlag = 1 << achFlag;
  lchFlag = ~lchFlag;
  AtModem::schFlags &= lchFlag;
}

bool AtModem::FlagTest ( char achFlag )
{
  char lchFlag = 1 << achFlag;
  lchFlag = AtModem::schFlags & lchFlag;

  if ( lchFlag == 0 )
  {
    return false;
  }

  return true;
}

void AtModem::ConstCharToChar ( const char *p1, char *p2 )
{
  if ( p1 == '\0' )
  {
    return;
  }

  do
  {
    *p2 = *p1;
    p1 ++;
    p2 ++;
    *p2 = '\0';
  }
  while ( *p1 != '\0' );
}

void AtModem::ConstCharToChar ( char *p1, char *p2 )
{
  if ( p1 == '\0' )
  {
    return;
  }

  do
  {
    *p2 = *p1;
    p1 ++;
    p2 ++;
    *p2 = '\0';
  }
  while ( *p1 != '\0' );
}

void AtModem::ResetPointers ()
{
  AtModem::siDataListLine = 0;
}

#ifdef I_NEED_PHONEBOOK_FUNCTIONS
  const char AtModem::kReceivePhoneBookFind[] = { "+CPBF: {inum},\"{snum}\",{inum},\"{str}\"\r\n" };
  const char *AtModem::pReceivePhoneBookFind = &AtModem::kReceivePhoneBookFind[ 0 ];
  const char AtModem::kSendPhoneBookClearId[] = { "AT+CPBW={pt},\"000000\",129,\"\"\r\n\0" };
  const char AtModem::kSendPhoneBookWriteId[] = { "AT+CPBW={pt},\"{pt}\",129,\"{pt}\"\r\n\0" };
  const char AtModem::kSendPhoneBookWrite[] = { "AT+CPBW=,\"{pt}\",129,\"{pt}\"\r\n\0" };
  const char AtModem::kSendPhoneBookFind[] = { "AT+CPBF=\"{pt}\"\r\n" };

  void AtModem::PhoneBookSet ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendPhoneBookWrite[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::PhoneBookIdSet ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendPhoneBookWriteId[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0'; //&AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::PhoneBookClearId ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendPhoneBookClearId[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::PhoneBookFind ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendPhoneBookFind[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }
#endif

#ifdef I_NEED_POWER_DOWN_FUNCTIONS
  const char AtModem::kSendPowerDown[] = { "AT+CPOWD=1\r\n\0" };
  const char AtModem::kReceivePowerOn[] = { (const char) 0x49, (const char) 0x49, (const char) 0x49, (const char) 0x49, (const char) 0xfe, (const char) 0xfe, (const char) 0xfe, (const char) 0xfe, '\0' };
  const char AtModem::kReceiveNormalPowerDown[] = { "\r\nNORMAL POWER DOWN\r\n\0" };

  const char *AtModem::pNormalPowerDown = &AtModem::kReceiveNormalPowerDown[ 0 ];
  const char *AtModem::pReceivePowerOn = &AtModem::kReceivePowerOn[ 0 ];
  void AtModem::PowerDown ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendPowerDown[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }
#endif

#ifdef I_NEED_SIM_PIN_FUNCTIONS
  const char AtModem::kSendSinPinLock[] = { "AT+CLCK=\"SC\",1,\"{pt}\",1\r\n\0" };
  const char AtModem::kSendSinPinChange[] = { "AT+CPWD=\"SC\",\"{pt}\",\"{pt}\"\r\n\0" };
  const char AtModem::kSendSinPinEnter[] = { "AT+CPIN=\"{pt}\"\r\n\0" };
  const char AtModem::kSendSinStatus[] =  { "AT+CPIN?\r\n\0" };
  const char AtModem::kSendSinPinUnlock[] = { "AT+CLCK=\"SC\",0,\"{pt}\",1\r\n\0" };

  const char AtModem::kReceiveSimReady[] = { "+CPIN: READY\r\n\0" };
  const char AtModem::kReceiveSimPin[] = { "+CPIN: SIM PIN\r\n\0" };
  const char AtModem::kReceiveSimPuk[] = { "+CPIN: SIM PUK\r\n\0" };
  const char AtModem::kReceiveSimPhPin[] = { "+CPIN: PH_SIM PIN\r\n\0" };
  const char AtModem::kReceiveSimPhPuk[] = { "+CPIN: PH_SIM PUK\r\n\0" };

  const char *AtModem::pReceiveSimReady = &AtModem::kReceiveSimReady[ 0 ];
  const char *AtModem::pReceiveSimPin = &AtModem::kReceiveSimPin[ 0 ];
  const char *AtModem::pReceiveSimPuk = &AtModem::kReceiveSimPuk[ 0 ];
  const char *AtModem::pReceiveSimPhPin = &AtModem::kReceiveSimPhPin[ 0 ];
  const char *AtModem::pReceiveSimPhPuk = &AtModem::kReceiveSimPhPuk[ 0 ];

  void AtModem::SimStatus ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendSinStatus[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::SimEnterPin ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendSinPinEnter[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::SimLockByPin ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendSinPinLock[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::SimUnlockByPin ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendSinPinUnlock[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::SimChangePin ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendSinPinChange[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }
#endif

#ifdef I_NEED_USE_INTERNET_FUNCTIONS
  const char AtModem::kReceiveDeactiveGprsDpdOk[] = { "SHUT OK\r\n\0" };
  const char AtModem::kReceiveConnectHost[] = { "CONNECT OK" };
  const char AtModem::kReceiveHeaderGetSend[] = { "SEND OK\r\n\0" };
  const char AtModem::kReceiveContentLength[] = { "Content-Length: \0" };
  const char AtModem::kReceiveClose[] = { "CLOSE\r\n\0" };
  const char AtModem::kReceiveClosed[] = { "CLOSED\r\n\0" };
  const char AtModem::kReceiveConnectionFailed1[] = { "CONNECTION FAILED\r\n\0" };
  const char AtModem::kReceiveConnectionFailed2[] = { "CONNECT FAIL\r\n\0" };
  const char AtModem::kReceiveOkEndMessage[] = { "\r\n\r\n\0" };

  const char *AtModem::pOkEndMessage = &AtModem::kReceiveOkEndMessage[ 0 ];
  const char *AtModem::pReceiveDeactiveGprsDpdOk = &AtModem::kReceiveDeactiveGprsDpdOk[ 0 ];
  const char *AtModem::pHeaderGetSend = &AtModem::kReceiveHeaderGetSend[ 0 ];
  const char *AtModem::pContentLength = &AtModem::kReceiveContentLength[ 0 ];
  const char *AtModem::pClose = &AtModem::kReceiveClose[ 0 ];
  const char *AtModem::pClosed = &AtModem::kReceiveClosed[ 0 ];
  const char *AtModem::pConnectionFailed1 = &AtModem::kReceiveConnectionFailed1[ 0 ];
  const char *AtModem::pConnectionFailed2 = &AtModem::kReceiveConnectionFailed2[ 0 ];

  void AtModem::DisconnectToHost ()
  {
    AtModem::gblInternetConnect = false;

    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendDeactiveGprsDpd[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveDeactiveGprsDpdOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::DisconnectAfterError ()
  {
    AtModem::gblInternetConnect = false;

    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendDeactiveGprsDpd[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }


/*
const char AtModem::kSendIpSingle[] = { "AT+CIPMUX=0\r\n\0" };
const char AtModem::kSendIpModeNormal[] = { "AT+CIPMODE=0\r\n\0" };
const char AtModem::kSendInternetConnect[] = { "AT+CGDCONT=1,\"IP\",\"{pt}\",\"0.0.0.0\",0,0\r\n\0" };
const char AtModem::kSendInternerConnectPassword[] = { "AT+CSTT=\"{pt}\",\"{pt}\",\"{pt}\"\r\n\0" };
const char AtModem::kSendDeactiveGprsDpd[] = { "AT+CIPSHUT\r\n\0" };
const char AtModem::kSendConnectHost[] = { "AT+CIPSTART=\"TCP\",\"{pt}\",\"{pt}\"\r\n\0" };
const char AtModem::kSendStartSendData[] = { "AT+CIPSEND\r\n\0" };
const char AtModem::kSendHeaderGetSend[] = { "GET {pt}{pt} HTTP/1.1\r\nHost: {pt}\r\nAccept: text/*;q=1\r\nUser-Agent: Arduino AtModem helmut.kemper@gmail.com Class\r\nAccept-Encoding: identity\r\n\r\n{bye}\0" };
*/
/*
AT+CENG?\r\n
\r\n
+CENG: 1,0\r\n
\r\n
+CENG:0,"0520,30,99,724,31,46,7e38,16,00,1aae,255"\r\n
+CENG:1,"0543,20,46,724,31,1aae"\r\n
+CENG:2,"0537,19,56,724,31,1aae"\r\n
+CENG:3,"0539,10,56,724,31,1aae"\r\n
+CENG:4,"0512,08,46,724,31,1aae"\r\n
+CENG:5,"0513,06,255,000,00,0"\r\n
+CENG:6,"0544,05,127,000,00,0"\r\n
\r\n
OK\r\n


POST /gsm/gsm-tracker.php HTTP/1.1
Host: cellphonetrackers.org
Content-Length: 418
Cache-Control: no-cache
Origin: chrome-extension://fhbjgbiflinjbdggehcddcbncdddomop
Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryrAAxRWlj5IViVI0O
User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/38.0.2125.111 Safari/537.36
Postman-Token: daa07698-548d-457e-5e51-4711bebdc46d
Accept: * / *
Accept-Encoding: gzip,deflate
Accept-Language: en-US,en;q=0.8,pt-BR;q=0.6,pt;q=0.4

------WebKitFormBoundaryrAAxRWlj5IViVI0O
Content-Disposition: form-data; name="mcc"

724
------WebKitFormBoundaryrAAxRWlj5IViVI0O
Content-Disposition: form-data; name="mnc"

31
------WebKitFormBoundaryrAAxRWlj5IViVI0O
Content-Disposition: form-data; name="lac"

6830
------WebKitFormBoundaryrAAxRWlj5IViVI0O
Content-Disposition: form-data; name="cid"

32312
------WebKitFormBoundaryrAAxRWlj5IViVI0O--




Lat=-8.11506 Lon=-34.89761

gprs.oi.br
gprs.oi.br
oi
oi
www.kemper.com.br
80
modem.php
?q=ola%20mundo
char *AtModem::pDataList[ 20 ];
*/

  const char AtModem::kSendIpSingle[] = { "AT+CIPMUX=0\r\n\0" };
  const char AtModem::kSendIpModeNormal[] = { "AT+CIPMODE=0\r\n\0" };
  const char AtModem::kSendInternetConnect[] = { "AT+CGDCONT=1,\"IP\",\"{pt}\",\"0.0.0.0\",0,0\r\n\0" };
  const char AtModem::kSendInternerConnectPassword[] = { "AT+CSTT=\"{pt}\",\"{pt}\",\"{pt}\"\r\n\0" };
  const char AtModem::kSendDeactiveGprsDpd[] = { "AT+CIPSHUT\r\n\0" };
  const char AtModem::kSendConnectHost[] = { "AT+CIPSTART=\"TCP\",\"{pt}\",\"{pt}\"\r\n\0" };
  const char AtModem::kSendStartSendData[] = { "AT+CIPSEND\r\n\0" };
  //const char AtModem::kSendHeaderGetSend[] = { "GET /server.php HTTP/1.1\r\nHost: rfid.elasticbeanstalk.com\r\nCache-Control: no-cache\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/38.0.2125.111 Safari/537.36\r\nPostman-Token: 85407953-229a-f42e-5113-4148cae3e736\r\nAccept: */*\r\nAccept-Encoding: deflate\r\nAccept-Language: en;q=1\r\n\r\n{bye}\0" };
  const char AtModem::kSendHeaderGetSend[] = { "GET {pt}{pt} HTTP/1.1\r\nHost: {pt}\r\nAccept: text/*;q=1\r\nUser-Agent: Arduino AtModem helmut.kemper@gmail.com Class\r\nAccept-Encoding: identity\r\n\r\n{bye}\0" };
  //const char AtModem::kSendHeaderGetSend[] = { "POST /gsm/gsm-tracker.php HTTP/1.1\r\nHost: cellphonetrackers.org\r\nContent-Length: 233\r\nCache-Control: no-cache\r\nContent-Type: multipart/form-data; boundary=X\r\nUser-Agent: Arduino AtModem helmut.kemper@gmail.com Class\r\nAccept: */*\r\nAccept-Encoding: deflate\r\nAccept-Language: en-US,en;q=0.8,pt-BR;q=0.6,pt;q=0.4\r\n\r\n--X\r\nContent-Disposition: form-data; name=\"mcc\"\r\n\r\n724\r\n--X\r\nContent-Disposition: form-data; name=\"mnc\"\r\n\r\n31\r\n--X\r\nContent-Disposition: form-data; name=\"lac\"\r\n\r\n6830\r\n--X\r\nContent-Disposition: form-data; name=\"cid\"\r\n\r\n32312\r\n--X--\r\n{bye}\0" };
  void AtModem::SendDataByGet ()
  {
    AtModem::gblInternetConnect = true;

    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendIpSingle[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = &AtModem::kSendIpModeNormal[ 0 ];
    AtModem::pDataRxToModem[ 1 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 2 ] = &AtModem::kSendInternetConnect[ 0 ];
    AtModem::pDataRxToModem[ 2 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 3 ] = &AtModem::kSendInternerConnectPassword[ 0 ];
    AtModem::pDataRxToModem[ 3 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 4 ] = &AtModem::kSendDeactiveGprsDpd[ 0 ];
    AtModem::pDataRxToModem[ 4 ] = &AtModem::kReceiveDeactiveGprsDpdOk[ 0 ];

    AtModem::pDataTxToModem[ 5 ] = &AtModem::kSendConnectHost[ 0 ];
    AtModem::pDataRxToModem[ 5 ] = &AtModem::kReceiveConnectHost[ 0 ];

    AtModem::pDataTxToModem[ 6 ] = &AtModem::kSendStartSendData[ 0 ];
    AtModem::pDataRxToModem[ 6 ] = &AtModem::kReceiveSmsTextRedyToSend[ 0 ];

    AtModem::pDataTxToModem[ 7 ] = &AtModem::kSendHeaderGetSend[ 0 ];
    AtModem::pDataRxToModem[ 7 ] = &AtModem::kReceiveHeaderGetSend[ 0 ];

    AtModem::pDataTxToModem[ 8 ] = '\0';
    AtModem::pDataRxToModem[ 8 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }
#endif

#ifdef I_NEED_SMS_FUNCTIONS
  const char AtModem::kSendSmsTextMode[] = { "AT+CMGF=1\r\n\0" };
  const char AtModem::kSendSmsSendConfig[] = { "AT+CMGS=\"{pt}\"\r\n\0" };
  const char AtModem::kSendSmsSendText[] = { "{pt}{bye}\0" };
  const char AtModem::kSendSmsReadMessageId[] = { "AT+CMGR={pt}\r\n\0" };
  const char AtModem::kSendSmsReadMessageStatus[] = { "AT+CMGL=\"{pt}\"\r\n\0" };
  const char AtModem::kSendSmsDeleteMessageId[] = { "AT+CMGD={pt}\r\n\0" };
  const char AtModem::kSendSmsDeleteMessageStatus[] = { "AT+CMGDA=\"{pt}\"\r\n\0" };
  const char AtModem::kSendSmsAdvancedMode[] = { "AT+CNMI=2,1,0,0,0\r\n\0" };

  char *AtModem::pchSmsNew = '\0';
  char *AtModem::pchSmsNewOriginal = '\0';
  char *AtModem::pchCmtPhone = '\0';
  char *AtModem::pchCmtPhoneOriginal = '\0';
  char *AtModem::pchCmtDay = '\0';
  char *AtModem::pchCmtDayOriginal = '\0';
  char *AtModem::pchCmtTime = '\0';
  char *AtModem::pchCmtTimeOriginal = '\0';
  char *AtModem::pchCmtMessage = '\0';
  char *AtModem::pchCmtMessageOriginal = '\0';

  //+CMGL: 1,"REC READ","+558183317942","","14/10/29,20:20:49-08"\r\n
  const char AtModem::kReceiveCmgl[] = { "+CMGL: {num},\"{str}\",\"{snum}\",\"{str}\",\"{time},{time}{inum}\"\r\n{all}\0" };
  //+CMGR: "REC UNREAD","+558183317942","","14/10/29,16:47:37-08"\r\n
  //+CMT: "+558183317942","","14/10/29,17:37:14-08"\r\n
  //{time}{inum}{snum}{hex}{num}{str}
  const char AtModem::kReceiveCmgr[] = { "+CMGR: \"{str}\",\"{snum}\",\"{str}\",\"{time},{time}{snum}\"\r\n{all}\0" };

  //+CMT: "+550310006052","","14/10/29,20:52:00-12"\r\n
  //Saldo atual de bonus: R$8,11. Saldo recarga: R$18,44. Detalhe saldo recarga: *804. Outros saldos de bonus: *805.\r\n
  //+CMT: "+550310006052","","14/10/29,22:55:08-08"\r\n
  //Saldo atual recarga: R$17,21 valido ate 08/01/15. Detalhe saldo recarga: *804. Outros saldos de bonus: *805.\r\n
  //+CMT: "+550310006052","","14/10/29,22:55:08-08"\r\nSaldo atual recarga: R$17,21 valido ate 08/01/15. Detalhe saldo recarga: *804. Outros saldos de bonus: *805.\r\n
  const char AtModem::kReceiveCmt[] = { "+CMT: \"{pPHO}\",\"{istr}\",\"{pDAY},{pTME}{inum}\"\r\n{pMSG}\0" };

  const char AtModem::kReceiveCmti[] = { "+CMTI: \"SM\",{pSMS}\0" };
  const char *AtModem::pReceiveCmt = &AtModem::kReceiveCmt[ 0 ];
  const char *AtModem::pCmti = &AtModem::kReceiveCmti[ 0 ];
  const char *AtModem::pCmgl = &AtModem::kReceiveCmgl[ 0 ];
  const char *AtModem::pCmgr = &AtModem::kReceiveCmgr[ 0 ];

  void AtModem::SmsSend ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendEchoOff[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = &AtModem::kSendSmsTextMode[ 0 ];
    AtModem::pDataRxToModem[ 1 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 2 ] = &AtModem::kSendSmsSendConfig[ 0 ];
    AtModem::pDataRxToModem[ 2 ] = &AtModem::kReceiveSmsTextRedyToSend[ 0 ];

    AtModem::pDataTxToModem[ 3 ] = &AtModem::kSendSmsSendText[ 0 ];
    AtModem::pDataRxToModem[ 3 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 4 ] = '\0';
    AtModem::pDataRxToModem[ 4 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::SmsReadAndDeleteById ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendEchoOff[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = &AtModem::kSendSmsTextMode[ 0 ];
    AtModem::pDataRxToModem[ 1 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 2 ] = &AtModem::kSendSmsReadMessageId[ 0 ];
    AtModem::pDataRxToModem[ 2 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 3 ] = &AtModem::kSendSmsDeleteMessageId[ 0 ];
    AtModem::pDataRxToModem[ 3 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 4 ] = '\0';
    AtModem::pDataRxToModem[ 4 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::SmsReadById ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendEchoOff[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = &AtModem::kSendSmsTextMode[ 0 ];
    AtModem::pDataRxToModem[ 1 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 2 ] = &AtModem::kSendSmsReadMessageId[ 0 ];
    AtModem::pDataRxToModem[ 2 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 3 ] = '\0';
    AtModem::pDataRxToModem[ 3 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::SmsReadByStatus ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendEchoOff[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = &AtModem::kSendSmsTextMode[ 0 ];
    AtModem::pDataRxToModem[ 1 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 2 ] = &AtModem::kSendSmsReadMessageStatus[ 0 ];
    AtModem::pDataRxToModem[ 2 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 3 ] = '\0';
    AtModem::pDataRxToModem[ 3 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::SmsDeleteById ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendEchoOff[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = &AtModem::kSendSmsTextMode[ 0 ];
    AtModem::pDataRxToModem[ 1 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 2 ] = &AtModem::kSendSmsDeleteMessageId[ 0 ];
    AtModem::pDataRxToModem[ 2 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 3 ] = '\0';
    AtModem::pDataRxToModem[ 3 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::SmsDeleteByStatus ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendEchoOff[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = &AtModem::kSendSmsTextMode[ 0 ];
    AtModem::pDataRxToModem[ 1 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 2 ] = &AtModem::kSendSmsDeleteMessageStatus[ 0 ];
    AtModem::pDataRxToModem[ 2 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 3 ] = '\0';
    AtModem::pDataRxToModem[ 3 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }
#endif

#ifdef I_NEED_POWER_DOWN_FUNCTIONS
  void AtModem::OnModemPowerOn ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendEchoOff[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = &AtModem::kSendSmsAdvancedMode[ 0 ];
    AtModem::pDataRxToModem[ 1 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 2 ] = &AtModem::kSendSmsTextMode[ 0 ];
    AtModem::pDataRxToModem[ 2 ] = &AtModem::kReceiveOk[ 0 ];

    #ifdef I_NEED_GEO_FUNCTIONS
      AtModem::pDataTxToModem[ 3 ] = &AtModem::kSendEnginneringModeOn[ 0 ];
      AtModem::pDataRxToModem[ 3 ] = &AtModem::kReceiveOk[ 0 ];

      AtModem::pDataTxToModem[ 4 ] = '\0';
      AtModem::pDataRxToModem[ 4 ] = '\0';
    #else
      AtModem::pDataTxToModem[ 3 ] = '\0';
      AtModem::pDataRxToModem[ 3 ] = '\0';
    #endif

    AtModem::StateMachineResetAndRun ();
  }
#endif

#ifdef I_NEED_GEO_FUNCTIONS
  const char AtModem::kSendEnginneringModeOn[] = { "AT+CENG=1\r\n\0" };
  const char AtModem::kSendEnginneringGet[] = { "AT+CENG?\r\n\0" };
  //?mcc=724&mnc=31&lac=6830&cid=32312
  //<cell>"<arfen>,<rxl>,<rxq>,<mcc>,<mnc>,<bsic>,<cellid>,<rla>,<txp>,<lac>,<TA>
  //<cell>"{inum},{inum},{inum},{hex},{hex},{inum},{hex},{inum},{inum},{hex}\0
  //+CENG:0,"0520,30,99,724,31,46,7e38,16,00,1aae,255"\r\n
  const char AtModem::kReceiveEnginneringModeData[] = { "+CENG:0,\"{inum},{inum},{inum},{mcc},{mncc},{inum},{celid},{inum},{inum},{lac}\0" };
  const char *AtModem::pReceiveEnginneringModeData = &AtModem::kReceiveEnginneringModeData[ 0 ];

  void AtModem::GetEnginneringData ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendEnginneringGet[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }
#endif

#ifdef I_NEED_CALL_FUNCTIONS
  const char AtModem::kSendDialNumberInVoiceMode[] = { "ATD{pt};\r\n\0" };
  const char AtModem::kSendHangUpInVoiceMode[] = { "ATH\r\n\0" };
  const char AtModem::kSendAnsweringInVoiceMode[] = { "ATA\r\n\0" };
  const char AtModem::kReceiveRingString[] = { "RING\r\n\0" };
  const char AtModem::kReceiveNoCarrier[] = { "NO CARRIER\r\n\0" };
  const char AtModem::kReceiveNoDialTone1[] = { "NO DIALTONE\r\n\0" };
  const char AtModem::kReceiveNoDialTone2[] = { "NO DIAL TONE\r\n\0" };
  const char AtModem::kReceiveNoAnswer[] = { "NO ANSWER\r\n\0" };
  const char AtModem::kReceiveBusy[] = { "BUSY\r\n\0" };
  //Numero da pessoa que está ligando
  const char AtModem::kSendCarrierNumber[] = { "AT+CLCC\r\n\0" };
  //+CLCC: 1,1,4,0,0,"08199268744",129,""\r\n

  //"+CLCC: %i,%N,%N,%N,%N,\"%t\",%N,\"%u\0"
  const char AtModem::kReceiveCarrierNumber[] = { "+CLCC: {num},{inum},{inum},{inum},{inum},\"{snum}\",{inum},\"{str}\0" };
  const char *AtModem::pCarrierNumber = &AtModem::kReceiveCarrierNumber[ 0 ];

  const char *AtModem::pRingString = &AtModem::kReceiveRingString[ 0 ];
  const char *AtModem::pCallReady = &AtModem::kReceiveCallReady[ 0 ];
  const char *AtModem::pNoCarrier = &AtModem::kReceiveNoCarrier[ 0 ];
  const char *AtModem::pNoDialTone1 = &AtModem::kReceiveNoDialTone1[ 0 ];
  const char *AtModem::pNoDialTone2 = &AtModem::kReceiveNoDialTone2[ 0 ];
  const char *AtModem::pNoAnswer = &AtModem::kReceiveNoAnswer[ 0 ];
  const char *AtModem::pBusy = &AtModem::kReceiveBusy[ 0 ];
  void AtModem::CallDial ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendDialNumberInVoiceMode[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::CallHangUp ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendHangUpInVoiceMode[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::CallAnswering ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendAnsweringInVoiceMode[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::CallGetNumber ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendCarrierNumber[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }
#endif

#ifdef I_NEED_QUALITY_FUNCTIONS
  //+CSQ: 21,0\r\n
  const char AtModem::kReceiveSignalQuality[] = { "+CSQ: {num}\0" };
  const char AtModem::kSendSignalQuality[] = { "AT+CSQ\r\n\0" };
  const char *AtModem::pSignalQuality = &AtModem::kReceiveSignalQuality[ 0 ];
  void AtModem::SignalQuality ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendSignalQuality[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = '\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }
#endif

#ifdef I_NEED_RTC_FUNCTIONS
  const char AtModem::kSendCclk[] = { "AT+CCLK?\r\n\0" };

  const char *AtModem::pSendRtc = &AtModem::kSendRtc[ 0 ];

  //AT+CCLK ="12/12/26,15:04:50+08"
  const char AtModem::kSendRtc[] = { "AT+CCLK =\"{pt},{pt}{pt}\"\r\n\0" };

  //+CCLK: "00/01/01,03:58:08+00"\r\n
  const char AtModem::kReceiveCclk[] = { "+CCLK: \"{time},{time}{snum}\0" };
  const char *AtModem::pCclk = &AtModem::kReceiveCclk[ 0 ];

  void AtModem::RtcSet ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendRtc[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ]; //'\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }

  void AtModem::RtcGet ()
  {
    AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendCclk[ 0 ];
    AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ]; //'\0';

    AtModem::pDataTxToModem[ 1 ] = '\0';
    AtModem::pDataRxToModem[ 1 ] = '\0';

    AtModem::StateMachineResetAndRun ();
  }
#endif

void AtModem::EchoOff ()
{
  AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendEchoOff[ 0 ];
  AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

  AtModem::pDataTxToModem[ 1 ] = '\0';
  AtModem::pDataRxToModem[ 1 ] = '\0';

  AtModem::StateMachineResetAndRun ();
}

void AtModem::EchoOn ()
{
  AtModem::pDataTxToModem[ 0 ] = &AtModem::kSendEchoOn[ 0 ];
  AtModem::pDataRxToModem[ 0 ] = &AtModem::kReceiveOk[ 0 ];

  AtModem::pDataTxToModem[ 1 ] = '\0';
  AtModem::pDataRxToModem[ 1 ] = '\0';

  AtModem::StateMachineResetAndRun ();
}

void AtModem::StateMachineResetAndRun ()
{
  AtModem::siDataListLine = 0;

  AtModem::siDataTxPointerLine = 0;
  AtModem::siDataRxPointerLine = 0;

  AtModem::FlagClear( kDefFlagWaiting );
  AtModem::FlagClear( kDefFlagNextStep );

  AtModem::FlagSet( kDefFlagRuning );
}

void AtModem::StateMachineRun ()
{
  if ( AtModem::FlagTest( kDefFlagRuning ) == true )
  {
    if ( AtModem::FlagTest( kDefFlagWaiting ) == false )
    {
      AtModem::StateMachine ();
    }
  }

  if ( AtModem::FlagTest( kDefFlagProcessEnd ) == true )
  {
    AtModem::FlagClear( kDefFlagProcessEnd );
    if ( AtModem::OnEndProcess != '\0' )
    {
      AtModem::OnEndProcess ();
    }
  }
}

/**
 * @brief AtModem::StateMachine 'Comandos' de envio:
 * {pt}  - Ponteiro de onde os dados estão
 * {bye} - Envia o byte 'bye' ( 0x1A ) ao fim da transmissão de dados
 */
void AtModem::StateMachine ()
{
  char lchDataToSend;
  char *lchpUserData = '\0';

  while ( true )
  {
    lchDataToSend = *AtModem::pDataTxToModem[ AtModem::siDataTxPointerLine ];

    if ( lchDataToSend == '\0' )
    {
      AtModem::siDataTxPointerLine ++;

      //if ( ( AtModem::pDataTxToModem[ AtModem::siDataTxPointerLine ] == '\0' ) && ( AtModem::pDataRxToModem[ AtModem::siDataTxPointerLine ] == '\0' ) )
      if ( AtModem::pDataTxToModem[ AtModem::siDataTxPointerLine ] == '\0' )
      {
        StackEnum::Add( Event::EndProcess );
        AtModem::FlagClear( kDefFlagRuning );
        return;
      }

      else
      {
        AtModem::FlagSet( kDefFlagWaiting );
        return;
      }
    }

    else
    {
      AtModem::pDataTxToModem[ AtModem::siDataTxPointerLine ] ++;
    }

    if ( ( lchDataToSend == '{' ) && ( *AtModem::pDataTxToModem[ AtModem::siDataTxPointerLine ] == 'p' ) && ( *( AtModem::pDataTxToModem[ AtModem::siDataTxPointerLine ] + 1 ) == 't' ) )
    {
      AtModem::pDataTxToModem[ AtModem::siDataTxPointerLine ] += 3;
      lchpUserData = AtModem::pDataList[ AtModem::siDataListLine++ ];
    }

    else if ( ( lchDataToSend == '{' ) && ( *AtModem::pDataTxToModem[ AtModem::siDataTxPointerLine ] == 'b' ) && ( *( AtModem::pDataTxToModem[ AtModem::siDataTxPointerLine ] + 1 ) == 'y' ) && ( *( AtModem::pDataTxToModem[ AtModem::siDataTxPointerLine ] + 2 ) == 'e' ) )
    {
      AtModem::pDataTxToModem[ AtModem::siDataTxPointerLine ] += 4;
      lchDataToSend = char( 0x1A );
    }

    if ( lchpUserData != '\0' )
    {
      while ( *lchpUserData != '\0' )
      {
        AtModem::DataSendEvent ( *lchpUserData );
        lchpUserData ++;
      }
      lchpUserData = '\0';
    }

    else if ( AtModem::DataSendEvent != '\0' )
    {
      AtModem::DataSendEvent ( lchDataToSend );
    }
  }
}

/**
 * @brief AtModem::DayOfWeek Retorna o dia da semana de uma determinada data.
 * @param apchDay pchar - Data no formato [0-9]{2}.[0-9]{2}.[0-9]{2}
 * @return char - 1, Domingo; 2, Segunda-feira; 3, Terça-feira; ... 7, Sábado
 */
char AtModem::DayOfWeek ( char * apchDay )
{
  char lchDayOfWeel[ 7 ] = { '1', '2', '3', '4', '5', '6', '7' };
  int lsiYear, lsiMonth, lsiDay;
  int a, y, m, d;

  lsiYear = ( *apchDay - '0' ) * 10;
  apchDay ++;
  lsiYear += ( *apchDay - '0' );
  apchDay += 2;

  lsiMonth = ( *apchDay - '0' ) * 10;
  apchDay ++;
  lsiMonth += ( *apchDay - '0' );
  apchDay += 2;

  lsiDay = ( *apchDay - '0' ) * 10;
  apchDay ++;
  lsiDay += ( *apchDay - '0' );

  a = ( 14 - lsiMonth ) / 12;
  y = lsiYear - a;
  m = lsiMonth + 12 * a - 2;
  d = ( lsiDay + y + y / 4 - y / 100 + y / 400 + ( 31 * m / 12 ) ) % 7;
  //d = ( ( 1491 * y + 3100 * m + 1200 * lsiDay ) / 1200 ) % 7;

  return lchDayOfWeel[ d ];
}

void AtModem::OnEvent ( eEvent aenEvent )
{
  switch ( aenEvent )
  {
    case Event::EndProcess:
      break;

    #ifdef I_NEED_USE_INTERNET_FUNCTIONS
      case Event::Close:
        if ( AtModem::FlagTest( kDefFlagInternetGet ) == true )
        {
          AtModem::DisconnectToHost ();
        }
        AtModem::FlagClear( kDefFlagInternetGet );
        break;

      #ifdef ENABLE_AUTO_INTERNET_DISCONECT
        case Event::InternetReadEnd:
          AtModem::DisconnectToHost ();
          break;
      #endif

      #ifdef ENABLE_AUTO_INTERNET_DISCONECT_AFTER_ERROR
        case Event::Error:
        case Event::ConnectionFailed:
          if ( AtModem::gblInternetConnect == true )
          {
            AtModem::DisconnectAfterError ();
          }
          break;
      #endif
    #endif
  }

  if ( AtModem::StatusEvent != '\0' )
  {
    AtModem::StatusEvent ( aenEvent );
  }

  return;


  switch ( aenEvent )
  {
    case Event::EndProcess:
      if ( AtModem::pchTmpValue != '\0' )
      {
        AtModem::PointReturnAfterSecuryCopy ();
      }
      break;

    #ifdef I_NEED_POWER_DOWN_FUNCTIONS
      #ifdef ENABLE_AUTO_POWER_ON_COMMANDS
      case Event::CallReady:
        AtModem::OnModemPowerOn();
        break;
      #endif
    #endif
  }
}

void AtModem::PontSecuryCopy ( char **pchOriginal, char **pchNew )
{
  AtModem::pchTmpValue = *pchOriginal;
  AtModem::ppchTmpAddr = pchOriginal;

  *pchOriginal = *pchNew;
}

void AtModem::PointReturnAfterSecuryCopy ()
{
  *AtModem::ppchTmpAddr = AtModem::pchTmpValue;
  AtModem::ppchTmpAddr = '\0';
  AtModem::pchTmpValue = '\0';
}

void AtModem::Checker ( const char *apcchPointer, char *apchRx, Event::eEvent e )
{
  const char **p = &apcchPointer;
  AtModem::pOriginal = *p;
  do
  {
    if ( AtModem::__GetTest ( p, apcchPointer, *apchRx, e ) == false )
    {
      *p = AtModem::pOriginal;
    }

    apchRx += 1;
  }
  while ( *apchRx != '\0' );
  AtModem::__GetTest ( p, apcchPointer, *apchRx, e );
}

/**
 * @brief AtModem::__GetTest
 * {time} - Captura data/hora, formato: [0-9]{1,}[:/][0-9]{1,}[0-9]{1,}[:/]
 * {inum} - Ignora número, formato: [^0-9]{1,}
 * {snum} - Captura número, formato: [0-9+-]{1,}
 * {num}  - Captura número, formato: [0-9]{1,}
 * {hex}  - Captura número, formato: [0-9a-fA-F]{1,}
 * {str}  - Captura texto, formato: [0-9a-z(sp)]{1,}
 * {istr} - Ignora texto, formato: [^0-9a-z(sp)]{1,}
 * {all}  - Captura tudo, formato: [^\r\n\0]
 * @param apcchPointer
 * @param apcchPointerStart
 * @param achRx
 * @param e
 * @return
 */
bool AtModem::__GetTest ( const char **apcchPointer, const char *apcchPointerStart, char achRx, Event::eEvent e )
{
  restart_process:
  if ( **apcchPointer == '{' )
  {
    if ( ( *( ( *apcchPointer ) + 1 ) == 't' ) && ( *( ( *apcchPointer ) + 2 ) == 'i' ) && ( *( ( *apcchPointer ) + 3 ) == 'm' ) && ( *( ( *apcchPointer ) + 4 ) == 'e' ) )
    {
      if ( AtModem::pDataList[ AtModem::siDataListLine ] != '\0' )
      {
        if ( ( ( achRx >= '0' ) && ( achRx <= '9' ) ) || ( achRx == ':' ) || ( achRx == '/' ) )
        {
          *AtModem::pDataList[ AtModem::siDataListLine ] = achRx;
          AtModem::pDataList[ AtModem::siDataListLine ] ++;
          *AtModem::pDataList[ AtModem::siDataListLine ] = '\0';
          return true;
        }

        AtModem::siDataListLine ++;
      }

      else
      {
        StackEnum::Add( Event::PTimeError );
        goto reset_pointers;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 6;
    }

    /*//(dec)siMcc, (dec)siMncc, (hex)siCelid, (hex)siLac;

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'm' ) && ( *( ( *apcchPointer ) + 2 ) == 'c' ) && ( *( ( *apcchPointer ) + 3 ) == 'c' ) )
    {
      if ( ( achRx >= '0' ) && ( achRx <= '9' ) )
      {
        *AtModem::pMcc = achRx;
        AtModem::pMcc ++;
        *AtModem::pMcc = '\0';
        return true;
      }

      pMcc = &chMcc[ 0 ];
      ( *apcchPointer ) = ( *apcchPointer ) + 6;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'm' ) && ( *( ( *apcchPointer ) + 2 ) == 'n' ) && ( *( ( *apcchPointer ) + 3 ) == 'c' ) && ( *( ( *apcchPointer ) + 4 ) == 'c' ) )
    {
      if ( ( achRx >= '0' ) && ( achRx <= '9' ) )
      {
        *AtModem::pMncc = achRx;
        AtModem::pMncc ++;
        *AtModem::pMncc = '\0';
        return true;
      }

      pMncc = &chMncc[ 0 ];
      ( *apcchPointer ) = ( *apcchPointer ) + 6;
    }//(hex)siCelid, (hex)siLac;

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'c' ) && ( *( ( *apcchPointer ) + 2 ) == 'e' ) && ( *( ( *apcchPointer ) + 3 ) == 'l' ) && ( *( ( *apcchPointer ) + 4 ) == 'i' ) && ( *( ( *apcchPointer ) + 5 ) == 'd' ) )
    {
      if ( ( achRx >= '0' ) && ( achRx <= '9' ) )
      {
        AtModem::siCelid *= 16;
        AtModem::siCelid += ( achRx - '0' );
        return true;
      }

      else if ( ( achRx >= 'a' ) && ( achRx <= 'f' ) )
      {
        AtModem::siCelid *= 16;
        AtModem::siCelid += ( achRx - 'a' );
        return true;
      }

      else if ( ( achRx >= 'A' ) && ( achRx <= 'F' ) )
      {
        AtModem::siCelid *= 16;
        AtModem::siCelid += ( achRx - 'A' );
        return true;
      }

      AtModem::siCounter = 0;
      do
      {
        AtModem::siCounter ++;
        *AtModem::pCelid = ( AtModem::siCelid % 10 ) + '0';
        AtModem::siCelid /= 10;
        AtModem::pCelid --;
      }
      while ( AtModem::siCelid > 0 );

      AtModem::pchGeneric = &AtModem::chCelid[ 0 ];
      //  ^12345\0
      //123456789
      //987654321
      while ( AtModem::siCounter > 0 )
      {
        AtModem::pCelid ++;
        *AtModem::pchGeneric = *AtModem::pCelid;
        AtModem::pchGeneric ++;
        AtModem::siCounter ++;
      }


      ( *apcchPointer ) = ( *apcchPointer ) + 7;
    }*/

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'i' ) && ( *( ( *apcchPointer ) + 2 ) == 'n' ) && ( *( ( *apcchPointer ) + 3 ) == 'u' ) && ( *( ( *apcchPointer ) + 4 ) == 'm' ) )
    {
      if ( ( ( achRx >= '0' ) && ( achRx <= '9' ) ) || ( achRx == '+' ) || ( achRx == '-' ) )
      {
        return true;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 6;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 's' ) && ( *( ( *apcchPointer ) + 2 ) == 'n' ) && ( *( ( *apcchPointer ) + 3 ) == 'u' ) && ( *( ( *apcchPointer ) + 4 ) == 'm' ) )
    {
      if ( AtModem::pDataList[ AtModem::siDataListLine ] != '\0' )
      {
        if ( ( ( achRx >= '0' ) && ( achRx <= '9' ) ) || ( achRx == '+' ) || ( achRx == '-' ) )
        {
          *AtModem::pDataList[ AtModem::siDataListLine ] = achRx;
          AtModem::pDataList[ AtModem::siDataListLine ] ++;
          *AtModem::pDataList[ AtModem::siDataListLine ] = '\0';
          return true;
        }

        AtModem::siDataListLine ++;
      }

      else
      {
        StackEnum::Add( Event::PSNumError );
        goto reset_pointers;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 6;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'h' ) && ( *( ( *apcchPointer ) + 2 ) == 'e' ) && ( *( ( *apcchPointer ) + 3 ) == 'x' ) )
    {
      if ( AtModem::pDataList[ AtModem::siDataListLine ] != '\0' )
      {
        if ( ( ( achRx >= '0' ) && ( achRx <= '9' ) ) || ( ( achRx >= 'a' ) && ( achRx <= 'f' ) ) || ( ( achRx >= 'A' ) && ( achRx <= 'F' ) ) )
        {
          *AtModem::pDataList[ AtModem::siDataListLine ] = achRx;
          AtModem::pDataList[ AtModem::siDataListLine ] ++;
          *AtModem::pDataList[ AtModem::siDataListLine ] = '\0';
          return true;
        }

        AtModem::siDataListLine ++;
      }

      else
      {
        StackEnum::Add( Event::PSHexError );
        goto reset_pointers;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 5;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'n' ) && ( *( ( *apcchPointer ) + 2 ) == 'u' ) && ( *( ( *apcchPointer ) + 3 ) == 'm' ) )
    {
      if ( AtModem::pDataList[ AtModem::siDataListLine ] != '\0' )
      {
        if ( ( achRx >= '0' ) && ( achRx <= '9' ) )
        {
          *AtModem::pDataList[ AtModem::siDataListLine ] = achRx;
          AtModem::pDataList[ AtModem::siDataListLine ] ++;
          *AtModem::pDataList[ AtModem::siDataListLine ] = '\0';
          return true;
        }

        AtModem::siDataListLine ++;
      }

      else
      {
        StackEnum::Add( Event::PNumError );
        goto reset_pointers;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 5;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 's' ) && ( *( ( *apcchPointer ) + 2 ) == 't' ) && ( *( ( *apcchPointer ) + 3 ) == 'r' ) )
    {
      if ( AtModem::pDataList[ AtModem::siDataListLine ] != '\0' )
      {
        if ( ( ( achRx >= '0' ) && ( achRx <= '9' ) ) || ( ( achRx >= 'A' ) && ( achRx <= 'Z' ) ) || ( ( achRx >= 'a' ) && ( achRx <= 'z' ) ) || ( achRx == ' ' ) )
        {
          *AtModem::pDataList[ AtModem::siDataListLine ] = achRx;
          AtModem::pDataList[ AtModem::siDataListLine ] ++;
          *AtModem::pDataList[ AtModem::siDataListLine ] = '\0';
          return true;
        }

        AtModem::siDataListLine ++;
      }

      else
      {
        StackEnum::Add( Event::PStrError );
        goto reset_pointers;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 5;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'i' ) && ( *( ( *apcchPointer ) + 2 ) == 's' ) && ( *( ( *apcchPointer ) + 3 ) == 't' ) && ( *( ( *apcchPointer ) + 4 ) == 'r' ) )
    {
      if ( ( ( achRx >= '0' ) && ( achRx <= '9' ) ) || ( ( achRx >= 'A' ) && ( achRx <= 'Z' ) ) || ( ( achRx >= 'a' ) && ( achRx <= 'z' ) ) || ( achRx == ' ' ) )
      {
        return true;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 6;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'a' ) && ( *( ( *apcchPointer ) + 2 ) == 'l' ) && ( *( ( *apcchPointer ) + 3 ) == 'l' ) )
    {
      if ( AtModem::pDataList[ AtModem::siDataListLine ] != '\0' )
      {
        if ( ( achRx != '\r' ) && ( achRx != '\n' ) && ( achRx != '\0' ) )
        {
          *AtModem::pDataList[ AtModem::siDataListLine ] = achRx;
          AtModem::pDataList[ AtModem::siDataListLine ] ++;
          *AtModem::pDataList[ AtModem::siDataListLine ] = '\0';
          return true;
        }

        AtModem::siDataListLine ++;
      }

      else
      {
        StackEnum::Add( Event::PAllError );
        goto reset_pointers;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 5;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'p' ) && ( *( ( *apcchPointer ) + 2 ) == 'S' ) && ( *( ( *apcchPointer ) + 3 ) == 'M' ) && ( *( ( *apcchPointer ) + 4 ) == 'S' ) )
    {
      if ( AtModem::pchSmsNew != '\0' )
      {
        if ( ( achRx >= '0' ) && ( achRx <= '9' ) )
        {
          *AtModem::pchSmsNew = achRx;
          AtModem::pchSmsNew ++;
          *AtModem::pchSmsNew = '\0';
          return true;
        }

        AtModem::pchSmsNew = AtModem::pchSmsNewOriginal;
        AtModem::siDataListLine ++;
      }

      else
      {
        StackEnum::Add( Event::PSmsError );
        goto reset_pointers;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 6;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'p' ) && ( *( ( *apcchPointer ) + 2 ) == 'M' ) && ( *( ( *apcchPointer ) + 3 ) == 'S' ) && ( *( ( *apcchPointer ) + 4 ) == 'G' ) )
    {
      if ( AtModem::pchCmtMessage != '\0' )
      {
        if ( ( achRx != '\r' ) && ( achRx != '\n' ) && ( achRx != '\0' ) )
        {
          *AtModem::pchCmtMessage = achRx;
          AtModem::pchCmtMessage ++;
          *AtModem::pchCmtMessage = '\0';
          return true;
        }

        AtModem::pchCmtMessage = AtModem::pchCmtMessageOriginal;
        AtModem::siDataListLine ++;
      }

      else
      {
        StackEnum::Add( Event::PCmtMsgError );
        goto reset_pointers;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 6;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'p' ) && ( *( ( *apcchPointer ) + 2 ) == 'T' ) && ( *( ( *apcchPointer ) + 3 ) == 'M' ) && ( *( ( *apcchPointer ) + 4 ) == 'E' ) )
    {
      if ( AtModem::pchCmtTime != '\0' )
      {
        if ( ( ( achRx >= '0' ) && ( achRx <= '9' ) ) || ( achRx == ':' ) )
        {
          *AtModem::pchCmtTime = achRx;
          AtModem::pchCmtTime ++;
          *AtModem::pchCmtTime = '\0';
          return true;
        }

        AtModem::pchCmtTime = AtModem::pchCmtTimeOriginal;
        AtModem::siDataListLine ++;
      }

      else
      {
        StackEnum::Add( Event::PCmtTimeError );
        goto reset_pointers;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 6;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'p' ) && ( *( ( *apcchPointer ) + 2 ) == 'D' ) && ( *( ( *apcchPointer ) + 3 ) == 'A' ) && ( *( ( *apcchPointer ) + 4 ) == 'Y' ) )
    {
      if ( AtModem::pchCmtDay != '\0' )
      {
        if ( ( ( achRx >= '0' ) && ( achRx <= '9' ) ) || ( achRx == '/' ) )
        {
          *AtModem::pchCmtDay = achRx;
          AtModem::pchCmtDay ++;
          *AtModem::pchCmtDay = '\0';
          return true;
        }

        AtModem::pchCmtDay = AtModem::pchCmtDayOriginal;
        AtModem::siDataListLine ++;
      }

      else
      {
        StackEnum::Add( Event::PCmtDayError );
        goto reset_pointers;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 6;
    }

    else if ( ( *( ( *apcchPointer ) + 1 ) == 'p' ) && ( *( ( *apcchPointer ) + 2 ) == 'P' ) && ( *( ( *apcchPointer ) + 3 ) == 'H' ) && ( *( ( *apcchPointer ) + 4 ) == 'O' ) )
    {
      if ( AtModem::pchCmtPhone != '\0' )
      {
        if ( ( ( achRx >= '0' ) && ( achRx <= '9' ) ) || ( achRx == '+' ) || ( achRx == '-' ) )
        {
          *AtModem::pchCmtPhone = achRx;
          AtModem::pchCmtPhone ++;
          *AtModem::pchCmtPhone = '\0';
          return true;
        }

        AtModem::pchCmtPhone = AtModem::pchCmtPhoneOriginal;
        AtModem::siDataListLine ++;
      }

      else
      {
        StackEnum::Add( Event::PCmtPhoneError );
        goto reset_pointers;
      }

      ( *apcchPointer ) = ( *apcchPointer ) + 6;
    }
  }

  if ( **apcchPointer == '{' )
  {
    goto restart_process;
  }

  else if ( **apcchPointer == '\0' )
  {
    ( *apcchPointer ) = apcchPointerStart;
    AtModem::FlagSet( kDefFlagCheckEnd );
    //AtModem::OnEvent( e );
    StackEnum::Add( e );
    goto reset_pointers;
  }

  else if ( ( **apcchPointer == achRx ) || ( **apcchPointer == '\0' ) )
  {
    ( *apcchPointer ) ++;

    if ( **apcchPointer == '\0' )
    {
      ( *apcchPointer ) = apcchPointerStart;
      AtModem::FlagSet( kDefFlagCheckEnd );
      StackEnum::Add( e );
      goto reset_pointers;
    }

    return true;
  }

  reset_pointers:
    ( *apcchPointer ) = apcchPointerStart;
    return false;
}

void AtModem::Get ( char achChar )
{
  // Maquina de estados - inicio ->
  if ( AtModem::pDataRxToModem[ AtModem::siDataRxPointerLine ] != '\0' )
  {
    if ( *AtModem::pDataRxToModem[ AtModem::siDataRxPointerLine ] == achChar )
    {
      AtModem::pDataRxToModem[ AtModem::siDataRxPointerLine ] ++;
      if ( *AtModem::pDataRxToModem[ AtModem::siDataRxPointerLine ] == '\0' )
      {
        AtModem::siDataRxPointerLine ++;
        AtModem::FlagClear( kDefFlagWaiting );

        if ( AtModem::pDataRxToModem[ AtModem::siDataRxPointerLine ] == '\0' )
        {
          AtModem::FlagSet( kDefFlagProcessEnd );
        }
      }
    }
    else
    {
      AtModem::pDataRxToModem[ AtModem::siDataRxPointerLine ] = &AtModem::pDataRxToModem[ AtModem::siDataRxPointerLine ][ 0 ];
      //AtModem::EnumEvent = Event::EndLine;
      //AtModem::OnEvent ( Event::EndLine );
      //StackEnum::Add( Event::EndLine );
    }
  }
  else
  {
    AtModem::FlagSet( kDefFlagProcessEnd );
  }
  // Maquina de estados <- fim

  #ifdef I_NEED_USE_INTERNET_FUNCTIONS
    if ( AtModem::EnumStep == Step::ContentLength1 )
    {
      if ( ( AtModem::siGenericCounter >= kDefContentLength - 1 ) || ( achChar == '\r' ) || ( achChar == '\n' ) )
      {
        AtModem::siGenericCounter = 0;
        AtModem::EnumStep = Step::ContentLength2;
        return;
      }

      if ( AtModem::siContentLength == -1 )
      {
        AtModem::siContentLength = ( int ) ( achChar - '0' );
      }

      else
      {
        AtModem::siContentLength = ( AtModem::siContentLength * 10 ) + ( int ) ( achChar - '0' );
      }

      AtModem::siGenericCounter ++;

      return;
    }

    if ( AtModem::EnumStep == Step::ContentLength2 )
    {
      if ( *AtModem::pOkEndMessage == achChar )
      {
        AtModem::pOkEndMessage ++;

        if ( *AtModem::pOkEndMessage == '\0' )
        {
          AtModem::pOkEndMessage = &AtModem::kReceiveOkEndMessage[ 0 ];
          AtModem::EnumStep = Step::ContentLength3;
          //AtModem::OnEvent( Event::InternetReadStart );
          //AtModem::EnumEvent = Event::InternetReadStart;
          StackEnum::Add( Event::InternetReadStart );
          return;
        }
      }
      else
      {
        AtModem::pOkEndMessage = &AtModem::kReceiveOkEndMessage[ 0 ];
      }
    }

    if ( AtModem::EnumStep == Step::ContentLength3 )
    {
      AtModem::siContentLength --;

      if ( AtModem::siContentLength == 0 )
      {
        //AtModem::OnEvent( Event::InternetReadEnd );
        //AtModem::EnumEvent = Event::InternetReadEnd;
        StackEnum::Add( Event::InternetReadEnd );
        AtModem::EnumStep = Step::Stop;
        return;
      }
    }

    AtModem::siGenericCounter = 0;

    if ( *AtModem::pHeaderGetSend == achChar )
    {
      AtModem::pHeaderGetSend ++;

      if ( *AtModem::pHeaderGetSend == '\0' )
      {
        AtModem::pHeaderGetSend = &AtModem::kReceiveHeaderGetSend[ 0 ];
        AtModem::FlagSet( kDefFlagInternetGet );
        //AtModem::OnEvent( Event::InternetConnect );
        //AtModem::EnumEvent = Event::InternetConnect;
        StackEnum::Add( Event::InternetConnect );
      }
    }
    else
    {
      AtModem::pHeaderGetSend = &AtModem::kReceiveHeaderGetSend[ 0 ];
    }

    if ( *AtModem::pReceiveDeactiveGprsDpdOk == achChar )
    {
      AtModem::pReceiveDeactiveGprsDpdOk ++;

      if ( *AtModem::pReceiveDeactiveGprsDpdOk == '\0' )
      {
        AtModem::pReceiveDeactiveGprsDpdOk = &AtModem::kReceiveDeactiveGprsDpdOk[ 0 ];

        if ( AtModem::FlagTest( kDefFlagInternetGet ) == true )
        {
          //AtModem::OnEvent( Event::InternetDisconnect );
          //AtModem::EnumEvent = Event::InternetDisconnect;
          StackEnum::Add( Event::InternetDisconnect );
        }

        AtModem::FlagClear( kDefFlagInternetGet );
      }
    }
    else
    {
      AtModem::pReceiveDeactiveGprsDpdOk = &AtModem::kReceiveDeactiveGprsDpdOk[ 0 ];
    }

    if ( *AtModem::pContentLength == achChar )
    {
      AtModem::pContentLength ++;

      if ( *AtModem::pContentLength == '\0' )
      {
        AtModem::pContentLength = &AtModem::kReceiveContentLength[ 0 ];
        AtModem::siContentLength = -1;
        AtModem::EnumStep = Step::ContentLength1;
      }
    }
    else
    {
      AtModem::pContentLength = &AtModem::kReceiveContentLength[ 0 ];
    }

    AtModem::__GetTest ( &AtModem::pClose, &AtModem::kReceiveClose[ 0 ], achChar, Event::Close );
    AtModem::__GetTest ( &AtModem::pClosed, &AtModem::kReceiveClosed[ 0 ], achChar, Event::Close );
    AtModem::__GetTest ( &AtModem::pConnectionFailed1, &AtModem::kReceiveConnectionFailed1[ 0 ], achChar, Event::ConnectionFailed );
    AtModem::__GetTest ( &AtModem::pConnectionFailed2, &AtModem::kReceiveConnectionFailed2[ 0 ], achChar, Event::ConnectionFailed );
  #endif

  #ifdef I_NEED_GEO_FUNCTIONS
    AtModem::__GetTest ( &AtModem::pReceiveEnginneringModeData, &AtModem::kReceiveEnginneringModeData[ 0 ], achChar, Event::EnginneringData );
  #endif

  #ifdef I_NEED_POWER_DOWN_FUNCTIONS
    AtModem::__GetTest ( &AtModem::pReceivePowerOn, &AtModem::kReceivePowerOn[ 0 ], achChar, Event::PowerOn );
    AtModem::__GetTest ( &AtModem::pNormalPowerDown, &AtModem::kReceiveNormalPowerDown[ 0 ], achChar, Event::PowerDown );
  #endif

  #ifdef I_NEED_SIM_PIN_FUNCTIONS
    AtModem::__GetTest ( &AtModem::pReceiveSimReady, &AtModem::kReceiveSimReady[ 0 ], achChar, Event::SimReady );
    AtModem::__GetTest ( &AtModem::pReceiveSimPin, &AtModem::kReceiveSimPin[ 0 ], achChar, Event::SimPin );
    AtModem::__GetTest ( &AtModem::pReceiveSimPuk, &AtModem::kReceiveSimPuk[ 0 ], achChar, Event::SimPuk );
    AtModem::__GetTest ( &AtModem::pReceiveSimPhPin, &AtModem::kReceiveSimPhPin[ 0 ], achChar, Event::SimPhPin );
    AtModem::__GetTest ( &AtModem::pReceiveSimPhPuk, &AtModem::kReceiveSimPhPuk[ 0 ], achChar, Event::SimPhPuk );
  #endif

  #ifdef I_NEED_SMS_FUNCTIONS
    AtModem::__GetTest ( &AtModem::pCmti, &AtModem::kReceiveCmti[ 0 ], achChar, Event::SMSNew );
    AtModem::__GetTest ( &AtModem::pCmgl, &AtModem::kReceiveCmgl[ 0 ], achChar, Event::SMSReadByStatus );
    AtModem::__GetTest ( &AtModem::pCmgr, &AtModem::kReceiveCmgr[ 0 ], achChar, Event::SMSRead );
    AtModem::__GetTest ( &AtModem::pReceiveCmt, &AtModem::kReceiveCmt[ 0 ], achChar, Event::SMSCompanyRead );
  #endif

  #ifdef I_NEED_CALL_FUNCTIONS
    AtModem::__GetTest ( &AtModem::pCarrierNumber, &AtModem::kReceiveCarrierNumber[ 0 ], achChar, Event::CarrierNumberCaptured );
    AtModem::__GetTest ( &AtModem::pRingString, &AtModem::kReceiveRingString[ 0 ], achChar, Event::Ring );
    AtModem::__GetTest ( &AtModem::pNoCarrier, &AtModem::kReceiveNoCarrier[ 0 ], achChar, Event::NoCarrier );
    AtModem::__GetTest ( &AtModem::pNoDialTone1, &AtModem::kReceiveNoDialTone1[ 0 ], achChar, Event::NoDialTone );
    AtModem::__GetTest ( &AtModem::pNoDialTone2, &AtModem::kReceiveNoDialTone2[ 0 ], achChar, Event::NoDialTone );
    AtModem::__GetTest ( &AtModem::pNoAnswer, &AtModem::kReceiveNoAnswer[ 0 ], achChar, Event::NoAnswer );
    AtModem::__GetTest ( &AtModem::pBusy, &AtModem::kReceiveBusy[ 0 ], achChar, Event::Busy );
  #endif

  AtModem::__GetTest ( &AtModem::pCallReady, &AtModem::kReceiveCallReady[ 0 ], achChar, Event::CallReady );
  AtModem::__GetTest ( &AtModem::pError, &AtModem::kReceiveError[ 0 ], achChar, Event::Error );

  #ifdef I_NEED_RTC_FUNCTIONS
    AtModem::__GetTest ( &AtModem::pCclk, &AtModem::kReceiveCclk[ 0 ], achChar, Event::RTCRead );
  #endif

  #ifdef I_NEED_QUALITY_FUNCTIONS
    AtModem::__GetTest ( &AtModem::pSignalQuality, &AtModem::kReceiveSignalQuality[ 0 ], achChar, Event::SignalQuality );
  #endif

  #ifdef I_NEED_PHONEBOOK_FUNCTIONS
    AtModem::__GetTest ( &AtModem::pReceivePhoneBookFind, &AtModem::kReceivePhoneBookFind[ 0 ], achChar, Event::PhoneBookFind );
  #endif
}
