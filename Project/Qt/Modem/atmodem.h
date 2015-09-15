#ifndef ATMODEM_H
#define ATMODEM_H

#define I_NEED_USE_INTERNET_FUNCTIONS
#define I_NEED_SIM_PIN_FUNCTIONS
#define I_NEED_POWER_DOWN_FUNCTIONS
#define I_NEED_SMS_FUNCTIONS
#define I_NEED_CALL_FUNCTIONS
#define I_NEED_GEO_FUNCTIONS
#define I_NEED_PHONEBOOK_FUNCTIONS
#define I_NEED_RTC_FUNCTIONS
#define I_NEED_QUALITY_FUNCTIONS

#define ENABLE_AUTO_POWER_ON_COMMANDS
#define ENABLE_AUTO_INTERNET_DISCONECT
#define ENABLE_AUTO_INTERNET_DISCONECT_AFTER_ERROR

#define kDefContentLength 5














// Nao mude nada a partir desse ponto
// Do not change anything from that point

#ifndef I_NEED_CALL_FUNCTIONS
  #undef ENABLE_AUTO_CALLER_NUMBER
#endif

#ifndef I_NEED_USE_INTERNET_FUNCTIONS
  #undef I_NEED_GEO_FUNCTIONS
  #undef ENABLE_AUTO_INTERNET_DISCONECT
  #undef ENABLE_AUTO_INTERNET_DISCONECT_AFTER_ERROR
#endif

#ifndef I_NEED_SMS_FUNCTIONS
  #undef ENABLE_AUTO_READ_AND_DELETE_SMS
#endif

#ifndef I_NEED_SMS_FUNCTIONS
  #undef ENABLE_AUTO_POWER_ON_COMMANDS
#endif

#ifndef I_NEED_SIM_PIN_FUNCTIONS
  #undef ENABLE_AUTO_PIN_ENABLE
#endif

#define kDefFlagRuning 0
#define kDefFlagNextStep 1
#define kDefFlagWaiting 2
#define kDefFlagInternetGet 3
#define kDefFlagCheckEnd 4
#define kDefFlagProcessEnd 5


namespace Step
{
  enum eStep
  {
    ContentLength1,
    ContentLength2,
    ContentLength3,
    Stop
  };
}
using namespace Step;


namespace Event
{
  enum eEvent
  {
    None,
    PTimeError,
    PNumError,
    PSNumError,
    PSHexError,
    PStrError,
    PAllError,
    PSmsError,
    PCmtMsgError,
    PCmtTimeError,
    PCmtDayError,
    PCmtPhoneError,

    #ifdef I_NEED_ROOT_FUNCTIONS
    RootEnable,
    RootDisable,
    RootAddData,
    RootDelData,
    #endif

    #ifdef I_NEED_USE_INTERNET_FUNCTIONS
      InternetReadStart,
      InternetReadEnd,
      Close,
      ConnectionFailed,
      InternetConnect,
      InternetDisconnect,
    #endif
    #ifdef I_NEED_GEO_FUNCTIONS
      EnginneringData,
      EnginneringDataToGeo,
    #endif
    #ifdef I_NEED_PHONEBOOK_FUNCTIONS
      PhoneBookFind,
    #endif
    EndLine,
    EndProcess,
    CarrierNumberCaptured,
    Ring,
    SMSNew,
    SMSSend,
    SMSReadByStatus,
    SMSRead,
    SMSCompanyRead,
    SMSNumberAvailable,
    SMSDeleted,
    PowerOn,


    SimReady,
    SimPin,
    SimPuk,
    SimPhPin,
    SimPhPuk,
    SimPinNotFound,

    NoCarrier,
    NoDialTone,
    NoAnswer,
    Busy,
    Error,

    CallReady,
    PowerDown,
    SignalQuality,
    RTCRead,

    UserEvent1,
    UserEvent2,
    UserEvent3,
    UserEvent4,
    UserEvent5,
    UserEvent6,
    UserEvent7,
    UserEvent8,
    UserEvent9,
    UserEvent10,
    UserEvent11,
    UserEvent12,
    UserEvent13,
    UserEvent14,
    UserEvent15,
    UserEvent16,
    UserEvent17,
    UserEvent18,
    UserEvent19,
    UserEvent20
  };
}
using namespace Event;

extern "C"
{
  typedef void ( * StatusModem ) ( eEvent );
  typedef void ( * ExternalDataModem ) ( char );
  typedef void ( * Action ) ();
}

class AtModem
{
public:

  #ifdef I_NEED_RTC_FUNCTIONS
    static const char kSendRtc[];
    static const char *pSendRtc;
    static const char kReceiveCclk[];
    static const char kSendCclk[];
    static const char *pCclk;
    void static RtcSet ();
    void static RtcGet ();
  #endif

  #ifdef I_NEED_POWER_DOWN_FUNCTIONS
    static const char kSendPowerDown[];
    static const char kReceivePowerOn[];
    static const char kReceiveNormalPowerDown[];
    static const char *pNormalPowerDown;
    static const char *pReceivePowerOn;
    void static PowerDown ();
    void static OnModemPowerOn ();
  #endif

  #ifdef I_NEED_SIM_PIN_FUNCTIONS
    static const char kSendSinStatus[];
    static const char kSendSinPinUnlock[];
    static const char kSendSinPinLock[];
    static const char kSendSinPinChange[];
    static const char kSendSinPinEnter[];
    static const char kReceiveSimReady[];
    static const char kReceiveSimPin[];
    static const char kReceiveSimPuk[];
    static const char kReceiveSimPhPin[];
    static const char kReceiveSimPhPuk[];
    static const char *pReceiveSimReady;
    static const char *pReceiveSimPin;
    static const char *pReceiveSimPuk;
    static const char *pReceiveSimPhPin;
    static const char *pReceiveSimPhPuk;
    void static SimStatus ();
    void static SimEnterPin ();
    void static SimLockByPin ();
    void static SimUnlockByPin ();
    void static SimChangePin ();
  #endif

  #ifdef I_NEED_USE_INTERNET_FUNCTIONS
    static const char kSendIpSingle[];
    static const char kSendIpModeNormal[];
    static const char kSendDeactiveGprsDpd[];
    static const char kSendConnectHost[];
    static const char kSendStartSendData[];
    static const char kSendHeaderGetSend[];
    static const char kSendInternetDns[];
    static const char kSendInternetConnect[];
    static const char kSendInternerConnectPassword[];
    static const char kReceiveDeactiveGprsDpdOk[];
    static const char kReceiveContentLength[];
    static const char kReceiveHeaderGetSend[];
    static const char kReceiveConnectHost[];
    static const char kReceiveClose[];
    static const char kReceiveClosed[];
    static const char kReceiveConnectionFailed1[];
    static const char kReceiveConnectionFailed2[];
    static const char *pReceiveDeactiveGprsDpdOk;
    static const char *pClose;
    static const char *pClosed;
    static const char *pConnectionFailed1;
    static const char *pConnectionFailed2;
    static const char *pContentLength;
    static const char *pHeaderGetSend;
    static int siContentLength;
    void static DisconnectToHost ();
    void static DisconnectAfterError ();
    void static SendDataByGet ();
  #endif

  #ifdef I_NEED_SMS_FUNCTIONS
    static const char kSendSmsTextMode[];
    static const char kSendSmsSendConfig[];
    static const char kSendSmsSendText[];
    static const char kSendSmsReadMessageId[];
    static const char kSendSmsReadMessageStatus[];
    static const char kSendSmsDeleteMessageId[];
    static const char kSendSmsDeleteMessageStatus[];
    static const char kSendSmsAdvancedMode[];
    static const char kReceiveCmti[];
    static const char kReceiveOkEndMessage[];
    static const char kReceiveCmgl[];
    static const char kReceiveCmgr[];
    static const char kReceiveCmt[];
    static const char *pOkEndMessage;
    static const char *pCmti;
    static const char *pCmgl;
    static const char *pCmgr;
    static const char *pReceiveCmt;
    void static SmsSend ();
    void static SmsReadById ();
    void static SmsReadByStatus ();
    void static SmsReadAndDeleteById ();
    void static SmsDeleteById ();
    void static SmsDeleteByStatus ();
  #endif

  #if defined I_NEED_CALL_FUNCTIONS || defined I_NEED_USE_INTERNET_FUNCTIONS
    static const char kReceiveSmsTextRedyToSend[];
    char static DayOfWeek (char *apchDay );
  #endif

  #ifdef I_NEED_CALL_FUNCTIONS
    static const char kSendDialNumberInVoiceMode[];
    static const char kSendHangUpInVoiceMode[];
    static const char kSendAnsweringInVoiceMode[];
    static const char kReceiveNoCarrier[];
    static const char kReceiveNoDialTone1[];
    static const char kReceiveNoDialTone2[];
    static const char kReceiveNoAnswer[];
    static const char kReceiveBusy[];
    static const char kReceiveRingString[];
    static const char kReceiveCarrierNumber[];
    static const char kSendCarrierNumber[];
    static const char *pRingString;
    static const char *pNoCarrier;
    static const char *pError;
    static const char *pNoDialTone1;
    static const char *pNoDialTone2;
    static const char *pNoAnswer;
    static const char *pBusy;
    static const char *pCarrierNumber;
    void static CallDial ();
    void static CallHangUp ();
    void static CallAnswering ();
    void static CallGetNumber ();
  #endif

  #ifdef I_NEED_ROOT_FUNCTIONS
    static const char kReceiveRootNumberEnable[];
    static const char *pReceiveRootNumberEnable;

    static const char kReceiveRootNumberDisable[];
    static const char *pReceiveRootNumberDisable;

    static const char kReceiveRootNumberAddPhoneBook[];
    static const char *pReceiveRootNumberAddPhoneBook;

    static const char kReceiveRootNumberDelPhoneBook[];
    static const char *pReceiveRootNumberDelPhoneBook;

    static const char kRootName[];
    static const char *pRootName;

    static void SetRootPhoneBook ();
    static void ClearRootPhoneBook ();
  #endif

  #ifdef I_NEED_GEO_FUNCTIONS
    static const char kSendEnginneringModeOn[];
    static const char kSendEnginneringGet[];
    static const char kReceiveEnginneringModeData[];
    static const char *pReceiveEnginneringModeData;
    static void GetEnginneringData ();
  #endif

  #ifdef I_NEED_QUALITY_FUNCTIONS
    static const char kReceiveSignalQuality[];
    static const char kSendSignalQuality[];
    static const char *pSignalQuality;
    void static SignalQuality ();
  #endif

  #ifdef I_NEED_PHONEBOOK_FUNCTIONS
    static const char kReceivePhoneBookFind[];
    static const char kSendPhoneBookClearId[];
    static const char kSendPhoneBookWriteId[];
    static const char kSendPhoneBookWrite[];
    static const char kSendPhoneBookFind[];

    static const char *pReceivePhoneBookFind;

    void static PhoneBookSet ();
    void static PhoneBookIdSet ();
    void static PhoneBookClearId ();
    void static PhoneBookFind ();
    void static PhoneBookFindId ();
  #endif

  static Action OnEndProcess;
  static StatusModem StatusEvent;
  static ExternalDataModem DataSendEvent;
  static ExternalDataModem DataReceivedEvent;

  static eStep EnumStep;
  static eEvent EnumEvent;

  static bool gblInternetConnect;

  static char *pchSmsNew;
  static char *pchSmsNewOriginal;
  static char *pchCmtPhone;
  static char *pchCmtPhoneOriginal;
  static char *pchCmtDay;
  static char *pchCmtDayOriginal;
  static char *pchCmtTime;
  static char *pchCmtTimeOriginal;
  static char *pchCmtMessage;
  static char *pchCmtMessageOriginal;

  static char *pchTmpValue;
  static char **ppchTmpAddr;

  static char *pDataList[];//20

  static const char *pOriginal;
  static const char *pCallReady;

  static const char *pDataTxToModem[];//13
  static const char *pDataRxToModem[];//13

  static int siDataListLine;
  static int siDataTxPointerLine;
  static int siDataRxPointerLine;
  static int siGenericCounter;

  static char schFlags;

  static const char kSendEchoOff[];
  static const char kSendEchoOn[];
  static const char kReceiveCallReady[];
  static const char kReceiveOk[];
  static const char kReceiveError[];

  AtModem();
  void static Init ();
  bool static __GetTest( const char **apcchPointer, const char *apcchPointerStart, char achRx, Event::eEvent e );
  void static Get ( char achChar );
  void static FlagSet ( char achFlag );
  void static FlagClear ( char achFlag );
  bool static FlagTest ( char achFlag );
  void static ConstCharToChar ( const char *p1, char *p2 );
  void static ConstCharToChar ( char *p1, char *p2 );
  void static ResetPointers ();
  void static OnEvent ( eEvent aenEvent );
  void static EchoOn ();
  void static EchoOff ();
  void static StateMachine ();
  void static StateMachineRun ();
  void static StateMachineResetAndRun ();
  void static PontSecuryCopy ( char **pchOriginal, char **pchNew );
  void static PointReturnAfterSecuryCopy ();
  void static Checker ( const char *apcchPointer, char *apchRx, Event::eEvent e );
};

#endif // ATMODEM_H
