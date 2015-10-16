/*
    Copyright (c) [2015] Western Digital Technologies, Inc. All rights reserved.
*/

/*
    Include Files
*/

#include <errno.h>
#include <stdint.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <thread>
#include <exception>
#include "Logger.hpp"
#include "SystemConfig.hpp"
#include "HeartbeatProvider.hpp"

/*
    Used Namespaces
*/

using std::string;

/**
    HeartbeatProvider Constructor

    Initailize the structure used to broadcast messages.
*/

HeartbeatProvider::HeartbeatProvider()
    : m_active(false), m_thread(nullptr), m_socketFd(-1) {

    memset(&m_address, 0, sizeof(m_address));
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = inet_addr(systemConfig.multicastIpAddress());
    m_address.sin_port = htons(systemConfig.multicastPort());
}

/**
    Start

    @return true if the thread was successfully created

    Starts the heartbeat provider thread, which sends out a heartbeat message at a recurring
    interval (around five seconds).
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
    Open Socket

    @exception  a runtime error exception is thrown if the socket could not be
                opened and configured successfully

    Causes a datagram socket on which to send multicast messages to be opened.
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
    Send Heartbeat Message

    @exception  a runtime error exception is thrown if the message wasn't sent successfully

    Send a kinetic heartbeat message to the multicast address.  Since some of the values in the
    message can change, it must be built with the latest values before sending.
*/

void
HeartbeatProvider::sendHeartbeatMessage() {

    boost::property_tree::ptree rootNode;
    rootNode.add("manufacturer", systemConfig.vendor());
    rootNode.add("model", systemConfig.model());
    rootNode.add("firmware_version", systemConfig.version());
    rootNode.add("serial_number", systemConfig.serialNumber());
    rootNode.add("world_wide_name", systemConfig.worldWideName());
    rootNode.add("protocol_version", systemConfig.protocolVersion());
    rootNode.add("port", systemConfig.tcpPort());
    rootNode.add("tlsPort", systemConfig.sslPort());

    boost::property_tree::ptree& interfaceListNode = rootNode.add("network_interfaces", "");
    for (auto networkInterfaceSet : systemConfig.networkInterfaceMap()) {
        auto networkInterface = networkInterfaceSet.second;
        boost::property_tree::ptree interfaceNode;
        interfaceNode.add("name", networkInterface->name());
        interfaceNode.add("ipv4_addr", networkInterface->ipv4());
        interfaceNode.add("ipv6_addr", networkInterface->ipv6());
        interfaceNode.add("mac_addr", networkInterface->macAddress());
        interfaceListNode.push_back(std::make_pair("", interfaceNode));
    }

    std::ostringstream outputStream;
    boost::property_tree::json_parser::write_json(outputStream, rootNode);
    string message = outputStream.str();

    if (sendto(m_socketFd, message.c_str(), message.length(), 0, (struct sockaddr*) &m_address, sizeof(m_address)) < 0)
        throw std::runtime_error("Failed to send multicast message");
}

/**
    Run

    This is the function performed by the heartbeat provider thread.  It opens a multicast sockets
    and sends heartbeat messages at the specified interval.
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
    Stop

    Causes the heartbeat provider thread to terminate.
*/

void
HeartbeatProvider::stop() {

    m_active = false;
}

/**
    Wait

    Causes the caller to be blocked until the thread ends.
*/

void
HeartbeatProvider::wait() {

    if (m_thread != nullptr)
        m_thread->join();
}

