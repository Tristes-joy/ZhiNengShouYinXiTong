/********************************************************************************
** Form generated from reading UI file 'charge.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGE_H
#define UI_CHARGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Charge
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *vip_card;
    QLabel *label_2;
    QLabel *class_level;
    QLabel *label_3;
    QLineEdit *phone_number;
    QLabel *rank_get;
    QLabel *label_4;
    QLabel *staute;
    QLabel *pay_;
    QLabel *pay_num;
    QTableView *table_view;
    QPushButton *setting_card;
    QPushButton *load;
    QLabel *total_price;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *cut_off;
    QLabel *label_7;
    QLabel *need_pay;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Charge)
    {
        if (Charge->objectName().isEmpty())
            Charge->setObjectName("Charge");
        Charge->resize(640, 480);
        centralwidget = new QWidget(Charge);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 641, 451));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(450, 0, 181, 171));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 41, 16));
        vip_card = new QLineEdit(groupBox);
        vip_card->setObjectName("vip_card");
        vip_card->setGeometry(QRect(50, 30, 121, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 100, 41, 16));
        class_level = new QLabel(groupBox);
        class_level->setObjectName("class_level");
        class_level->setGeometry(QRect(50, 60, 81, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 111, 51, 41));
        phone_number = new QLineEdit(groupBox);
        phone_number->setObjectName("phone_number");
        phone_number->setGeometry(QRect(50, 120, 121, 21));
        rank_get = new QLabel(groupBox);
        rank_get->setObjectName("rank_get");
        rank_get->setGeometry(QRect(50, 100, 61, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 62, 40, 20));
        staute = new QLabel(groupBox);
        staute->setObjectName("staute");
        staute->setGeometry(QRect(50, 62, 101, 20));
        pay_ = new QLabel(groupBox);
        pay_->setObjectName("pay_");
        pay_->setGeometry(QRect(10, 150, 40, 20));
        pay_num = new QLabel(groupBox);
        pay_num->setObjectName("pay_num");
        pay_num->setGeometry(QRect(50, 150, 101, 20));
        table_view = new QTableView(widget);
        table_view->setObjectName("table_view");
        table_view->setGeometry(QRect(20, 20, 411, 341));
        setting_card = new QPushButton(widget);
        setting_card->setObjectName("setting_card");
        setting_card->setGeometry(QRect(450, 260, 91, 51));
        load = new QPushButton(widget);
        load->setObjectName("load");
        load->setGeometry(QRect(450, 200, 91, 51));
        total_price = new QLabel(widget);
        total_price->setObjectName("total_price");
        total_price->setGeometry(QRect(80, 369, 41, 41));
        QFont font;
        font.setPointSize(14);
        total_price->setFont(font);
        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 370, 51, 31));
        QFont font1;
        font1.setPointSize(18);
        label_5->setFont(font1);
        label_6 = new QLabel(widget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(150, 370, 51, 31));
        label_6->setFont(font1);
        cut_off = new QLabel(widget);
        cut_off->setObjectName("cut_off");
        cut_off->setGeometry(QRect(200, 370, 51, 41));
        cut_off->setFont(font);
        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(310, 370, 51, 31));
        label_7->setFont(font1);
        need_pay = new QLabel(widget);
        need_pay->setObjectName("need_pay");
        need_pay->setGeometry(QRect(360, 370, 61, 41));
        need_pay->setFont(font);
        Charge->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Charge);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 640, 17));
        Charge->setMenuBar(menubar);
        statusbar = new QStatusBar(Charge);
        statusbar->setObjectName("statusbar");
        Charge->setStatusBar(statusbar);

        retranslateUi(Charge);

        QMetaObject::connectSlotsByName(Charge);
    } // setupUi

    void retranslateUi(QMainWindow *Charge)
    {
        Charge->setWindowTitle(QCoreApplication::translate("Charge", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Charge", "\344\274\232\345\221\230\344\277\241\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("Charge", "\344\274\232\345\221\230\345\215\241", nullptr));
        label_2->setText(QCoreApplication::translate("Charge", "\347\272\247\345\210\253", nullptr));
        class_level->setText(QString());
        label_3->setText(QCoreApplication::translate("Charge", "\346\211\213\346\234\272\345\217\267", nullptr));
        rank_get->setText(QString());
        label_4->setText(QCoreApplication::translate("Charge", "\347\212\266\346\200\201", nullptr));
        staute->setText(QString());
        pay_->setText(QCoreApplication::translate("Charge", "\344\275\231\351\242\235", nullptr));
        pay_num->setText(QString());
        setting_card->setText(QCoreApplication::translate("Charge", "\347\273\223\347\256\227", nullptr));
        load->setText(QCoreApplication::translate("Charge", "\347\231\273\345\205\245", nullptr));
        total_price->setText(QString());
        label_5->setText(QCoreApplication::translate("Charge", "\346\200\273\351\242\235", nullptr));
        label_6->setText(QCoreApplication::translate("Charge", "\346\212\230\346\211\243", nullptr));
        cut_off->setText(QString());
        label_7->setText(QCoreApplication::translate("Charge", "\345\272\224\344\273\230", nullptr));
        need_pay->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Charge: public Ui_Charge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGE_H
