/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSair;
    QAction *actionSerial;
    QAction *actionSobre;
    QAction *actionGet_SIM_Status;
    QAction *actionEnter_PIN;
    QAction *actionChange_PIN;
    QAction *actionLock;
    QAction *actionPIN_Unlock;
    QAction *actionUse_GET_method_to_connect_a_host;
    QAction *actionDisconnect;
    QAction *actionSend;
    QAction *actionRead_by_id;
    QAction *actionDelete_by_id;
    QAction *actionRead_and_delete_by_id;
    QAction *actionEcho_ON;
    QAction *actionEcho_OFF;
    QAction *actionPower_OFF;
    QAction *actionGet_signal_quality;
    QAction *actionDelete_by_status_DEL_READ;
    QAction *actionDelete_by_status_DEL_UNREAD;
    QAction *actionDelete_by_status_DEL_SENT;
    QAction *actionDelete_by_status_DEL_UNSENT;
    QAction *actionDelete_by_status_DEL_INBOX;
    QAction *actionDelete_by_status_DEL_ALL;
    QAction *actionRead_by_status_ALL;
    QAction *actionRead_by_status_REC_READ;
    QAction *actionRead_by_status_REC_UNREAD;
    QAction *actionRead_by_status_STO_SEND;
    QAction *actionRead_by_status_STO_UNSENT;
    QAction *actionGet_Number;
    QAction *actionCall_Number;
    QAction *actionHang_Up;
    QAction *actionAnswering;
    QAction *actionRead;
    QAction *actionSet;
    QAction *actionGet_GEO_data_GPS_Less;
    QAction *actionAgenda_Adicionar;
    QAction *actionAgenda_Adicionar_com_Id;
    QAction *actionAgenda_Apagar_com_Id;
    QAction *actionAgenda_Procurar;
    QWidget *centralWidget;
    QLabel *lbDadoEnviado;
    QTextEdit *teSerialTx;
    QPushButton *pbSend;
    QPushButton *btClear;
    QLabel *lbStatus;
    QTextEdit *teStatus;
    QPushButton *pbDebug;
    QLineEdit *leUrl;
    QLabel *lbHost;
    QLabel *lbPort;
    QLineEdit *lePorta;
    QLabel *lbQueryString;
    QLineEdit *leQueryString;
    QLabel *lbOperadoraId;
    QLabel *lbOperadoraPassword;
    QLabel *UserName;
    QLabel *lbUserPassword;
    QLineEdit *leOperadoraId;
    QLineEdit *leOperadoraPassword;
    QLineEdit *leUserName;
    QLineEdit *leUserPassword;
    QLabel *lbSmsId;
    QLabel *lbSmsTexto;
    QLineEdit *leSmsId;
    QLineEdit *leSmsTexto;
    QLineEdit *leSmsTelefone;
    QLabel *lbSmsTelefone;
    QLabel *lbHost_2;
    QLineEdit *leSite;
    QLineEdit *lePin;
    QLabel *lbPin;
    QLabel *lbSmsId_2;
    QLineEdit *leSend;
    QLineEdit *lePinNew;
    QLabel *lbPinNew;
    QMenuBar *menuBar;
    QMenu *menuArquivo;
    QMenu *menuSerial;
    QMenu *menuAjuda;
    QMenu *menuComandos;
    QMenu *menuChip_SIM;
    QMenu *menuInternet;
    QMenu *menuSMS;
    QMenu *menuGeneric_commands;
    QMenu *menuCall;
    QMenu *menuRTC;
    QMenu *menuPhone_Book;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(576, 550);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(576, 550));
        MainWindow->setMaximumSize(QSize(576, 550));
        actionSair = new QAction(MainWindow);
        actionSair->setObjectName(QStringLiteral("actionSair"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icons/appbar.stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSair->setIcon(icon);
        actionSerial = new QAction(MainWindow);
        actionSerial->setObjectName(QStringLiteral("actionSerial"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/icons/appbar.connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSerial->setIcon(icon1);
        actionSobre = new QAction(MainWindow);
        actionSobre->setObjectName(QStringLiteral("actionSobre"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/icons/appbar.cursor.information.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSobre->setIcon(icon2);
        actionGet_SIM_Status = new QAction(MainWindow);
        actionGet_SIM_Status->setObjectName(QStringLiteral("actionGet_SIM_Status"));
        actionEnter_PIN = new QAction(MainWindow);
        actionEnter_PIN->setObjectName(QStringLiteral("actionEnter_PIN"));
        actionChange_PIN = new QAction(MainWindow);
        actionChange_PIN->setObjectName(QStringLiteral("actionChange_PIN"));
        actionLock = new QAction(MainWindow);
        actionLock->setObjectName(QStringLiteral("actionLock"));
        actionPIN_Unlock = new QAction(MainWindow);
        actionPIN_Unlock->setObjectName(QStringLiteral("actionPIN_Unlock"));
        actionUse_GET_method_to_connect_a_host = new QAction(MainWindow);
        actionUse_GET_method_to_connect_a_host->setObjectName(QStringLiteral("actionUse_GET_method_to_connect_a_host"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionSend = new QAction(MainWindow);
        actionSend->setObjectName(QStringLiteral("actionSend"));
        actionRead_by_id = new QAction(MainWindow);
        actionRead_by_id->setObjectName(QStringLiteral("actionRead_by_id"));
        actionDelete_by_id = new QAction(MainWindow);
        actionDelete_by_id->setObjectName(QStringLiteral("actionDelete_by_id"));
        actionRead_and_delete_by_id = new QAction(MainWindow);
        actionRead_and_delete_by_id->setObjectName(QStringLiteral("actionRead_and_delete_by_id"));
        actionEcho_ON = new QAction(MainWindow);
        actionEcho_ON->setObjectName(QStringLiteral("actionEcho_ON"));
        actionEcho_OFF = new QAction(MainWindow);
        actionEcho_OFF->setObjectName(QStringLiteral("actionEcho_OFF"));
        actionPower_OFF = new QAction(MainWindow);
        actionPower_OFF->setObjectName(QStringLiteral("actionPower_OFF"));
        actionGet_signal_quality = new QAction(MainWindow);
        actionGet_signal_quality->setObjectName(QStringLiteral("actionGet_signal_quality"));
        actionDelete_by_status_DEL_READ = new QAction(MainWindow);
        actionDelete_by_status_DEL_READ->setObjectName(QStringLiteral("actionDelete_by_status_DEL_READ"));
        actionDelete_by_status_DEL_UNREAD = new QAction(MainWindow);
        actionDelete_by_status_DEL_UNREAD->setObjectName(QStringLiteral("actionDelete_by_status_DEL_UNREAD"));
        actionDelete_by_status_DEL_SENT = new QAction(MainWindow);
        actionDelete_by_status_DEL_SENT->setObjectName(QStringLiteral("actionDelete_by_status_DEL_SENT"));
        actionDelete_by_status_DEL_UNSENT = new QAction(MainWindow);
        actionDelete_by_status_DEL_UNSENT->setObjectName(QStringLiteral("actionDelete_by_status_DEL_UNSENT"));
        actionDelete_by_status_DEL_INBOX = new QAction(MainWindow);
        actionDelete_by_status_DEL_INBOX->setObjectName(QStringLiteral("actionDelete_by_status_DEL_INBOX"));
        actionDelete_by_status_DEL_ALL = new QAction(MainWindow);
        actionDelete_by_status_DEL_ALL->setObjectName(QStringLiteral("actionDelete_by_status_DEL_ALL"));
        actionRead_by_status_ALL = new QAction(MainWindow);
        actionRead_by_status_ALL->setObjectName(QStringLiteral("actionRead_by_status_ALL"));
        actionRead_by_status_REC_READ = new QAction(MainWindow);
        actionRead_by_status_REC_READ->setObjectName(QStringLiteral("actionRead_by_status_REC_READ"));
        actionRead_by_status_REC_UNREAD = new QAction(MainWindow);
        actionRead_by_status_REC_UNREAD->setObjectName(QStringLiteral("actionRead_by_status_REC_UNREAD"));
        actionRead_by_status_STO_SEND = new QAction(MainWindow);
        actionRead_by_status_STO_SEND->setObjectName(QStringLiteral("actionRead_by_status_STO_SEND"));
        actionRead_by_status_STO_UNSENT = new QAction(MainWindow);
        actionRead_by_status_STO_UNSENT->setObjectName(QStringLiteral("actionRead_by_status_STO_UNSENT"));
        actionGet_Number = new QAction(MainWindow);
        actionGet_Number->setObjectName(QStringLiteral("actionGet_Number"));
        actionCall_Number = new QAction(MainWindow);
        actionCall_Number->setObjectName(QStringLiteral("actionCall_Number"));
        actionHang_Up = new QAction(MainWindow);
        actionHang_Up->setObjectName(QStringLiteral("actionHang_Up"));
        actionAnswering = new QAction(MainWindow);
        actionAnswering->setObjectName(QStringLiteral("actionAnswering"));
        actionRead = new QAction(MainWindow);
        actionRead->setObjectName(QStringLiteral("actionRead"));
        actionSet = new QAction(MainWindow);
        actionSet->setObjectName(QStringLiteral("actionSet"));
        actionGet_GEO_data_GPS_Less = new QAction(MainWindow);
        actionGet_GEO_data_GPS_Less->setObjectName(QStringLiteral("actionGet_GEO_data_GPS_Less"));
        actionAgenda_Adicionar = new QAction(MainWindow);
        actionAgenda_Adicionar->setObjectName(QStringLiteral("actionAgenda_Adicionar"));
        actionAgenda_Adicionar_com_Id = new QAction(MainWindow);
        actionAgenda_Adicionar_com_Id->setObjectName(QStringLiteral("actionAgenda_Adicionar_com_Id"));
        actionAgenda_Apagar_com_Id = new QAction(MainWindow);
        actionAgenda_Apagar_com_Id->setObjectName(QStringLiteral("actionAgenda_Apagar_com_Id"));
        actionAgenda_Procurar = new QAction(MainWindow);
        actionAgenda_Procurar->setObjectName(QStringLiteral("actionAgenda_Procurar"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lbDadoEnviado = new QLabel(centralWidget);
        lbDadoEnviado->setObjectName(QStringLiteral("lbDadoEnviado"));
        lbDadoEnviado->setGeometry(QRect(12, 4, 96, 13));
        teSerialTx = new QTextEdit(centralWidget);
        teSerialTx->setObjectName(QStringLiteral("teSerialTx"));
        teSerialTx->setGeometry(QRect(8, 20, 560, 188));
        teSerialTx->setInputMethodHints(Qt::ImhMultiLine|Qt::ImhUppercaseOnly);
        teSerialTx->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        pbSend = new QPushButton(centralWidget);
        pbSend->setObjectName(QStringLiteral("pbSend"));
        pbSend->setGeometry(QRect(492, 456, 76, 20));
        btClear = new QPushButton(centralWidget);
        btClear->setObjectName(QStringLiteral("btClear"));
        btClear->setGeometry(QRect(416, 484, 75, 20));
        lbStatus = new QLabel(centralWidget);
        lbStatus->setObjectName(QStringLiteral("lbStatus"));
        lbStatus->setGeometry(QRect(12, 212, 36, 13));
        teStatus = new QTextEdit(centralWidget);
        teStatus->setObjectName(QStringLiteral("teStatus"));
        teStatus->setGeometry(QRect(8, 228, 560, 88));
        pbDebug = new QPushButton(centralWidget);
        pbDebug->setObjectName(QStringLiteral("pbDebug"));
        pbDebug->setGeometry(QRect(492, 484, 75, 20));
        leUrl = new QLineEdit(centralWidget);
        leUrl->setObjectName(QStringLiteral("leUrl"));
        leUrl->setGeometry(QRect(8, 336, 128, 20));
        lbHost = new QLabel(centralWidget);
        lbHost->setObjectName(QStringLiteral("lbHost"));
        lbHost->setGeometry(QRect(12, 320, 28, 13));
        lbPort = new QLabel(centralWidget);
        lbPort->setObjectName(QStringLiteral("lbPort"));
        lbPort->setGeometry(QRect(444, 320, 32, 13));
        lePorta = new QLineEdit(centralWidget);
        lePorta->setObjectName(QStringLiteral("lePorta"));
        lePorta->setGeometry(QRect(440, 336, 128, 20));
        lbQueryString = new QLabel(centralWidget);
        lbQueryString->setObjectName(QStringLiteral("lbQueryString"));
        lbQueryString->setGeometry(QRect(300, 320, 64, 13));
        leQueryString = new QLineEdit(centralWidget);
        leQueryString->setObjectName(QStringLiteral("leQueryString"));
        leQueryString->setGeometry(QRect(296, 336, 128, 20));
        lbOperadoraId = new QLabel(centralWidget);
        lbOperadoraId->setObjectName(QStringLiteral("lbOperadoraId"));
        lbOperadoraId->setGeometry(QRect(12, 360, 72, 13));
        lbOperadoraPassword = new QLabel(centralWidget);
        lbOperadoraPassword->setObjectName(QStringLiteral("lbOperadoraPassword"));
        lbOperadoraPassword->setGeometry(QRect(156, 360, 108, 13));
        UserName = new QLabel(centralWidget);
        UserName->setObjectName(QStringLiteral("UserName"));
        UserName->setGeometry(QRect(300, 360, 60, 13));
        lbUserPassword = new QLabel(centralWidget);
        lbUserPassword->setObjectName(QStringLiteral("lbUserPassword"));
        lbUserPassword->setGeometry(QRect(444, 360, 76, 13));
        leOperadoraId = new QLineEdit(centralWidget);
        leOperadoraId->setObjectName(QStringLiteral("leOperadoraId"));
        leOperadoraId->setGeometry(QRect(8, 376, 128, 20));
        leOperadoraPassword = new QLineEdit(centralWidget);
        leOperadoraPassword->setObjectName(QStringLiteral("leOperadoraPassword"));
        leOperadoraPassword->setGeometry(QRect(152, 376, 128, 20));
        leUserName = new QLineEdit(centralWidget);
        leUserName->setObjectName(QStringLiteral("leUserName"));
        leUserName->setGeometry(QRect(296, 376, 128, 20));
        leUserPassword = new QLineEdit(centralWidget);
        leUserPassword->setObjectName(QStringLiteral("leUserPassword"));
        leUserPassword->setGeometry(QRect(440, 376, 128, 20));
        lbSmsId = new QLabel(centralWidget);
        lbSmsId->setObjectName(QStringLiteral("lbSmsId"));
        lbSmsId->setGeometry(QRect(12, 400, 48, 13));
        lbSmsTexto = new QLabel(centralWidget);
        lbSmsTexto->setObjectName(QStringLiteral("lbSmsTexto"));
        lbSmsTexto->setGeometry(QRect(300, 400, 96, 13));
        leSmsId = new QLineEdit(centralWidget);
        leSmsId->setObjectName(QStringLiteral("leSmsId"));
        leSmsId->setGeometry(QRect(8, 416, 128, 20));
        leSmsTexto = new QLineEdit(centralWidget);
        leSmsTexto->setObjectName(QStringLiteral("leSmsTexto"));
        leSmsTexto->setGeometry(QRect(296, 416, 128, 20));
        leSmsTelefone = new QLineEdit(centralWidget);
        leSmsTelefone->setObjectName(QStringLiteral("leSmsTelefone"));
        leSmsTelefone->setGeometry(QRect(152, 416, 128, 20));
        lbSmsTelefone = new QLabel(centralWidget);
        lbSmsTelefone->setObjectName(QStringLiteral("lbSmsTelefone"));
        lbSmsTelefone->setGeometry(QRect(156, 400, 136, 13));
        lbHost_2 = new QLabel(centralWidget);
        lbHost_2->setObjectName(QStringLiteral("lbHost_2"));
        lbHost_2->setGeometry(QRect(156, 320, 28, 13));
        leSite = new QLineEdit(centralWidget);
        leSite->setObjectName(QStringLiteral("leSite"));
        leSite->setGeometry(QRect(152, 336, 128, 20));
        lePin = new QLineEdit(centralWidget);
        lePin->setObjectName(QStringLiteral("lePin"));
        lePin->setGeometry(QRect(440, 416, 60, 20));
        lbPin = new QLabel(centralWidget);
        lbPin->setObjectName(QStringLiteral("lbPin"));
        lbPin->setGeometry(QRect(444, 400, 20, 13));
        lbSmsId_2 = new QLabel(centralWidget);
        lbSmsId_2->setObjectName(QStringLiteral("lbSmsId_2"));
        lbSmsId_2->setGeometry(QRect(12, 440, 108, 13));
        leSend = new QLineEdit(centralWidget);
        leSend->setObjectName(QStringLiteral("leSend"));
        leSend->setGeometry(QRect(8, 456, 480, 20));
        lePinNew = new QLineEdit(centralWidget);
        lePinNew->setObjectName(QStringLiteral("lePinNew"));
        lePinNew->setGeometry(QRect(508, 416, 60, 20));
        lbPinNew = new QLabel(centralWidget);
        lbPinNew->setObjectName(QStringLiteral("lbPinNew"));
        lbPinNew->setGeometry(QRect(512, 400, 48, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 576, 21));
        menuArquivo = new QMenu(menuBar);
        menuArquivo->setObjectName(QStringLiteral("menuArquivo"));
        menuSerial = new QMenu(menuBar);
        menuSerial->setObjectName(QStringLiteral("menuSerial"));
        menuAjuda = new QMenu(menuBar);
        menuAjuda->setObjectName(QStringLiteral("menuAjuda"));
        menuComandos = new QMenu(menuBar);
        menuComandos->setObjectName(QStringLiteral("menuComandos"));
        menuChip_SIM = new QMenu(menuComandos);
        menuChip_SIM->setObjectName(QStringLiteral("menuChip_SIM"));
        menuInternet = new QMenu(menuComandos);
        menuInternet->setObjectName(QStringLiteral("menuInternet"));
        menuSMS = new QMenu(menuComandos);
        menuSMS->setObjectName(QStringLiteral("menuSMS"));
        menuGeneric_commands = new QMenu(menuComandos);
        menuGeneric_commands->setObjectName(QStringLiteral("menuGeneric_commands"));
        menuCall = new QMenu(menuComandos);
        menuCall->setObjectName(QStringLiteral("menuCall"));
        menuRTC = new QMenu(menuComandos);
        menuRTC->setObjectName(QStringLiteral("menuRTC"));
        menuPhone_Book = new QMenu(menuComandos);
        menuPhone_Book->setObjectName(QStringLiteral("menuPhone_Book"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuArquivo->menuAction());
        menuBar->addAction(menuSerial->menuAction());
        menuBar->addAction(menuComandos->menuAction());
        menuBar->addAction(menuAjuda->menuAction());
        menuArquivo->addAction(actionSair);
        menuSerial->addAction(actionSerial);
        menuAjuda->addAction(actionSobre);
        menuComandos->addAction(menuChip_SIM->menuAction());
        menuComandos->addAction(menuCall->menuAction());
        menuComandos->addAction(menuInternet->menuAction());
        menuComandos->addAction(menuSMS->menuAction());
        menuComandos->addAction(menuRTC->menuAction());
        menuComandos->addAction(menuGeneric_commands->menuAction());
        menuComandos->addAction(menuPhone_Book->menuAction());
        menuChip_SIM->addAction(actionGet_SIM_Status);
        menuChip_SIM->addAction(actionEnter_PIN);
        menuChip_SIM->addAction(actionChange_PIN);
        menuChip_SIM->addAction(actionLock);
        menuChip_SIM->addAction(actionPIN_Unlock);
        menuInternet->addAction(actionUse_GET_method_to_connect_a_host);
        menuInternet->addAction(actionGet_GEO_data_GPS_Less);
        menuInternet->addAction(actionDisconnect);
        menuSMS->addAction(actionSend);
        menuSMS->addAction(actionRead_by_id);
        menuSMS->addAction(actionRead_and_delete_by_id);
        menuSMS->addAction(actionRead_by_status_ALL);
        menuSMS->addAction(actionRead_by_status_REC_READ);
        menuSMS->addAction(actionRead_by_status_REC_UNREAD);
        menuSMS->addAction(actionRead_by_status_STO_SEND);
        menuSMS->addAction(actionRead_by_status_STO_UNSENT);
        menuSMS->addAction(actionDelete_by_id);
        menuSMS->addAction(actionDelete_by_status_DEL_READ);
        menuSMS->addAction(actionDelete_by_status_DEL_UNREAD);
        menuSMS->addAction(actionDelete_by_status_DEL_SENT);
        menuSMS->addAction(actionDelete_by_status_DEL_UNSENT);
        menuSMS->addAction(actionDelete_by_status_DEL_INBOX);
        menuSMS->addAction(actionDelete_by_status_DEL_ALL);
        menuGeneric_commands->addAction(actionEcho_ON);
        menuGeneric_commands->addAction(actionEcho_OFF);
        menuGeneric_commands->addAction(actionPower_OFF);
        menuGeneric_commands->addAction(actionGet_signal_quality);
        menuCall->addAction(actionGet_Number);
        menuCall->addAction(actionCall_Number);
        menuCall->addAction(actionHang_Up);
        menuCall->addAction(actionAnswering);
        menuRTC->addAction(actionRead);
        menuRTC->addAction(actionSet);
        menuPhone_Book->addAction(actionAgenda_Adicionar);
        menuPhone_Book->addAction(actionAgenda_Adicionar_com_Id);
        menuPhone_Book->addAction(actionAgenda_Apagar_com_Id);
        menuPhone_Book->addAction(actionAgenda_Procurar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "AtModem Class Test", 0));
        actionSair->setText(QApplication::translate("MainWindow", "Sair", 0));
        actionSerial->setText(QApplication::translate("MainWindow", "Serial", 0));
        actionSobre->setText(QApplication::translate("MainWindow", "Sobre", 0));
        actionGet_SIM_Status->setText(QApplication::translate("MainWindow", "SIM - Ler Status", 0));
        actionEnter_PIN->setText(QApplication::translate("MainWindow", "SIM - Enviar PIN", 0));
        actionChange_PIN->setText(QApplication::translate("MainWindow", "SIM - Trocar PIN", 0));
        actionLock->setText(QApplication::translate("MainWindow", "SIM - Ativar senha PIN", 0));
        actionPIN_Unlock->setText(QApplication::translate("MainWindow", "SIM - Desativar senha PIN", 0));
        actionUse_GET_method_to_connect_a_host->setText(QApplication::translate("MainWindow", "Internet - Enviar dados via GET", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow", "Internet - Desconectar", 0));
        actionSend->setText(QApplication::translate("MainWindow", "SMS - Enviar", 0));
        actionRead_by_id->setText(QApplication::translate("MainWindow", "SMS - Ler por Id", 0));
        actionRead_by_id->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+R", 0));
        actionDelete_by_id->setText(QApplication::translate("MainWindow", "SMS - Apagar por Id", 0));
        actionRead_and_delete_by_id->setText(QApplication::translate("MainWindow", "SMS - Ler e apagar por Id", 0));
        actionEcho_ON->setText(QApplication::translate("MainWindow", "Echo - Ligar", 0));
        actionEcho_OFF->setText(QApplication::translate("MainWindow", "Echo - Desligar", 0));
        actionPower_OFF->setText(QApplication::translate("MainWindow", "Power - Desligar", 0));
        actionGet_signal_quality->setText(QApplication::translate("MainWindow", "Sinal - Medir", 0));
        actionDelete_by_status_DEL_READ->setText(QApplication::translate("MainWindow", "SMS - Apagar por status: DEL READ", 0));
        actionDelete_by_status_DEL_UNREAD->setText(QApplication::translate("MainWindow", "SMS - Apagar por status: DEL UNREAD", 0));
        actionDelete_by_status_DEL_SENT->setText(QApplication::translate("MainWindow", "SMS - Apagar por status: DEL SENT", 0));
        actionDelete_by_status_DEL_UNSENT->setText(QApplication::translate("MainWindow", "SMS - Apagar por status: DEL UNSENT", 0));
        actionDelete_by_status_DEL_INBOX->setText(QApplication::translate("MainWindow", "SMS - Apagar por status: DEL INBOX", 0));
        actionDelete_by_status_DEL_ALL->setText(QApplication::translate("MainWindow", "SMS - Apagar por status: DEL ALL", 0));
        actionRead_by_status_ALL->setText(QApplication::translate("MainWindow", "SMS - Ler por status: ALL", 0));
        actionRead_by_status_REC_READ->setText(QApplication::translate("MainWindow", "SMS - Ler por status: REC READ", 0));
        actionRead_by_status_REC_UNREAD->setText(QApplication::translate("MainWindow", "SMS - Ler por status: REC UNREAD", 0));
        actionRead_by_status_STO_SEND->setText(QApplication::translate("MainWindow", "SMS - Ler por status: STO SENT", 0));
        actionRead_by_status_STO_UNSENT->setText(QApplication::translate("MainWindow", "SMS - Ler por status: STO UNSENT", 0));
        actionGet_Number->setText(QApplication::translate("MainWindow", "Liga\303\247\303\243o - N\303\272mero do chamador", 0));
        actionCall_Number->setText(QApplication::translate("MainWindow", "Lica\303\247\303\243o - Ligar", 0));
        actionHang_Up->setText(QApplication::translate("MainWindow", "Liga\303\247\303\243o - Desligar", 0));
        actionAnswering->setText(QApplication::translate("MainWindow", "Liga\303\247\303\243o - Atender", 0));
        actionRead->setText(QApplication::translate("MainWindow", "Read RTC", 0));
        actionSet->setText(QApplication::translate("MainWindow", "Set RTC", 0));
        actionGet_GEO_data_GPS_Less->setText(QApplication::translate("MainWindow", "Internet - Localizar modem ( SEM GPS )", 0));
        actionAgenda_Adicionar->setText(QApplication::translate("MainWindow", "Agenda - Adicionar", 0));
        actionAgenda_Adicionar_com_Id->setText(QApplication::translate("MainWindow", "Agenda - Adicionar com Id", 0));
        actionAgenda_Apagar_com_Id->setText(QApplication::translate("MainWindow", "Agenda - Apagar com Id", 0));
        actionAgenda_Procurar->setText(QApplication::translate("MainWindow", "Agenda - Procurar", 0));
        lbDadoEnviado->setText(QApplication::translate("MainWindow", "Dado a ser enviado:", 0));
        pbSend->setText(QApplication::translate("MainWindow", "Enviar", 0));
        btClear->setText(QApplication::translate("MainWindow", "Limpar", 0));
        lbStatus->setText(QApplication::translate("MainWindow", "Status:", 0));
        pbDebug->setText(QApplication::translate("MainWindow", "Debug", 0));
        leUrl->setText(QApplication::translate("MainWindow", "www.kemper.com.br", 0));
        lbHost->setText(QApplication::translate("MainWindow", "Host:", 0));
        lbPort->setText(QApplication::translate("MainWindow", "Porta:", 0));
        lePorta->setText(QApplication::translate("MainWindow", "80", 0));
        lbQueryString->setText(QApplication::translate("MainWindow", "Query String:", 0));
        leQueryString->setText(QApplication::translate("MainWindow", "?id=1", 0));
        lbOperadoraId->setText(QApplication::translate("MainWindow", "Operadora ID:", 0));
        lbOperadoraPassword->setText(QApplication::translate("MainWindow", "Operadora Password:", 0));
        UserName->setText(QApplication::translate("MainWindow", "User Name:", 0));
        lbUserPassword->setText(QApplication::translate("MainWindow", "User Password:", 0));
        leOperadoraId->setText(QApplication::translate("MainWindow", "gprs.oi.br", 0));
        leOperadoraPassword->setText(QApplication::translate("MainWindow", "gprs.oi.br", 0));
        leUserName->setText(QApplication::translate("MainWindow", "oi", 0));
        leUserPassword->setText(QApplication::translate("MainWindow", "oi", 0));
        lbSmsId->setText(QApplication::translate("MainWindow", "Id SMS:", 0));
        lbSmsTexto->setText(QApplication::translate("MainWindow", "Texto SMS/Agenda:", 0));
        leSmsId->setText(QApplication::translate("MainWindow", "2", 0));
        leSmsTexto->setText(QApplication::translate("MainWindow", "+ROOT: DESABLE", 0));
        leSmsTelefone->setText(QApplication::translate("MainWindow", "83317942", 0));
        lbSmsTelefone->setText(QApplication::translate("MainWindow", "Telefone SMS/Ligar/Agenda:", 0));
        lbHost_2->setText(QApplication::translate("MainWindow", "Site:", 0));
        leSite->setText(QApplication::translate("MainWindow", "/modem.php", 0));
        lePin->setText(QApplication::translate("MainWindow", "1234", 0));
        lbPin->setText(QApplication::translate("MainWindow", "PIN:", 0));
        lbSmsId_2->setText(QApplication::translate("MainWindow", "Enviar para o modem:", 0));
        leSend->setText(QString());
        lePinNew->setText(QApplication::translate("MainWindow", "5678", 0));
        lbPinNew->setText(QApplication::translate("MainWindow", "Novo PIN:", 0));
        menuArquivo->setTitle(QApplication::translate("MainWindow", "Arquivo", 0));
        menuSerial->setTitle(QApplication::translate("MainWindow", "Perif\303\251ricos", 0));
        menuAjuda->setTitle(QApplication::translate("MainWindow", "Ajuda", 0));
        menuComandos->setTitle(QApplication::translate("MainWindow", "Fun\303\247\303\265es do modem", 0));
        menuChip_SIM->setTitle(QApplication::translate("MainWindow", "Chip SIM", 0));
        menuInternet->setTitle(QApplication::translate("MainWindow", "Internet", 0));
        menuSMS->setTitle(QApplication::translate("MainWindow", "SMS", 0));
        menuGeneric_commands->setTitle(QApplication::translate("MainWindow", "Comandos gen\303\251ricos", 0));
        menuCall->setTitle(QApplication::translate("MainWindow", "Liga\303\247\303\243o", 0));
        menuRTC->setTitle(QApplication::translate("MainWindow", "RTC", 0));
        menuPhone_Book->setTitle(QApplication::translate("MainWindow", "Agenda", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
