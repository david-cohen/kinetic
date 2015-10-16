/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

/*
    Include Files
*/

#include <list>
#include "SystemConfig.hpp"
#include "TcpTransport.hpp"
#include "TransportManager.hpp"

/**
    Transport Manager Constructor
*/

TransportManager::TransportManager()
    : m_transportList() {
}

/**
    Transport Manager Destructor
*/
TransportManager::~TransportManager() {

    for (auto transport : m_transportList)
        delete transport;

    m_transportList.clear();
}

/**
    Start

    transportList   list of transports to manage
*/

void
TransportManager::start(std::list<TransportInterface*> transportList) {

    m_transportList = transportList;
    for (auto transport : m_transportList)
        transport->start();
}

/**
    Stop
*/

void
TransportManager::stop() {

    for (auto transport : m_transportList)
        transport->stop();
}

/**
    Wait
*/

void
TransportManager::wait() {

    for (auto transport : m_transportList)
        transport->wait();
}

/**
    Wait
*/

bool
TransportManager::connectionCount() {

    uint32_t connectionCount = 0;
    for (auto transport : m_transportList)
        connectionCount += transport->connectionCount();

    return connectionCount;
}
