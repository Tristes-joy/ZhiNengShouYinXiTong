#include "serialport.h"
#include "ui_serialport.h"
#include "QSerialPortInfo"
#include <QSerialPort>
#include <QMessageBox>
#include <QDateTime>
#include <QApplication>
#include <QMainWindow>
#include <QStatusBar>
#include <QLabel>
#include <string>
#include "EventBus.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "crc.h"

extern

SerialPort::SerialPort(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SerialPort)
{
    ui->setupUi(this);
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QStringList serialNamePort;

    serialPort_ = new QSerialPort(this);
    connect(serialPort_,SIGNAL(readyRead()),this,SLOT(manual_serialPortReadyRead()));
    ui->port_text->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->port_text->addItem(info.portName());
    }

    timSend = new QTimer;
    timSend->setInterval(1000);// 设置默认定时时长1000ms
}

SerialPort::~SerialPort()
{
    delete ui;
}

void SerialPort::on_cheek_clicked()
{
    ui->port_text->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->port_text->addItem(info.portName());
    }
}

void SerialPort::manual_serialPortReadyRead()
{
    QByteArray recBuf = serialPort_->readAll();
    qDebug() << "parseReceivedData" << recBuf;
    //processBuffer(recBuf);
    emit EventBus::instance()->serialDataReceived(recBuf);
    QString str_rev;
    recvNum += recBuf.size();
    ui->RX_text->setText(QString("%1").arg(recvNum));
    if(ui->hex_receive->checkState() == false){
        if(ui->time_s->checkState() == Qt::Checked){
            QDateTime nowtime = QDateTime::currentDateTime();
            str_rev = "[" + nowtime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
            str_rev += QString(recBuf).append("\r\n");
        }
        else{
            // 在当前位置插入文本，不会发生换行。如果没有移动光标到文件结尾，会导致文件超出当前界面显示范围，界面也不会向下滚动。
            //ui->recvEdit->appendPlainText(buf);
            if(ui->auto_line->checkState() == Qt::Checked){
                str_rev = QString(recBuf).append("\r\n");
            }
            else
            {
                str_rev = QString(recBuf);
            }
        }
    }else{

        // 16进制显示，并转换为大写
        QString str1 = recBuf.toHex().toUpper();//.data();
        // 添加空格
        QString str2;
        for(int i = 0; i<str1.length (); i+=2)
        {
            str2 += str1.mid (i,2);
            str2 += " ";
        }
        if(ui->time_s->checkState() == Qt::Checked)
        {
            QDateTime nowtime = QDateTime::currentDateTime();
            str_rev = "[" + nowtime.toString("yyyy-MM-dd hh:mm:ss") + "] ";
            str_rev += str2.append("\r\n");
        }
        else
        {
            if(ui->auto_line->checkState() == Qt::Checked)
                str_rev += str2.append("\r\n");
            else
                str_rev = str2;

        }
    }

    //ui->textEdit->insertPlainText(str_rev);

}
#pragma pack(push, 1)  // 确保1字节对齐
typedef struct {
    uint8_t SOF;
    uint16_t data_length;
    uint8_t seq;
    uint8_t CRC8;
} FrameHeader;

typedef struct {
    uint8_t end1;
} MsgEnd;

// CRC8计算（示例）
uint8_t calculateCRC8(const char *data, size_t length) {
    uint8_t crc = 0x00;
    while (length--) {
        crc ^= *data++;
        for (int i = 0; i < 8; i++) {
            crc = (crc & 0x80) ? (crc << 1) ^ 0x07 : (crc << 1);
        }
    }
    qDebug()<<"CRC8"<<crc;
    return crc;
}

// CRC16计算（示例：Modbus）
uint16_t calculateCRC16(const char *data, size_t length) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= static_cast<uint8_t>(data[i]);
        for (int j = 0; j < 8; j++) {
            crc = (crc & 0x0001) ? (crc >> 1) ^ 0xA001 : (crc >> 1);
        }
    }
    return crc;
}

//QByteArray m_buffer;
//const uint8_t HEADER_SOF = 0xA5;    // 帧头起始字节
//const uint8_t END1_SOF = 0x0D;      // 帧尾结束字节
//typedef struct
//{
//    uint16_t id;
//} vision_t;
//void processBuffer(QByteArray recBuf) {
//    m_buffer.append(recBuf);
//    while (true) {
//        // 查找帧头起始位置
//        int headerPos = m_buffer.indexOf(0xA5);
//        if (headerPos < 0) {
//            m_buffer.clear();
//            return;
//        }
//
//        // 移除头部的无效数据
//        if (headerPos > 0) {
//            m_buffer.remove(0, headerPos);
//        }
//
//        // 检查帧头完整性
//        if (m_buffer.size() < sizeof(FrameHeader)) return;
//
//        // 解析帧头
//        FrameHeader header;
//        memcpy(&header, m_buffer.constData(), sizeof(FrameHeader));
//        qDebug()<<"header.CRC8"<<header.CRC8;
//        // 验证CRC8
//        if(  !Verify_CRC8_Check_Sum((unsigned char *)m_buffer.constData(), sizeof(FrameHeader))  )
//        {
//            m_buffer.remove(0, 1);
//            continue;
//        }
//
//        // 计算完整包长度
//        const int fullPacketSize = sizeof(FrameHeader) +
//                                   sizeof(uint16_t) +    // cmd_id
//                                   header.data_length +  // payload
//                                   2 +                  // CRC16
//                                   sizeof(MsgEnd);       // footer
//
//        // 检查数据完整性
//        if (m_buffer.size() < fullPacketSize) return;
//
//        // 验证CRC16
//        const int crc16Position = sizeof(FrameHeader) +
//                                  sizeof(uint16_t) +
//                                  header.data_length;
//
//        uint16_t receivedCrc16;
//        memcpy(&receivedCrc16, m_buffer.constData() + crc16Position, 2);
//
//        MsgEnd footer;
//        memcpy(&footer, m_buffer.constData() + fullPacketSize - sizeof(MsgEnd), sizeof(MsgEnd));
//        if (footer.end1 != 0x0D) {
//            m_buffer.remove(0, 1);
//            continue;
//        }
//
//        // 提取命令ID
//        uint16_t cmdId;
//        memcpy(&cmdId, m_buffer.constData() + sizeof(FrameHeader), sizeof(uint16_t));
//        memcpy(&vv, m_buffer.constData() + sizeof(FrameHeader)+sizeof(uint16_t), sizeof(vision_t));
//        // 提取有效载荷
//        QByteArray payload(m_buffer.constData() + sizeof(FrameHeader) + sizeof(uint16_t),
//                           header.data_length);
//
//        // 移除已处理数据
//        m_buffer.remove(0, fullPacketSize);
//    }
//}




void SerialPort::on_openserialport_clicked()
{
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity checkBits;

    if(ui->bit_text->currentText()=="1200")
        baudRate=QSerialPort::Baud1200;
    else if(ui->bit_text->currentText()=="2400")
        baudRate=QSerialPort::Baud2400;
    else if(ui->bit_text->currentText()=="4800")
        baudRate=QSerialPort::Baud4800;
    else if(ui->bit_text->currentText()=="9600")
        baudRate=QSerialPort::Baud9600;
    else if(ui->bit_text->currentText()=="19200")
        baudRate=QSerialPort::Baud19200;
    else if(ui->bit_text->currentText()=="38400")
        baudRate=QSerialPort::Baud38400;
    else if(ui->bit_text->currentText()=="57600")
        baudRate=QSerialPort::Baud57600;
    else if(ui->bit_text->currentText()=="115200")
        baudRate=QSerialPort::Baud115200;

    // 获取串口数据位
    if(ui->numberbit_txt->currentText()=="5")
        dataBits=QSerialPort::Data5;
    else if(ui->numberbit_txt->currentText()=="6")
        dataBits=QSerialPort::Data6;
    else if(ui->numberbit_txt->currentText()=="7")
        dataBits=QSerialPort::Data7;
    else if(ui->numberbit_txt->currentText()=="8")
        dataBits=QSerialPort::Data8;

    // 获取串口停止位
    if(ui->stopbit_text->currentText()=="1")
        stopBits=QSerialPort::OneStop;
    else if(ui->stopbit_text->currentText()=="1.5")
        stopBits=QSerialPort::OneAndHalfStop;
    else if(ui->stopbit_text->currentText()=="2")
        stopBits=QSerialPort::TwoStop;

    // 获取串口奇偶校验位
    if(ui->checkbit_text->currentText() == "none"){
        checkBits = QSerialPort::NoParity;
    }else if(ui->checkbit_text->currentText() == "奇校验"){
        checkBits = QSerialPort::OddParity;
    }else if(ui->checkbit_text->currentText() == "偶校验"){
        checkBits = QSerialPort::EvenParity;
    }else{

    }

    // 初始化串口属性，设置 端口号、波特率、数据位、停止位、奇偶校验位数
    serialPort_->setPortName(ui->port_text->currentText());
    serialPort_->setBaudRate(baudRate);
    serialPort_->setDataBits(dataBits);
    serialPort_->setStopBits(stopBits);
    serialPort_->setParity(checkBits);

    if(ui->openserialport->text() == "打开串口")
    {
        if (serialPort_->open(QIODevice::ReadWrite) == true)
        {
            //QMessageBox::
            ui->openserialport->setText("关闭串口");
            // 让端口号下拉框不可选，避免误操作（选择功能不可用，控件背景为灰色）
            ui->port_text->setEnabled(false);
        } else
        {
            QMessageBox::critical(this, "错误提示", "串口打开失败！！！\r\n该串口可能被占用\r\n请选择正确的串口");
        }
    }
    else{
        serialPort_->close();
        ui->openserialport->setText("打开串口");
        // 端口号下拉框恢复可选，避免误操作
        ui->port_text->setEnabled(true);
        //statusBar 状态栏显示端口状态
    }
}

void SerialPort::setNumOnLabel(QLabel *lbl, QString strS, long num)
{
    // 标签显示
    QString str = strS + QString("num: %1").arg(num);
    lbl->setText(str);
}

void SerialPort::on_clear_text_clicked()
{
    ui->textEdit->clear();
}

void SerialPort::analysisByteArray(QByteArray data)
{
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data, &json_error));
    if(json_error.error != QJsonParseError::NoError){

        qDebug() << "json error!";
        return;
    }
    QJsonObject rootObj = jsonDoc.object();
    QStringList keys = rootObj.keys();
    for(int i = 0; i < keys.size(); i++){
        qDebug() << "key" << i << " is:" << keys.at(i) << rootObj.value(keys.at(i)).toString();
        if(!QString::localeAwareCompare(keys.at(i), "tem"))
        {

        }
        else if(!QString::localeAwareCompare(keys.at(i), "light"))
        {

        }
        else if(!QString::localeAwareCompare(keys.at(i), "humi"))
        {

        }
        else if(!QString::localeAwareCompare(keys.at(i), "led"))
        {

        }
        else if(!QString::localeAwareCompare(keys.at(i), "num"))
        {

        }
    }

}
void SerialPort::handleSerialSend(const QByteArray &data) {
    //qDebug() << "Sent:qDebug() << \"Update card error:\" << sql_query.lastError();" << data;
    if(serialPort_->isOpen()) {
        serialPort_->write(data);  // 实际发送数据
        qDebug() << "Sent:qDebug() << \"Update card error:\" << sql_query.lastError();" << data;
    }
}
