/********************************************************************************
** Form generated from reading UI file 'serialport.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALPORT_H
#define UI_SERIALPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialPort
{
public:
    QWidget *widget;
    QComboBox *comboBox;
    QLabel *port;
    QLabel *bit;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QLabel *numberbit;
    QComboBox *comboBox_4;
    QLabel *stopbit;
    QComboBox *comboBox_5;
    QLabel *checkbit;

    void setupUi(QWidget *SerialPort)
    {
        if (SerialPort->objectName().isEmpty())
            SerialPort->setObjectName("SerialPort");
        SerialPort->resize(250, 440);
        widget = new QWidget(SerialPort);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 241, 421));
        comboBox = new QComboBox(widget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(110, 70, 62, 22));
        port = new QLabel(widget);
        port->setObjectName("port");
        port->setGeometry(QRect(40, 70, 61, 21));
        port->setAlignment(Qt::AlignCenter);
        bit = new QLabel(widget);
        bit->setObjectName("bit");
        bit->setGeometry(QRect(40, 100, 61, 21));
        bit->setAlignment(Qt::AlignCenter);
        comboBox_2 = new QComboBox(widget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(110, 100, 62, 22));
        comboBox_3 = new QComboBox(widget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(110, 130, 62, 22));
        numberbit = new QLabel(widget);
        numberbit->setObjectName("numberbit");
        numberbit->setGeometry(QRect(40, 130, 61, 21));
        numberbit->setAlignment(Qt::AlignCenter);
        comboBox_4 = new QComboBox(widget);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName("comboBox_4");
        comboBox_4->setGeometry(QRect(110, 160, 62, 22));
        stopbit = new QLabel(widget);
        stopbit->setObjectName("stopbit");
        stopbit->setGeometry(QRect(40, 160, 61, 21));
        stopbit->setAlignment(Qt::AlignCenter);
        comboBox_5 = new QComboBox(widget);
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName("comboBox_5");
        comboBox_5->setGeometry(QRect(110, 190, 62, 22));
        checkbit = new QLabel(widget);
        checkbit->setObjectName("checkbit");
        checkbit->setGeometry(QRect(40, 190, 61, 21));
        checkbit->setAlignment(Qt::AlignCenter);

        retranslateUi(SerialPort);

        QMetaObject::connectSlotsByName(SerialPort);
    } // setupUi

    void retranslateUi(QWidget *SerialPort)
    {
        SerialPort->setWindowTitle(QCoreApplication::translate("SerialPort", "Form", nullptr));
        port->setText(QCoreApplication::translate("SerialPort", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\347\253\257\345\217\243</span></p></body></html>", nullptr));
        bit->setText(QCoreApplication::translate("SerialPort", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\346\263\242\347\211\271\347\216\207</span></p></body></html>", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("SerialPort", "9600", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("SerialPort", "19200", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("SerialPort", "115200", nullptr));

        comboBox_3->setItemText(0, QCoreApplication::translate("SerialPort", "5", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("SerialPort", "6", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("SerialPort", "7", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("SerialPort", "8", nullptr));

        comboBox_3->setCurrentText(QCoreApplication::translate("SerialPort", "8", nullptr));
        numberbit->setText(QCoreApplication::translate("SerialPort", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\346\225\260\346\215\256\344\275\215</span></p></body></html>", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("SerialPort", "1", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("SerialPort", "1.5", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("SerialPort", "2", nullptr));

        stopbit->setText(QCoreApplication::translate("SerialPort", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\345\201\234\346\255\242\344\275\215</span></p></body></html>", nullptr));
        comboBox_5->setItemText(0, QCoreApplication::translate("SerialPort", "none", nullptr));
        comboBox_5->setItemText(1, QCoreApplication::translate("SerialPort", "\345\245\207\346\240\241\351\252\214", nullptr));
        comboBox_5->setItemText(2, QCoreApplication::translate("SerialPort", "\345\201\266\346\240\241\351\252\214", nullptr));

        checkbit->setText(QCoreApplication::translate("SerialPort", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\346\240\241\351\252\214\344\275\215</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerialPort: public Ui_SerialPort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPORT_H
