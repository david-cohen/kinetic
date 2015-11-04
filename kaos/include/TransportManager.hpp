/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef TRANSPORT_MANAGER_HPP
#define TRANSPORT_MANAGER_HPP

/*
    Include Files
*/

#include <list>
#include "TransportInterface.hpp"

/**
    Transport Manager Class

    This class provides management of the system's transports (such as TCP).
*/

class TransportManager {

public:

    /*
        Constructor/Destructor
    */

    TransportManager();
    ~TransportManager();

    /*
        Public Member Functions
    */

    void start(std::list<TransportInterface*> transportList);
    void stop();
    void wait();
    uint32_t connectionCount();
    uint32_t batchCount();

private:

    std::list<TransportInterface*> m_transportList;
};

extern TransportManager transportManager;

#endif
