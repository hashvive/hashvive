// Copyright (c) 2015-2022 The Hashvive developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HASHVIVE_COMMON_URL_H
#define HASHVIVE_COMMON_URL_H

#include <string>
#include <string_view>

/* Decode a URL.
 *
 * Notably this implementation does not decode a '+' to a ' '.
 */
std::string UrlDecode(std::string_view url_encoded);

#endif // HASHVIVE_COMMON_URL_H
