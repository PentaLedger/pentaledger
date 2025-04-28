/**
 * \file test_base64.cpp
 * \brief Base64 unit tests
 * 
 * This file is part of the libRFC distribution (https://github.com/alchemicure/libRFC).
 * Copyright (c) 2021 Joe Turner
 * 
 *  libRFC is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  libRFC is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with libRFC.  If not, see <https://www.gnu.org/licenses/>.
 * 
 */
#include <gtest/gtest.h>
#include <pentaledger/codec/base64.hpp>

using namespace libRFC ;

const char* rfc_4648_encoded[] = {
    "Zg==",
    "Zm8=",
    "Zm9v",
    "Zm9vYg==",
    "Zm9vYmE=",
    "Zm9vYmFy",
    ""
};

const char* rfc_4648_decoded[] = {
    "f",
    "fo",
    "foo",
    "foob",
    "fooba",
    "foobar",
    ""
};

TEST(base64, max_decoded_size)
{
    EXPECT_EQ((size_t)0, Base64::max_decoded_size(0));

    EXPECT_EQ((size_t)3, Base64::max_decoded_size(4));
    EXPECT_EQ((size_t)6, Base64::max_decoded_size(8));
}

TEST(base64, max_encoded_size)
{
    // zero bytes in, zero bytes out
    EXPECT_EQ((size_t)0, Base64::max_encoded_size(0));

    // 3 bytes in, 4 bytes out.
    EXPECT_EQ((size_t)4, Base64::max_encoded_size(1));
    EXPECT_EQ((size_t)4, Base64::max_encoded_size(2));
    EXPECT_EQ((size_t)4, Base64::max_encoded_size(3));

    EXPECT_EQ((size_t)8, Base64::max_encoded_size(4));
}

