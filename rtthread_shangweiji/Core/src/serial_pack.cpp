//
// Created by lth on 2025/5/27.
//

#include "serial_pack.h"
#include "serialport.h"
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

//void processBuffer(QByteArray recBuf,QByteArray m_buffer) {
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
//        // 计算完整包长度
//        const int fullPacketSize = sizeof(FrameHeader) +
//                                   sizeof(uint16_t) +    // cmd_id
//                                   header.data_length +  // payload
//                                   2 +                  // CRC16
//                                   sizeof(MsgEnd);       // footer
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
//        uint16_t cmd_id;
//        memcpy(&cmd_id, m_buffer.constData() + sizeof(FrameHeader), sizeof(uint16_t));
//        switch (cmd_id)
//        {
//            case 0x01:
//            {
//                memcpy(&card_information, m_buffer.constData() + sizeof(FrameHeader) + sizeof(uint16_t), sizeof(card_information));
//
//            }
//                break;
//            case 0x02:
//            {
//                memcpy(&charge_information, m_buffer.constData() + sizeof(FrameHeader) + sizeof(uint16_t), sizeof(charge_information));
//            }
//        }
//        // 提取有效载荷
//        QByteArray payload(m_buffer.constData() + sizeof(FrameHeader) + sizeof(uint16_t),
//                           header.data_length);
//
//        // 移除已处理数据
//        m_buffer.remove(0, fullPacketSize);
//    }
//}