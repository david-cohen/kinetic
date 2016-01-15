/*
 * Copyright (c) [2015 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
 */
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <string>
#include <thread>
#include <sstream>
#include <exception>
#include "Logger.hpp"
#include "SystemConfig.hpp"
#include "HeartbeatProvider.hpp"

/**
 * HeartbeatProvider Constructor
 *
 * Initialize the structure used to broadcast messages.
 */
HeartbeatProvider::HeartbeatProvider()
    : m_active(false), m_thread(nullptr), m_socketFd(-1) {

    memset(&m_address, 0, sizeof(m_address));
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = inet_addr(systemConfig.multicastIpAddress());
    m_address.sin_port = htons(systemConfig.multicastPort());
}

/**
 * Start
 *
 * @return true if the thread was successfully created
 *
 * Starts the heartbeat provider thread, which sends out a heartbeat message at a recurring interval
 * (around five seconds).
 */
bool
HeartbeatProvider::start() {

    try {
        m_active = true;
        m_thread = new std::thread(&HeartbeatProvider::run, this);
        return true;
    }
    catch (std::exception& e) {
        LOG(ERROR) << "Failed to create Heartbeat Provider thread: description=" << e.what();
        m_thread = nullptr;
        return false;
    }
}

/**
 * Open Socket
 *
 * @exception  a runtime error exception is thrown if the socket could not be opened and configured successfully
 *
 * Opens a datagram socket for sending multicast messages.
 */
void
HeartbeatProvider::openSocket() {

    const uint8_t MULTICAST_TTL(1);
    m_socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (m_socketFd == STATUS_FAILURE) {
        LOG(ERROR) << "Failed to create multicast socket: error_code=" << errno << ", description=" << strerror(errno);
        throw std::runtime_error("Failed to create multicast socket");
    }

    if (setsockopt(m_socketFd, IPPROTO_IP, IP_MULTICAST_TTL, &MULTICAST_TTL, sizeof(MULTICAST_TTL)) == STATUS_FAILURE) {
        LOG(ERROR) << "Failed to set socket options IP_MULTICAST_TTL: error_code=" << errno << ", description=" << strerror(errno);
        throw std::runtime_error("Failed to set socket options IP_MULTICAST_TTL");
    }
}

/**
 * Send Heartbeat Message
 *
 * @exception  a runtime error exception is thrown if the message wasn't sent successfully
 *
 * Send a kinetic heartbeat message to the multicast address.  Since some of the values in the
 * message can change, it must be built with the latest values before sending.
 */
void
HeartbeatProvider::sendHeartbeatMessage() {

    std::stringstream stream;
    stream << "{"
           << "\"manufacturer\":\"" << systemConfig.vendor() << "\","
           << "\"model\":\"" << systemConfig.model() << "\","
           << "\"firmware_version\":\"" << systemConfig.version() << "\","
           << "\"serial_number\":\"" << systemConfig.serialNumber() << "\","
           << "\"world_wide_name\":\"" << systemConfig.worldWideName() << "\","
           << "\"protocol_version\":\"" << systemConfig.protocolVersion() << "\","
           << "\"port\":" << systemConfig.tcpPort() << ","
           << "\"tlsPort\":" << systemConfig.sslPort() << ","
           << "\"network_interfaces\":[";

    auto interfaceCount = systemConfig.networkInterfaceMap().size();
    for (auto networkInterfaceSet : systemConfig.networkInterfaceMap()) {
        auto networkInterface = networkInterfaceSet.second;
        stream << "{\"name\":\"" << networkInterface->name() << "\","
               << "\"ipv4_addr\":\"" << networkInterface->ipv4() << "\","
               << "\"ipv6_addr\":\"" << networkInterface->ipv6() << "\","
               << "\"mac_addr\":\"" << networkInterface->macAddress() << "\"}";
        if (--interfaceCount > 0)
            stream << ",";
    }
    stream << "]}";
    std::string message = stream.str();

    if (sendto(m_socketFd, message.c_str(), message.length(), 0, (struct sockaddr*) &m_address, sizeof(m_address)) < 0)
        throw std::runtime_error("Failed to send multicast message");
}

/**
 * Run
 *
 * This is the function performed by the heartbeat provider thread.  It opens a multicast sockets
 * and sends heartbeat messages at the specified interval.
 */
void
HeartbeatProvider::run() {

    while (m_active) {
        try {
            openSocket();
            while (m_active) {
                sendHeartbeatMessage();
                sleep(systemConfig.heartbeatSendInterval());
            }
        }
        catch (std::exception& ex) {
            LOG(ERROR) << "Heartbeat Provider exception: " << ex.what();
            sleep(systemConfig.heartbeatConnectionRetryInterval());
        }
    }
}

/**
 * Stop
 *
 * Causes the heartbeat provider thread to terminate.
 */
void
HeartbeatProvider::stop() {

    m_active = false;
}

/**
 * Wait
 *
 * Causes the caller to be blocked until the thread ends.
 */
void
HeartbeatProvider::wait() {

    if (m_thread != nullptr)
        m_thread->join();
}
