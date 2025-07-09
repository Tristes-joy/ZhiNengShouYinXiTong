#ifndef CHARGE_H
#define CHARGE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QMessageBox>
namespace Ui {
class Charge;
}

class Charge : public QMainWindow
{
    Q_OBJECT

public:
    explicit Charge(QWidget *parent = nullptr);
    void analysisByteArray(QByteArray data);
    ~Charge();
    void  onDataReceived(const QByteArray &data);
    void processBuffer(QByteArray recBuf,QByteArray m_buffer);
    QStandardItemModel* model = new QStandardItemModel(this);
    void show_charge_su_Message(QString PP,QString need_pay);
    void show_charge_fa_Message(QString need_pay);
    void update_data();
signals:
    // 信号声明
    void requestSendData(const QByteArray &data);
private slots:
    void on_setting_card_clicked();
    void onTimeout();
    void on_load_clicked();
private:
    Ui::Charge *ui;
    int rowCount;
};
//void processBuffer(QByteArray recBuf,QByteArray m_buffer);
typedef struct {
    uint8_t SOF;
    uint8_t data_length;
    uint8_t seq;
    uint8_t CRC8;
} FrameHeader;


typedef struct {
    uint8_t end1;
} MsgEnd;

typedef struct
{
    uint8_t lens;
    char id[10];
} card_inf;

typedef struct
{
//    uint8_t id_len;
//    uint8_t nam_len;
//    char id[10];
//    char name[10];
//    uint16_t price;
    uint8_t nam_len;
    char name[10];
    uint16_t price;
    //float price;
}  charge_inf;

//card_inf card_information;
//charge_inf charge_information;

const uint8_t HEADER_SOF = 0xA5;    // 帧头起始字节
const uint8_t END1_SOF = 0x0D;      // 帧尾结束字节

#endif // CHARGE_H
