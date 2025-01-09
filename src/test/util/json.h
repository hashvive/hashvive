// Copyright (c) 2023-present The Hashvive developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HASHVIVE_TEST_UTIL_JSON_H
#define HASHVIVE_TEST_UTIL_JSON_H

#include <univalue.h>

#include <string_view>

UniValue read_json(std::string_view jsondata);

#endif // HASHVIVE_TEST_UTIL_JSON_H
