#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QWidget>

#include <QSerialPort>
#include <QString>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <QMainWindow>
namespace Ui {
class SerialPort;
}

class SerialPort : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPort(QWidget *parent = nullptr);
    ~SerialPort();
    QSerialPort *serialPort_;
public slots:
    // 槽函数声明（参数必须匹配信号）
    void handleSerialSend(const QByteArray &data);
private slots:
    void on_cheek_clicked();

    void on_openserialport_clicked();
    void manual_serialPortReadyRead();
    void on_clear_text_clicked();

private:
    Ui::SerialPort *ui;
    QStatusBar *sBar;
    long sendNum, recvNum=2;
    QLabel *lblSendNum;
    QLabel *lblRecvNum;
    QLabel *lblPortState;

    void setNumOnLabel(QLabel *lbl, QString strS, long num);
    void parseReceivedData(const QByteArray& data);
    void analysisByteArray(QByteArray data);
    // 定时发送-定时器
    QTimer *timSend;


};
void processBuffer(QByteArray recBuf);
#endif // SERIALPORT_H
