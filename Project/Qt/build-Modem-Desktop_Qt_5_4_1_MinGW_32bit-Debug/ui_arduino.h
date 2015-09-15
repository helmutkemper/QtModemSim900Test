/********************************************************************************
** Form generated from reading UI file 'arduino.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARDUINO_H
#define UI_ARDUINO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Arduino
{
public:

    void setupUi(QDialog *Arduino)
    {
        if (Arduino->objectName().isEmpty())
            Arduino->setObjectName(QStringLiteral("Arduino"));
        Arduino->resize(400, 300);

        retranslateUi(Arduino);

        QMetaObject::connectSlotsByName(Arduino);
    } // setupUi

    void retranslateUi(QDialog *Arduino)
    {
        Arduino->setWindowTitle(QApplication::translate("Arduino", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class Arduino: public Ui_Arduino {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARDUINO_H
