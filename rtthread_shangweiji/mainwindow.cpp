#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "serialport.h"
#include "charge.h"
#include "card_id.h"
extern
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    eventBus = EventBus::instance();
    QStatusBar *sBar = statusBar();
    connect(serial->serialPort_,SIGNAL(readyRead()),this,SLOT(manual_serialPortReadyRead()));
    bool isConnected = connect(
            charge_view,
            &Charge::requestSendData,
            serial,
            &SerialPort::handleSerialSend
    );

    if(!isConnected) {
        qWarning() << "Connection failed!";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SerialPort_clicked()
{
     serial->show();
    serial->raise();
}


void MainWindow::on_chareg_clicked()
{
    charge_view->show();
    charge_view->raise();
}


void MainWindow::on_chareg_2_clicked()
{
    card_manage->show();
    card_manage->raise();
}

