#include <QTimer>

#include "serialdialog.h"
#include "ui_serialdialog.h"

#include "qextserialenumerator.h"
#include "qextserialport.h"

#include "types.h"

SerialData SerialDialog::Rx = '\0';
SerialData SerialDialog::Tx = '\0';

SerialEvent SerialDialog::OnConnect = '\0';
SerialEvent SerialDialog::OnDisconnect = '\0';

bool SerialDialog::IsConnected = false;
QextSerialPort *SerialDialog::SerialPort;

SerialDialog::SerialDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SerialDialog)
{
  ui->setupUi(this);

  ui->SerialPortConnectPushButton->setText ( kDefSerialPortConnectLabel );

  serialList ();

  QTimer::singleShot ( 500, this, SLOT ( enableControls () ) );
  QTimer::singleShot ( 10, this, SLOT ( readSerial () ) );
}

SerialDialog::~SerialDialog()
{
  if ( SerialDialog::IsConnected == true )
  {
    if ( SerialDialog::SerialPort->isOpen() )
    {
      SerialDialog::SerialPort->close();

      SerialDialog::OnDisconnectEvent ();
    }
  }
  delete ui;
}

void SerialDialog::OnConnectEvent ()
{
  if ( SerialDialog::OnConnect != '\0' )
  {
    SerialDialog::OnConnect ();
  }

  SerialDialog::Tx = &SerialDialog::writeSerial;
}

void SerialDialog::OnDisconnectEvent ()
{
  if ( SerialDialog::OnDisconnect != '\0' )
  {
    SerialDialog::OnDisconnect ();
  }

  SerialDialog::Tx = '\0';
}

void SerialDialog::enableControls ()
{
  if ( SerialDialog::IsConnected == false )
  {
    enableSerialControls ( false );
  }

  QTimer::singleShot ( 500, this, SLOT ( enableControls () ) );
}

void SerialDialog::writeSerial ( char achData )
{
  if ( SerialDialog::IsConnected == true )
  {
    SerialDialog::SerialPort->write( &achData, 1 );
  }
}

void SerialDialog::readSerial ()
{
  char dado;

  if ( SerialDialog::IsConnected == true )
  {
    while ( SerialDialog::SerialPort->bytesAvailable () )
    {
      SerialDialog::SerialPort->read( &dado, 1 );

      if ( SerialDialog::Rx != 0 )
      {
        SerialDialog::Rx ( dado );
      }
    }
  }

  QTimer::singleShot ( 50, this, SLOT ( readSerial () ) );
}

void SerialDialog::serialList ()
{
  int vluchContador;
  unsigned int vluiCurrentIndex =  0;
  QString    vlqstrActualPort =  ui->SerialPortListComboBox->currentText();

  ui->SerialPortListComboBox->clear();

  QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
  for ( vluchContador = 0; vluchContador < ports.size(); vluchContador ++)
  {
    if ( ports.at( vluchContador ).friendName.length() == 0 )
    {
      continue;
    }

    ui->SerialPortListComboBox->addItem( ports.at( vluchContador ).friendName );

    if ( vlqstrActualPort.contains( ports.at( vluchContador ).friendName ) )
    {
      ui->SerialPortListComboBox->setCurrentIndex( vluiCurrentIndex );
    }

    vluiCurrentIndex ++;
  }
}

void SerialDialog::enableSerialControls ( bool vablEnable )
{
  serialList();
  if ( vablEnable == true )
  {
    ui->SerialPortConnectPushButton->setDisabled ( false );
    ui->SerialPortListComboBox->setDisabled ( false );
  }

  else
  {
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    if ( ui->SerialPortListComboBox->count() > 0 )
    {
      ui->SerialPortConnectPushButton->setDisabled ( false );
      ui->SerialPortConnectPushButton->setFocus ();
      ui->SerialPortListComboBox->setDisabled ( false );
    }
    else
    {
      ui->SerialPortConnectPushButton->setDisabled ( true );
      ui->SerialPortListComboBox->setDisabled ( true );
    }
  }
}

void SerialDialog::serialConnect ()
{
  if ( SerialDialog::IsConnected == true )
  {
    SerialDialog::IsConnected =  false;
    ui->SerialPortConnectPushButton->setText ( kDefSerialPortConnectLabel );
    SerialDialog::SerialPort->close();

    SerialDialog::OnDisconnectEvent ();
  }

  else
  {
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    PortSettings settings = kDefSerialPortSettings;

    #ifdef Q_OS_LINUX

      SerialDialog::SerialPort = new QextSerialPort( ports.at ( ui->SerialPortListComboBox->currentIndex() ).physName , settings, QextSerialPort::Polling );
      SerialDialog::SerialPort->open(QIODevice::ReadWrite);

    #else

      SerialDialog::SerialPort = new QextSerialPort( ports.at ( ui->SerialPortListComboBox->currentIndex() ).portName , settings, QextSerialPort::Polling );
      SerialDialog::SerialPort->open(QIODevice::ReadWrite);

    #endif

    if ( SerialDialog::SerialPort->isOpen() )
    {
      SerialDialog::IsConnected =  true;
      ui->SerialPortConnectPushButton->setText ( kDefSerialPortDisconnectLabel );
      readSerial ();
    }

    else
    {
      SerialDialog::IsConnected =  false;
    }
  }

  enableSerialControls ( SerialDialog::IsConnected );
}

void SerialDialog::serialDisconect ()
{
  if ( SerialDialog::IsConnected == true )
  {
    SerialDialog::IsConnected =  false;
    ui->SerialPortConnectPushButton->setText ( kDefSerialPortConnectLabel );
    SerialDialog::SerialPort->close();

    SerialDialog::OnDisconnectEvent ();
  }
}

void SerialDialog::on_SerialPortConnectPushButton_clicked()
{
  serialConnect ();
  this->hide();

  SerialDialog::OnConnectEvent ();
}

void SerialDialog::on_bcClose_clicked()
{
  this->hide();
}
