#ifndef SERIALDIALOG_H
#define SERIALDIALOG_H

#define kDefSerialPortConnectLabel    "Conecatar"
#define kDefSerialPortDisconnectLabel "Desconectar"
#define kDefSerialPortCloseLabel      "Fechar"
#define kDefSerialPortSettings        {BAUD115200, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 100}

#include <QDialog>

#include "qextserialenumerator.h"
#include "qextserialport.h"

#include "types.h"

extern "C"
{
  typedef void ( * SerialData ) ( char );
  typedef void ( * SerialEvent ) ();
}

namespace Ui {
class SerialDialog;
}

class SerialDialog : public QDialog
{
  Q_OBJECT

public:
  static SerialData  Rx;
  static SerialData  Tx;
  static SerialEvent OnConnect;
  static SerialEvent OnDisconnect;
  static QextSerialPort *SerialPort;
  static bool IsConnected;


  explicit SerialDialog(QWidget *parent = 0);
  void serialDisconect ();
  void static writeSerial ( char achData );
  ~SerialDialog();

private slots:
  void on_SerialPortConnectPushButton_clicked();
  void readSerial ();
  void enableControls ();

  void on_bcClose_clicked();

signals:
  void setPortName ( QString portName );

private:
  Ui::SerialDialog *ui;
  void enableSerialControls(bool vablEnable);
  void OnConnectEvent ();
  void OnDisconnectEvent ();
  void serialConnect ();
  void serialList ();
};

#endif // SERIALDIALOG_H
