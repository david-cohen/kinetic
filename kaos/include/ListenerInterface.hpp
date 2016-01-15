/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef LISTENER_INTERFACE_HPP
#define LISTENER_INTERFACE_HPP

/*
 * Include Files
 */
#include <memory>

/*
 * Listener Interface
 *
 * Interface for a socket listener (for new connections).
 */
class ListenerInterface {

public:
    virtual bool start() = 0;
    virtual void stop() = 0;
};

/*
 * Listener Interface Pointer
 */
typedef std::shared_ptr<ListenerInterface> ListenerInterfacePtr;

#endif
