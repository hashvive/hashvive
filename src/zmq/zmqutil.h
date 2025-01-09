// Copyright (c) 2014-2021 The Hashvive developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HASHVIVE_ZMQ_ZMQUTIL_H
#define HASHVIVE_ZMQ_ZMQUTIL_H

#include <string>

void zmqError(const std::string& str);

/** Prefix for unix domain socket addresses (which are local filesystem paths) */
const std::string ADDR_PREFIX_IPC = "ipc://"; // used by libzmq, example "ipc:///root/path/to/file"

#endif // HASHVIVE_ZMQ_ZMQUTIL_H
