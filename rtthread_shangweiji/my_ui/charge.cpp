#include "charge.h"
#include "ui_charge.h"
#include <QStandardItemModel>
#include "EventBus.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "crc.h"
#include "QSqlDatabase"
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "stdio.h"
#include <QTimer>

int times;

card_inf card_information;
charge_inf charge_information;
QByteArray m_buffer1;
QTimer* timer;
extern QSqlDatabase db ;

Charge::Charge(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Charge)
{
    ui->setupUi(this);

    model->setColumnCount(2);
// 设置表头名字
    model->setHorizontalHeaderLabels(QStringList() << "商品" << "价格");
// 绑定模型到tableView
    ui->table_view->setModel(model);
    ui->setting_card->setEnabled(false);
    connect(EventBus::instance(), &EventBus::serialDataReceived, this, &Charge::onDataReceived);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Charge::onTimeout);
    timer->stop();  // 一秒触发一次
    //model->clear();
    //model->removeRows(0, model->rowCount());
}

bool isItemInTable(const QString &itemName, QStandardItemModel *model) {
    for (int row = 0; row < model->rowCount(); ++row) {
        if (model->item(row, 1) && model->item(row, 0)->text() == itemName) {
            return true;
        }
    }
    return false;
}



void Charge::analysisByteArray(QByteArray data)
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


Charge::~Charge()
{
    delete ui;
}

void Charge::onDataReceived(const QByteArray &data)
{
    //int rowCount = ui->table_view->rowCount();
    //ui->table_view->insertRow(rowCount); // 在表格末尾插入一行
    processBuffer(data,m_buffer1);
    //qDebug() << "charge"<<data;
}


void Charge::processBuffer(QByteArray recBuf,QByteArray m_buffer) {
    m_buffer.append(recBuf);
    while (true) {
        // 查找帧头起始位置
        int headerPos = m_buffer.indexOf(0xA5);
        if (headerPos < 0) {
            m_buffer.clear();
            return;
        }

        // 移除头部的无效数据
        if (headerPos > 0) {
            m_buffer.remove(0, headerPos);
        }
        // 检查帧头完整性
        if (m_buffer.size() < sizeof(FrameHeader)) return;

        // 解析帧头
        FrameHeader header;
        memcpy(&header, m_buffer.constData(), sizeof(FrameHeader));
        qDebug()<<"header.CRC8"<<header.CRC8;
        // 验证CRC8
        if(  !Verify_CRC8_Check_Sum((unsigned char *)m_buffer.constData(), sizeof(FrameHeader))  )
        {
            m_buffer.remove(0, 1);
            continue;
        }
        // 计算完整包长度
        const int fullPacketSize = sizeof(FrameHeader) +
                                   sizeof(uint16_t) +    // cmd_id
                                   header.data_length +  // payload
                                   2 +                  // CRC16
                                   sizeof(MsgEnd);       // footer
        // 检查数据完整性
        if (m_buffer.size() < fullPacketSize) return;

        // 验证CRC16
        const int crc16Position = sizeof(FrameHeader) +
                                  sizeof(uint16_t) +
                                  header.data_length;

        uint16_t receivedCrc16;
        memcpy(&receivedCrc16, m_buffer.constData() + crc16Position, 2);

        MsgEnd footer;
        memcpy(&footer, m_buffer.constData() + fullPacketSize - sizeof(MsgEnd), sizeof(MsgEnd));
        if (footer.end1 != 0x0D) {
            m_buffer.remove(0, 1);
            continue;
        }
        // 提取命令ID
        uint16_t cmd_id;
        memcpy(&cmd_id, m_buffer.constData() + sizeof(FrameHeader), sizeof(uint16_t));
        switch (cmd_id)
        {
            case 0x01:
            {    memcpy(&card_information, m_buffer.constData() + sizeof(FrameHeader) + sizeof(uint16_t),
                       sizeof(card_information));
                QString receive_id = QString(card_information.id);
                if (card_information.lens > 4 &&
                    QString::compare(receive_id, ui->vip_card->text(), Qt::CaseInsensitive) != 0
                    && !ui->vip_card->isReadOnly())
                {
                    ui->vip_card->setText(receive_id);
                    char id_get[card_information.lens];
                    strncpy(id_get, card_information.id, card_information.lens);
                    qDebug() << "card_information:"<<card_information.id<<";"<<card_information.lens;
                    QString str(id_get);
                    //ui->vip_card->setText(str);
                    QSqlQuery sql_query;
                    sql_query.exec(QString("SELECT * FROM card WHERE id = '%1'").arg(receive_id));
                    if (sql_query.next())
                    {
                        QString rank = sql_query.value("rank").toString();
                        QString Phone = sql_query.value("Phone").toString();
                        QString pay_ = sql_query.value("pay_m").toString();
                        ui->staute->setText("已注册");
                        // 你可以将这些数据显示出来
                        qDebug() << rank << Phone;
                        ui->rank_get->setText(rank);
                        ui->phone_number->setText(Phone);
                        ui->pay_num->setText(pay_);

                    } else
                    {
                        ui->staute->setText("未注册");
                        ui->rank_get->setText("");
                        ui->phone_number->setText("");
                    }
                }
            }
                break;

            case 0x02:
            {
                memcpy(&charge_information, m_buffer.constData() + sizeof(FrameHeader) + sizeof(uint16_t), sizeof(charge_information));
                if(!isItemInTable(charge_information.name,model))
                {
                    QList<QStandardItem*> newRow;
//                    newRow << new QStandardItem(charge_information.id)  // 条形码
//                           << new QStandardItem(charge_information.name)        // 商品
//                           << new QStandardItem(QString::number(charge_information.price));   // 价格
                    newRow<< new QStandardItem(charge_information.name)        // 商品
                           << new QStandardItem(QString::number((float )charge_information.price/100));
                    model->appendRow(newRow);
                    update_data();
                    times=0;
                    if(model->rowCount()==1) timer->start(1000);
                }
            }break;
        }
        // 提取有效载荷
        QByteArray payload(m_buffer.constData() + sizeof(FrameHeader) + sizeof(uint16_t),
                           header.data_length);

        // 移除已处理数据
        m_buffer.remove(0, fullPacketSize);
    }
}

void Charge::on_setting_card_clicked()
{
    double totalPrice=0;
    for (int row = 0; row < model->rowCount(); ++row) {
        if (model->item(row, 1)) { // 第三列是价格列
            totalPrice += model->item(row, 1)->text().toDouble();
        }
    }
    int rank = ui->rank_get->text().toInt();
    float cut_off=1.0;
    if(rank == 1) cut_off=0.95;
    if(rank == 2) cut_off=0.9;

    QSqlQuery sql_query;
    totalPrice = cut_off * totalPrice;
    totalPrice = round(totalPrice * 100) / 100.0;

    double pay = ui->pay_num->text().toDouble();
    timer->stop();
    if(pay  >  totalPrice )
    {
        pay =  pay -   totalPrice;
        QByteArray data = "[2]";
        emit requestSendData(data);
        QString pp=QString::number(pay);

        QString cardNum = ui->vip_card->text();

        sql_query.prepare("UPDATE card SET pay_m = :newPay WHERE id = :id");
        sql_query.bindValue(":newPay", pp);
        sql_query.bindValue(":id", cardNum);
        if (!sql_query.exec()) {
            qDebug() << "Update card error:" << sql_query.lastError();
        } else {
            ui->pay_num->setText(pp);
            model->clear();
            ui->need_pay->clear();
            ui->cut_off->clear();
            ui->total_price->clear();
            model->removeRows(0, model->rowCount());
            show_charge_su_Message(pp,QString::number(totalPrice, 'f', 2));
            timer->stop();
            times=0;
        }
    }
    else
    {
        show_charge_fa_Message(QString::number(totalPrice, 'f', 2));
    }
}

void Charge::show_charge_su_Message(QString PP,QString need_pay)
{
    QString message = QString("成功支付:%1,余额:%2").arg(need_pay).arg(PP);
    QMessageBox::information(this, "提示", message);
}

void Charge::show_charge_fa_Message(QString need_pay)
{
    QString message = QString("余额不足,应支付%1").arg(need_pay);
    QMessageBox::information(this, "提示", message);
}


void Charge::on_load_clicked()
{
    //if(ui->vip_card)
    if(ui->load->text()=="登入")
    {
        ui->setting_card->setEnabled(true);
        ui->load->setText("登出");
        ui->vip_card->setReadOnly(true);
        ui->phone_number->setReadOnly(true);
        QSqlQuery sql_query;
        sql_query.exec(QString("SELECT * FROM card WHERE id = '%1'").arg(ui->vip_card->text()));
        if (sql_query.next())
        {
            QString rank = sql_query.value("rank").toString();
            QString Phone = sql_query.value("Phone").toString();
            QString pay_ = sql_query.value("pay_m").toString();
            ui->staute->setText("已注册");
            // 你可以将这些数据显示出来
            qDebug() << rank << Phone;
            ui->rank_get->setText(rank);
            ui->phone_number->setText(Phone);
            ui->pay_num->setText(pay_);

        } else
        {
            ui->staute->setText("未注册");
            ui->rank_get->setText("");
            ui->phone_number->setText("");
        }
    }
    else
    {
        ui->load->setText("登入");
        ui->vip_card->clear();
        ui->vip_card->setReadOnly(false);
        ui->phone_number->setReadOnly(false);
        ui->phone_number->clear();
        ui->rank_get->clear();
    }
}

void Charge::onTimeout()
{
    times++;
    //qDebug() << "time:" << times;
    if(times > 10)
    {
        QByteArray data = "[1]";
        qDebug() << "time:" << times;
        times=0;
        emit requestSendData(data);
    }
}

void Charge::update_data()
{
    double totalPrice=0;
    for (int row = 0; row < model->rowCount(); ++row) {
        if (model->item(row, 1)) { // 第三列是价格列
            totalPrice += model->item(row, 1)->text().toDouble();
        }
    }
    int rank = ui->rank_get->text().toInt();
    float cut_off=1.0;
    if(rank == 1) cut_off=0.95;
    if(rank == 2) cut_off=0.9;
    ui->total_price->setText(QString::number(totalPrice));
    QSqlQuery sql_query;
    totalPrice = cut_off * totalPrice;
    totalPrice = round(totalPrice * 100) / 100.0;
    ui->need_pay->setText(QString::number(totalPrice));
    ui->cut_off->setText(QString::number(cut_off));
}





