/********************************************************************************
** Form generated from reading UI file 'dtmf.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTMF_H
#define UI_DTMF_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dtmf
{
public:
    QPushButton *pb1;
    QPushButton *pb2;
    QPushButton *pb3;
    QPushButton *pb6;
    QPushButton *pb4;
    QPushButton *pb5;
    QPushButton *pb9;
    QPushButton *pb7;
    QPushButton *pb8;
    QPushButton *pbB;
    QPushButton *pbA;
    QPushButton *pb0;

    void setupUi(QDialog *Dtmf)
    {
        if (Dtmf->objectName().isEmpty())
            Dtmf->setObjectName(QStringLiteral("Dtmf"));
        Dtmf->resize(236, 310);
        Dtmf->setMinimumSize(QSize(236, 310));
        Dtmf->setMaximumSize(QSize(236, 310));
        pb1 = new QPushButton(Dtmf);
        pb1->setObjectName(QStringLiteral("pb1"));
        pb1->setGeometry(QRect(4, 4, 75, 76));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        pb1->setFont(font);
        pb2 = new QPushButton(Dtmf);
        pb2->setObjectName(QStringLiteral("pb2"));
        pb2->setGeometry(QRect(80, 4, 75, 76));
        pb2->setFont(font);
        pb3 = new QPushButton(Dtmf);
        pb3->setObjectName(QStringLiteral("pb3"));
        pb3->setGeometry(QRect(156, 4, 75, 76));
        pb3->setFont(font);
        pb6 = new QPushButton(Dtmf);
        pb6->setObjectName(QStringLiteral("pb6"));
        pb6->setGeometry(QRect(156, 80, 75, 76));
        pb6->setFont(font);
        pb4 = new QPushButton(Dtmf);
        pb4->setObjectName(QStringLiteral("pb4"));
        pb4->setGeometry(QRect(4, 80, 75, 76));
        pb4->setFont(font);
        pb5 = new QPushButton(Dtmf);
        pb5->setObjectName(QStringLiteral("pb5"));
        pb5->setGeometry(QRect(80, 80, 75, 76));
        pb5->setFont(font);
        pb9 = new QPushButton(Dtmf);
        pb9->setObjectName(QStringLiteral("pb9"));
        pb9->setGeometry(QRect(156, 156, 75, 76));
        pb9->setFont(font);
        pb7 = new QPushButton(Dtmf);
        pb7->setObjectName(QStringLiteral("pb7"));
        pb7->setGeometry(QRect(4, 156, 75, 76));
        pb7->setFont(font);
        pb8 = new QPushButton(Dtmf);
        pb8->setObjectName(QStringLiteral("pb8"));
        pb8->setGeometry(QRect(80, 156, 75, 76));
        pb8->setFont(font);
        pbB = new QPushButton(Dtmf);
        pbB->setObjectName(QStringLiteral("pbB"));
        pbB->setGeometry(QRect(156, 232, 75, 76));
        pbB->setFont(font);
        pbA = new QPushButton(Dtmf);
        pbA->setObjectName(QStringLiteral("pbA"));
        pbA->setGeometry(QRect(4, 232, 75, 76));
        pbA->setFont(font);
        pb0 = new QPushButton(Dtmf);
        pb0->setObjectName(QStringLiteral("pb0"));
        pb0->setGeometry(QRect(80, 232, 75, 76));
        pb0->setFont(font);

        retranslateUi(Dtmf);

        QMetaObject::connectSlotsByName(Dtmf);
    } // setupUi

    void retranslateUi(QDialog *Dtmf)
    {
        Dtmf->setWindowTitle(QApplication::translate("Dtmf", "Dialog", 0));
        pb1->setText(QApplication::translate("Dtmf", "1", 0));
        pb2->setText(QApplication::translate("Dtmf", "2", 0));
        pb3->setText(QApplication::translate("Dtmf", "3", 0));
        pb6->setText(QApplication::translate("Dtmf", "6", 0));
        pb4->setText(QApplication::translate("Dtmf", "4", 0));
        pb5->setText(QApplication::translate("Dtmf", "5", 0));
        pb9->setText(QApplication::translate("Dtmf", "9", 0));
        pb7->setText(QApplication::translate("Dtmf", "7", 0));
        pb8->setText(QApplication::translate("Dtmf", "8", 0));
        pbB->setText(QApplication::translate("Dtmf", "#", 0));
        pbA->setText(QApplication::translate("Dtmf", "*", 0));
        pb0->setText(QApplication::translate("Dtmf", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class Dtmf: public Ui_Dtmf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTMF_H
