/********************************************************************************
** Form generated from reading UI file 'card_id.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARD_ID_H
#define UI_CARD_ID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_card_id
{
public:
    QLineEdit *card_num;
    QPushButton *add;
    QPushButton *delet;
    QTableView *tableView;
    QPushButton *search;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *rank;
    QLabel *label_3;
    QLineEdit *phone_number;
    QLineEdit *rank_2;
    QLabel *pay_mem;

    void setupUi(QWidget *card_id)
    {
        if (card_id->objectName().isEmpty())
            card_id->setObjectName("card_id");
        card_id->resize(499, 439);
        card_num = new QLineEdit(card_id);
        card_num->setObjectName("card_num");
        card_num->setGeometry(QRect(40, 270, 71, 31));
        add = new QPushButton(card_id);
        add->setObjectName("add");
        add->setGeometry(QRect(200, 330, 111, 41));
        delet = new QPushButton(card_id);
        delet->setObjectName("delet");
        delet->setGeometry(QRect(340, 330, 111, 41));
        tableView = new QTableView(card_id);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(50, 20, 411, 241));
        search = new QPushButton(card_id);
        search->setObjectName("search");
        search->setGeometry(QRect(50, 330, 111, 41));
        label = new QLabel(card_id);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 270, 51, 31));
        label_2 = new QLabel(card_id);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 270, 61, 31));
        rank = new QLineEdit(card_id);
        rank->setObjectName("rank");
        rank->setGeometry(QRect(160, 270, 51, 31));
        label_3 = new QLabel(card_id);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(220, 270, 41, 31));
        phone_number = new QLineEdit(card_id);
        phone_number->setObjectName("phone_number");
        phone_number->setGeometry(QRect(260, 270, 111, 31));
        rank_2 = new QLineEdit(card_id);
        rank_2->setObjectName("rank_2");
        rank_2->setGeometry(QRect(440, 270, 41, 31));
        pay_mem = new QLabel(card_id);
        pay_mem->setObjectName("pay_mem");
        pay_mem->setGeometry(QRect(390, 270, 61, 31));

        retranslateUi(card_id);

        QMetaObject::connectSlotsByName(card_id);
    } // setupUi

    void retranslateUi(QWidget *card_id)
    {
        card_id->setWindowTitle(QCoreApplication::translate("card_id", "Form", nullptr));
        add->setText(QCoreApplication::translate("card_id", "\346\263\250\345\206\214", nullptr));
        delet->setText(QCoreApplication::translate("card_id", "\345\210\240\351\231\244", nullptr));
        search->setText(QCoreApplication::translate("card_id", "\346\237\245\350\257\242", nullptr));
        label->setText(QCoreApplication::translate("card_id", "\345\215\241\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("card_id", "\347\255\211\347\272\247", nullptr));
        label_3->setText(QCoreApplication::translate("card_id", "\346\211\213\346\234\272\345\217\267", nullptr));
        phone_number->setText(QString());
        pay_mem->setText(QCoreApplication::translate("card_id", "\344\275\231\351\242\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class card_id: public Ui_card_id {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARD_ID_H
