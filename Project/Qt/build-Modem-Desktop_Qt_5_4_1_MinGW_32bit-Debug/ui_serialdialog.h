/********************************************************************************
** Form generated from reading UI file 'serialdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALDIALOG_H
#define UI_SERIALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SerialDialog
{
public:
    QPushButton *bcClose;
    QPushButton *SerialPortConnectPushButton;
    QComboBox *SerialPortListComboBox;
    QLabel *lbDevices;

    void setupUi(QDialog *SerialDialog)
    {
        if (SerialDialog->objectName().isEmpty())
            SerialDialog->setObjectName(QStringLiteral("SerialDialog"));
        SerialDialog->setWindowModality(Qt::NonModal);
        SerialDialog->resize(400, 99);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SerialDialog->sizePolicy().hasHeightForWidth());
        SerialDialog->setSizePolicy(sizePolicy);
        SerialDialog->setMinimumSize(QSize(400, 99));
        SerialDialog->setMaximumSize(QSize(400, 99));
        SerialDialog->setFocusPolicy(Qt::ClickFocus);
        SerialDialog->setSizeGripEnabled(true);
        bcClose = new QPushButton(SerialDialog);
        bcClose->setObjectName(QStringLiteral("bcClose"));
        bcClose->setGeometry(QRect(292, 68, 100, 23));
        SerialPortConnectPushButton = new QPushButton(SerialDialog);
        SerialPortConnectPushButton->setObjectName(QStringLiteral("SerialPortConnectPushButton"));
        SerialPortConnectPushButton->setGeometry(QRect(292, 8, 100, 23));
        SerialPortListComboBox = new QComboBox(SerialDialog);
        SerialPortListComboBox->setObjectName(QStringLiteral("SerialPortListComboBox"));
        SerialPortListComboBox->setGeometry(QRect(52, 8, 236, 22));
        lbDevices = new QLabel(SerialDialog);
        lbDevices->setObjectName(QStringLiteral("lbDevices"));
        lbDevices->setGeometry(QRect(8, 12, 40, 16));

        retranslateUi(SerialDialog);

        QMetaObject::connectSlotsByName(SerialDialog);
    } // setupUi

    void retranslateUi(QDialog *SerialDialog)
    {
        SerialDialog->setWindowTitle(QApplication::translate("SerialDialog", "Dialog", 0));
        bcClose->setText(QApplication::translate("SerialDialog", "Fechar", 0));
        SerialPortConnectPushButton->setText(QApplication::translate("SerialDialog", "Conectar", 0));
        lbDevices->setText(QApplication::translate("SerialDialog", "Devices:", 0));
    } // retranslateUi

};

namespace Ui {
    class SerialDialog: public Ui_SerialDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALDIALOG_H
