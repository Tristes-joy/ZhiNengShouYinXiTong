//
// Created by lth on 2025/4/28.
//

#ifndef BANK_RTTHREAD_EVENTBUS_H
#define BANK_RTTHREAD_EVENTBUS_H


#include <QObject>
#include <QByteArray>

class EventBus : public QObject {
Q_OBJECT  // 必须包含Q_OBJECT宏以支持信号/槽
public:
    static EventBus* instance();  // 获取单例实例
    ~EventBus();

signals:
    void serialDataReceived(const QByteArray &data);  // 串口数据接收信号
    //void sendSerialData(const QByteArray& data);
private:
    explicit EventBus(QObject *parent = nullptr);  // 私有构造函数
    static EventBus* m_instance;  // 静态成员变量声明
};

#endif //BANK_RTTHREAD_EVENTBUS_H
