/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc.
 *
 * This code is CONFIDENTIAL and a TRADE SECRET of Western Digital Technologies, Inc. and its
 * affiliates ("WD").  This code is protected under copyright laws as an unpublished work of WD.
 * Notice is for informational purposes only and does not imply publication.
 *
 * The receipt or possession of this code does not convey any rights to reproduce or disclose its
 * contents, or to manufacture, use, or sell anything that it may describe, in whole or in part,
 * without the specific written consent of WD.  Any reproduction or distribution of this code
 * without the express written consent of WD is strictly prohibited, is a violation of the copyright
 * laws, and may subject you to criminal prosecution.
 */
#pragma once
#ifndef LISTENER_INTERFACE_HPP
#define LISTENER_INTERFACE_HPP

/*
 * Include Files
 */
#include <memory>

/*
 * Interface for a socket listener (used for new connections).
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
