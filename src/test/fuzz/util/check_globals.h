// Copyright (c) 2024-present The Hashvive developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HASHVIVE_TEST_FUZZ_UTIL_CHECK_GLOBALS_H
#define HASHVIVE_TEST_FUZZ_UTIL_CHECK_GLOBALS_H

#include <memory>
#include <optional>
#include <string>

struct CheckGlobalsImpl;
struct CheckGlobals {
    CheckGlobals();
    ~CheckGlobals();
    std::unique_ptr<CheckGlobalsImpl> m_impl;
};

#endif // HASHVIVE_TEST_FUZZ_UTIL_CHECK_GLOBALS_H
