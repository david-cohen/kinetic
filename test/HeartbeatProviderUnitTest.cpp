/*
 * Copyright (c) 2014-2016 Western Digital Corporation or its affiliates <copyrightagent@wdc.com>
 * @author Gary Ballance <gary.ballance@wdc.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 * This file is part of Kinetic Advanced Object Store (KAOS).
 *
 * This program is free software: you may copy, redistribute and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA. <http://www.gnu.org/licenses/>
 */

/*
 * Include Files
 */
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/times.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <iomanip>
#include <sstream>
#include "gtest/gtest.h"
#include "Logger.hpp"
#include "GlobalConfig.hpp"
#include "HeartbeatProvider.hpp"

/*
 * Used Namespaces
 */
using std::string;
using boost::property_tree::ptree;

/*
 * Constants
 */
static const char*   NOT_FOUND_STRING = "Not found";
static const int32_t CONNECTION_HAS_NO_DATA_TO_RECEIVE = 0;
static const int32_t CONNECTION_HAS_DATA_TO_RECEIVE = 1;
static const int32_t ONE_TICK = 1;
static const int32_t ONE_SECOND = 1;
static const int32_t DOUBLE_INTERVAL = 2;
static const int32_t KNOWN_INCORRECT_PORT_NUMBER = 0;
static const int     MESSAGE_BUFFER_SIZE = 2048;

/*
 * Data Types
 */
class MulticastConnection {
public:
    int     socketfd;
    char    messageBuffer[MESSAGE_BUFFER_SIZE];
    ptree   messageNode;

    MulticastConnection() {
        socketfd = 0;
        memset(messageBuffer, 0, MESSAGE_BUFFER_SIZE);
    }
};

/*
 * Data Objects
 */
LogControl logControl;
GlobalConfig  globalConfig;

/**
 * Create Connection
 *
 * @param  connection  contains information about the multicast connection
 *
 * Creates the multicast connection, joining the multicast group so that it will receive any
 * messages broadcast to the multicast IP address and port specified.
 */
void createConnection(MulticastConnection& connection) {
    connection.socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    ASSERT_NE(connection.socketfd, STATUS_FAILURE) << "Failed to create socket: Error Code=" << errno << ", Description=" << strerror(errno);

    const int OPTION_SET(1);
    ASSERT_NE(setsockopt(connection.socketfd, SOL_SOCKET, SO_REUSEADDR, &OPTION_SET, sizeof(OPTION_SET)), STATUS_FAILURE)
            << "Failed to set socket options SO_REUSEADDR: Error Code=" << errno << ", Description=" << strerror(errno);

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(globalConfig.multicastPort());
    ASSERT_NE(bind(connection.socketfd, (struct sockaddr*) &server, sizeof(struct sockaddr)), STATUS_FAILURE)
            << "Failed to bind socket: Error Code=" << errno << ", Description=" << strerror(errno);

    struct ip_mreq group;
    memset(&group, 0, sizeof(group));
    group.imr_multiaddr.s_addr = inet_addr(globalConfig.multicastIpAddress());
    ASSERT_NE(setsockopt(connection.socketfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group)), STATUS_FAILURE)
            << "Failed to set socket options IP_ADD_MEMBERSHIP: Error Code=" << errno << ", Description=" << strerror(errno);
}

/**
 * Get Message
 *
 * @param  connection  contains connection information as well as the message buffer
 *
 * Reads the next multicast message (blocking until it is received).
 */
void getMessage(MulticastConnection& connection) {
    int32_t byteCount = read(connection.socketfd, connection.messageBuffer, MESSAGE_BUFFER_SIZE);
    ASSERT_GT(byteCount, 0);
    std::istringstream stream(connection.messageBuffer);
    boost::property_tree::json_parser::read_json(stream, connection.messageNode);
}

/**
 * I/O Ready Status
 *
 * @param  connection  contains information about the multicast connection
 *
 * @return  1 if I/O is ready to be performed on the connection
 *          0 if I/O is not ready to be performed on the connection
 *         -1 if an error was encountered checking if I/O was ready
 */
bool ioReadyStatus(MulticastConnection& connection) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(connection.socketfd, &readfds);

    struct timeval timeout;
    memset(&timeout, 0, sizeof(timeout));
    timeout.tv_sec = globalConfig.heartbeatSendInterval() * DOUBLE_INTERVAL;

    return select(connection.socketfd + 1, &readfds, nullptr, nullptr, &timeout);
}

/**
 * Validate Message
 *
 * @param  connection  contains the last message received
 *
 * Check that the contents of the heartbeat message are correct.
 */
void validateMessage(MulticastConnection& connection) {
    string manufacturer = connection.messageNode.get<string>("manufacturer", NOT_FOUND_STRING);
    ASSERT_STREQ(globalConfig.vendor(), manufacturer.c_str());

    string model = connection.messageNode.get<string>("model", NOT_FOUND_STRING);
    ASSERT_STREQ(globalConfig.model(), model.c_str());

    string version = connection.messageNode.get<string>("firmware_version", NOT_FOUND_STRING);
    ASSERT_STREQ(globalConfig.version(), version.c_str());

    string serialNumber = connection.messageNode.get<string>("serial_number", NOT_FOUND_STRING);
    ASSERT_STREQ(globalConfig.serialNumber().c_str(), serialNumber.c_str());

    string worldWideName = connection.messageNode.get<string>("world_wide_name", NOT_FOUND_STRING);
    ASSERT_STREQ(globalConfig.worldWideName().c_str(), worldWideName.c_str());

    string protocolVersion = connection.messageNode.get<string>("protocol_version", NOT_FOUND_STRING);
    ASSERT_STREQ(globalConfig.protocolVersion(), protocolVersion.c_str());

    uint32_t tcpPort = connection.messageNode.get<uint32_t>("port", KNOWN_INCORRECT_PORT_NUMBER);
    ASSERT_EQ(globalConfig.tcpPort(), tcpPort);

    uint32_t sslPort = connection.messageNode.get<uint32_t>("tlsPort", KNOWN_INCORRECT_PORT_NUMBER);
    ASSERT_EQ(globalConfig.sslPort(), sslPort);

    NetworkInterfaceList networkInterfaceList = globalConfig.networkInterfaceList();

    bool foundNetworkInterface = false;
    for (boost::property_tree::ptree::value_type& node : connection.messageNode.get_child("network_interfaces")) {
        string name = node.second.get<string>("name", NOT_FOUND_STRING);
        for (auto networkInterface : networkInterfaceList) {
            if (networkInterface->name() == name) {
                string ipv4 = node.second.get<string>("ipv4_addr", NOT_FOUND_STRING);
                ASSERT_STREQ(networkInterface->ipv4().c_str(), ipv4.c_str());

                string ipv6 = node.second.get<string>("ipv6_addr", NOT_FOUND_STRING);
                ASSERT_STREQ(networkInterface->ipv6().c_str(), ipv6.c_str());

                string macAddress = node.second.get<string>("mac_addr", NOT_FOUND_STRING);
                ASSERT_STREQ(networkInterface->macAddress().c_str(), macAddress.c_str());
                foundNetworkInterface = true;
                break;
            }
        }
    }
    ASSERT_TRUE(foundNetworkInterface);
}

/**
 * Broadcast Test
 *
 * Verify that message is broadcast to the correct multicast IP address and port.
 */
TEST(Heartbeat_Provider_Unit_Test, Broadcast_Test) {
    MulticastConnection connection;
    ASSERT_NO_FATAL_FAILURE(createConnection(connection));

    HeartbeatProvider heartbeatProvider;
    heartbeatProvider.start();

    ASSERT_EQ(ioReadyStatus(connection), CONNECTION_HAS_DATA_TO_RECEIVE);

    heartbeatProvider.stop();
    heartbeatProvider.wait();
}

/**
 * Message Content Test
 *
 * Verify that the contents the heartbeat message are correct.
 */
TEST(Heartbeat_Provider_Unit_Test, Message_Content_Test) {
    MulticastConnection connection;
    ASSERT_NO_FATAL_FAILURE(createConnection(connection));

    HeartbeatProvider heartbeatProvider;
    heartbeatProvider.start();

    ASSERT_NO_FATAL_FAILURE(getMessage(connection));
    std::cout << "Message Contents: " << std::endl << connection.messageBuffer << std::endl;
    ASSERT_NO_FATAL_FAILURE(validateMessage(connection));

    heartbeatProvider.stop();
    heartbeatProvider.wait();
}

/**
 * Broadcast Interval Test
 *
 * Verify that the heartbeat messages are broadcast are the correct interval.
 */
TEST(Heartbeat_Provider_Unit_Test, Broadcast_Interval_Test) {
    MulticastConnection connection;
    ASSERT_NO_FATAL_FAILURE(createConnection(connection));

    HeartbeatProvider heartbeatProvider;
    heartbeatProvider.start();

    ASSERT_NO_FATAL_FAILURE(getMessage(connection));
    ASSERT_NO_FATAL_FAILURE(validateMessage(connection));

    ASSERT_NO_FATAL_FAILURE(getMessage(connection));
    clock_t startTime = times(NULL);
    ASSERT_NO_FATAL_FAILURE(validateMessage(connection));

    ASSERT_NO_FATAL_FAILURE(getMessage(connection));
    clock_t endTime = times(NULL);
    ASSERT_NO_FATAL_FAILURE(validateMessage(connection));

    int64_t ticksPerSecond = sysconf(_SC_CLK_TCK);
    int64_t elapsedTimeInTicks = endTime - startTime;
    int64_t expectedElapsedTimeInTicks = globalConfig.heartbeatSendInterval() * ticksPerSecond;

    std::cout << "Time between messages: " << static_cast<float>(elapsedTimeInTicks) / static_cast<float>(ticksPerSecond)
              << " seconds" << std::endl;
    ASSERT_GE(elapsedTimeInTicks, expectedElapsedTimeInTicks - ONE_TICK);
    ASSERT_LE(elapsedTimeInTicks, expectedElapsedTimeInTicks + ONE_TICK);

    heartbeatProvider.stop();
    heartbeatProvider.wait();
}

/**
 * Halt Broadcast Test
 *
 * Verify that the heartbeat provder does not send heartbeat messages after it has been stopped.
 */
TEST(Heartbeat_Provider_Unit_Test, Halt_Broadcast_Test) {
    MulticastConnection connection;
    ASSERT_NO_FATAL_FAILURE(createConnection(connection));

    HeartbeatProvider heartbeatProvider;
    heartbeatProvider.start();

    ASSERT_NO_FATAL_FAILURE(getMessage(connection));
    ASSERT_NO_FATAL_FAILURE(validateMessage(connection));

    heartbeatProvider.stop();
    sleep(ONE_SECOND);
    ASSERT_EQ(ioReadyStatus(connection), CONNECTION_HAS_NO_DATA_TO_RECEIVE);
    heartbeatProvider.wait();
}

int main(int argc, char** argv) {
    std::cout << "Notice: No other Kinetic device can be broadcasting heartbeat messages on this network" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

