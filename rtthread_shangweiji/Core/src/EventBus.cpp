//
// Created by lth on 2025/4/28.
//

#include "EventBus.h"


// 静态成员变量定义（必须写在.cpp中）
EventBus* EventBus::m_instance = nullptr;

EventBus* EventBus::instance() {
    if (!m_instance) {
        m_instance = new EventBus();  // 懒汉式单例
    }
    return m_instance;
}

EventBus::EventBus(QObject *parent) : QObject(parent) {
}

EventBus::~EventBus() {
}
