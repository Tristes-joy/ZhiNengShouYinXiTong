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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialPort
{
public:
    QWidget *widget;
    QTextEdit *textEdit;
    QGroupBox *groupBox;
    QPushButton *openserialport;
    QLabel *port;
    QPushButton *cheek;
    QLabel *stopbit;
    QComboBox *numberbit_txt;
    QLabel *checkbit;
    QComboBox *bit_text;
    QComboBox *port_text;
    QComboBox *checkbit_text;
    QLabel *bit;
    QLabel *numberbit;
    QComboBox *stopbit_text;
    QGroupBox *groupBox_2;
    QPushButton *clear_text;
    QCheckBox *hex_receive;
    QCheckBox *time_s;
    QCheckBox *auto_line;
    QGroupBox *groupBox_3;
    QCheckBox *autosend;
    QLabel *label;
    QSpinBox *sendtime;
    QCheckBox *hex_send;
    QCheckBox *send_line;
    QTextEdit *send_text;
    QPushButton *clear_send_text;
    QPushButton *send;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *RX_text;
    QLabel *TX_text;

    void setupUi(QWidget *SerialPort)
    {
        if (SerialPort->objectName().isEmpty())
            SerialPort->setObjectName("SerialPort");
        SerialPort->resize(645, 443);
        widget = new QWidget(SerialPort);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 641, 441));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        textEdit = new QTextEdit(widget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(250, 20, 371, 261));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 20, 151, 231));
        openserialport = new QPushButton(groupBox);
        openserialport->setObjectName("openserialport");
        openserialport->setGeometry(QRect(30, 200, 91, 21));
        port = new QLabel(groupBox);
        port->setObjectName("port");
        port->setGeometry(QRect(10, 20, 61, 21));
        port->setAlignment(Qt::AlignCenter);
        cheek = new QPushButton(groupBox);
        cheek->setObjectName("cheek");
        cheek->setGeometry(QRect(30, 170, 91, 21));
        stopbit = new QLabel(groupBox);
        stopbit->setObjectName("stopbit");
        stopbit->setGeometry(QRect(10, 110, 61, 21));
        stopbit->setAlignment(Qt::AlignCenter);
        numberbit_txt = new QComboBox(groupBox);
        numberbit_txt->addItem(QString());
        numberbit_txt->addItem(QString());
        numberbit_txt->addItem(QString());
        numberbit_txt->addItem(QString());
        numberbit_txt->setObjectName("numberbit_txt");
        numberbit_txt->setGeometry(QRect(80, 80, 62, 22));
        checkbit = new QLabel(groupBox);
        checkbit->setObjectName("checkbit");
        checkbit->setGeometry(QRect(10, 140, 61, 21));
        checkbit->setAlignment(Qt::AlignCenter);
        bit_text = new QComboBox(groupBox);
        bit_text->addItem(QString());
        bit_text->addItem(QString());
        bit_text->addItem(QString());
        bit_text->setObjectName("bit_text");
        bit_text->setGeometry(QRect(80, 50, 62, 22));
        port_text = new QComboBox(groupBox);
        port_text->setObjectName("port_text");
        port_text->setGeometry(QRect(80, 20, 62, 22));
        checkbit_text = new QComboBox(groupBox);
        checkbit_text->addItem(QString());
        checkbit_text->addItem(QString());
        checkbit_text->addItem(QString());
        checkbit_text->setObjectName("checkbit_text");
        checkbit_text->setGeometry(QRect(80, 140, 62, 22));
        bit = new QLabel(groupBox);
        bit->setObjectName("bit");
        bit->setGeometry(QRect(10, 50, 61, 21));
        bit->setAlignment(Qt::AlignCenter);
        numberbit = new QLabel(groupBox);
        numberbit->setObjectName("numberbit");
        numberbit->setGeometry(QRect(10, 80, 61, 21));
        numberbit->setAlignment(Qt::AlignCenter);
        stopbit_text = new QComboBox(groupBox);
        stopbit_text->addItem(QString());
        stopbit_text->addItem(QString());
        stopbit_text->addItem(QString());
        stopbit_text->setObjectName("stopbit_text");
        stopbit_text->setGeometry(QRect(80, 110, 62, 22));
        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(20, 250, 151, 71));
        clear_text = new QPushButton(groupBox_2);
        clear_text->setObjectName("clear_text");
        clear_text->setGeometry(QRect(10, 20, 51, 21));
        sizePolicy.setHeightForWidth(clear_text->sizePolicy().hasHeightForWidth());
        clear_text->setSizePolicy(sizePolicy);
        hex_receive = new QCheckBox(groupBox_2);
        hex_receive->setObjectName("hex_receive");
        hex_receive->setGeometry(QRect(70, 20, 71, 21));
        sizePolicy.setHeightForWidth(hex_receive->sizePolicy().hasHeightForWidth());
        hex_receive->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(8);
        hex_receive->setFont(font);
        time_s = new QCheckBox(groupBox_2);
        time_s->setObjectName("time_s");
        time_s->setGeometry(QRect(10, 47, 81, 21));
        sizePolicy.setHeightForWidth(time_s->sizePolicy().hasHeightForWidth());
        time_s->setSizePolicy(sizePolicy);
        time_s->setFont(font);
        auto_line = new QCheckBox(groupBox_2);
        auto_line->setObjectName("auto_line");
        auto_line->setGeometry(QRect(70, 47, 71, 21));
        sizePolicy.setHeightForWidth(auto_line->sizePolicy().hasHeightForWidth());
        auto_line->setSizePolicy(sizePolicy);
        auto_line->setFont(font);
        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(20, 320, 151, 71));
        autosend = new QCheckBox(groupBox_3);
        autosend->setObjectName("autosend");
        autosend->setGeometry(QRect(0, 47, 91, 21));
        sizePolicy.setHeightForWidth(autosend->sizePolicy().hasHeightForWidth());
        autosend->setSizePolicy(sizePolicy);
        autosend->setFont(font);
        label = new QLabel(groupBox_3);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 50, 16, 16));
        sendtime = new QSpinBox(groupBox_3);
        sendtime->setObjectName("sendtime");
        sendtime->setGeometry(QRect(70, 45, 51, 21));
        hex_send = new QCheckBox(groupBox_3);
        hex_send->setObjectName("hex_send");
        hex_send->setGeometry(QRect(0, 17, 81, 31));
        sizePolicy.setHeightForWidth(hex_send->sizePolicy().hasHeightForWidth());
        hex_send->setSizePolicy(sizePolicy);
        hex_send->setFont(font);
        send_line = new QCheckBox(groupBox_3);
        send_line->setObjectName("send_line");
        send_line->setGeometry(QRect(70, 27, 61, 21));
        sizePolicy.setHeightForWidth(send_line->sizePolicy().hasHeightForWidth());
        send_line->setSizePolicy(sizePolicy);
        send_line->setFont(font);
        send_text = new QTextEdit(widget);
        send_text->setObjectName("send_text");
        send_text->setGeometry(QRect(260, 300, 301, 64));
        clear_send_text = new QPushButton(widget);
        clear_send_text->setObjectName("clear_send_text");
        clear_send_text->setGeometry(QRect(570, 327, 71, 21));
        sizePolicy.setHeightForWidth(clear_send_text->sizePolicy().hasHeightForWidth());
        clear_send_text->setSizePolicy(sizePolicy);
        send = new QPushButton(widget);
        send->setObjectName("send");
        send->setGeometry(QRect(570, 350, 71, 18));
        sizePolicy.setHeightForWidth(send->sizePolicy().hasHeightForWidth());
        send->setSizePolicy(sizePolicy);
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(520, 421, 21, 20));
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(570, 420, 21, 21));
        RX_text = new QLabel(widget);
        RX_text->setObjectName("RX_text");
        RX_text->setGeometry(QRect(540, 422, 31, 20));
        TX_text = new QLabel(widget);
        TX_text->setObjectName("TX_text");
        TX_text->setGeometry(QRect(590, 420, 31, 20));
        groupBox_3->raise();
        groupBox->raise();
        textEdit->raise();
        groupBox_2->raise();
        send_text->raise();
        clear_send_text->raise();
        send->raise();
        label_2->raise();
        label_3->raise();
        RX_text->raise();
        TX_text->raise();

        retranslateUi(SerialPort);

        QMetaObject::connectSlotsByName(SerialPort);
    } // setupUi

    void retranslateUi(QWidget *SerialPort)
    {
        SerialPort->setWindowTitle(QCoreApplication::translate("SerialPort", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SerialPort", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        openserialport->setText(QCoreApplication::translate("SerialPort", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        port->setText(QCoreApplication::translate("SerialPort", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\347\253\257\345\217\243</span></p></body></html>", nullptr));
        cheek->setText(QCoreApplication::translate("SerialPort", "\346\243\200\346\265\213\344\270\262\345\217\243", nullptr));
        stopbit->setText(QCoreApplication::translate("SerialPort", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\345\201\234\346\255\242\344\275\215</span></p></body></html>", nullptr));
        numberbit_txt->setItemText(0, QCoreApplication::translate("SerialPort", "8", nullptr));
        numberbit_txt->setItemText(1, QCoreApplication::translate("SerialPort", "5", nullptr));
        numberbit_txt->setItemText(2, QCoreApplication::translate("SerialPort", "6", nullptr));
        numberbit_txt->setItemText(3, QCoreApplication::translate("SerialPort", "7", nullptr));

        numberbit_txt->setCurrentText(QCoreApplication::translate("SerialPort", "8", nullptr));
        checkbit->setText(QCoreApplication::translate("SerialPort", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\346\240\241\351\252\214\344\275\215</span></p></body></html>", nullptr));
        bit_text->setItemText(0, QCoreApplication::translate("SerialPort", "115200", nullptr));
        bit_text->setItemText(1, QCoreApplication::translate("SerialPort", "9600", nullptr));
        bit_text->setItemText(2, QCoreApplication::translate("SerialPort", "19200", nullptr));

        checkbit_text->setItemText(0, QCoreApplication::translate("SerialPort", "none", nullptr));
        checkbit_text->setItemText(1, QCoreApplication::translate("SerialPort", "\345\245\207\346\240\241\351\252\214", nullptr));
        checkbit_text->setItemText(2, QCoreApplication::translate("SerialPort", "\345\201\266\346\240\241\351\252\214", nullptr));

        bit->setText(QCoreApplication::translate("SerialPort", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\346\263\242\347\211\271\347\216\207</span></p></body></html>", nullptr));
        numberbit->setText(QCoreApplication::translate("SerialPort", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\346\225\260\346\215\256\344\275\215</span></p></body></html>", nullptr));
        stopbit_text->setItemText(0, QCoreApplication::translate("SerialPort", "1", nullptr));
        stopbit_text->setItemText(1, QCoreApplication::translate("SerialPort", "1.5", nullptr));
        stopbit_text->setItemText(2, QCoreApplication::translate("SerialPort", "2", nullptr));

        groupBox_2->setTitle(QCoreApplication::translate("SerialPort", "\346\216\245\346\224\266\350\256\276\347\275\256", nullptr));
        clear_text->setText(QCoreApplication::translate("SerialPort", "\346\270\205\347\251\272\346\216\245\346\224\266", nullptr));
        hex_receive->setText(QCoreApplication::translate("SerialPort", "Hex\346\216\245\346\224\266", nullptr));
        time_s->setText(QCoreApplication::translate("SerialPort", "\346\227\266\351\227\264\346\210\263", nullptr));
        auto_line->setText(QCoreApplication::translate("SerialPort", "\350\207\252\345\212\250\346\215\242\350\241\214", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SerialPort", "\345\217\221\351\200\201\350\256\276\347\275\256", nullptr));
        autosend->setText(QCoreApplication::translate("SerialPort", "\350\207\252\345\212\250\345\217\221\351\200\201", nullptr));
        label->setText(QCoreApplication::translate("SerialPort", "ms", nullptr));
        hex_send->setText(QCoreApplication::translate("SerialPort", "Hex\345\217\221\351\200\201", nullptr));
        send_line->setText(QCoreApplication::translate("SerialPort", "\350\207\252\345\212\250\346\215\242\350\241\214", nullptr));
        clear_send_text->setText(QCoreApplication::translate("SerialPort", "\346\270\205\347\251\272\345\217\221\351\200\201", nullptr));
        send->setText(QCoreApplication::translate("SerialPort", "\345\217\221\351\200\201", nullptr));
        label_2->setText(QCoreApplication::translate("SerialPort", "RX", nullptr));
        label_3->setText(QCoreApplication::translate("SerialPort", "TX", nullptr));
        RX_text->setText(QCoreApplication::translate("SerialPort", "0", nullptr));
        TX_text->setText(QCoreApplication::translate("SerialPort", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SerialPort: public Ui_SerialPort {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPORT_H
