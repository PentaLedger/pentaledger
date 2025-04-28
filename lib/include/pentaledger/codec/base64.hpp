/**
 * \file base64.hpp
 * \brief Base16, Base32, Base64, Base85 Data Encodings
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
#ifndef _LIBRFC_BASE64_HPP_
#define _LIBRFC_BASE64_HPP_
#include <iostream>
#include <string>
#include <vector>

/** @defgroup base64 Base64 Data Encoding and Decoding
 * 
 * This module contains functions for encoding binary data into printable
 * ASCII characters and decoding those encodings back to binary data, 
 * as specified in RFC 3548.
 * 
 * This encoding is designed to make binary data survive transport through 
 * transport layers that are not 8-bit clean, such as mail bodies.
 * 
 * Base64-encoded data takes about 33% more space than the original data.
 */
namespace libRFC {

/**
 * \brief Base64 Encoder/Decoder Utility Class
 * 
 * This class contains static methods to encode and/or decode base64.
 * 
 */
class Base64 {
public:
    //! \brief Get the number of characters required to decode a base64 string
    //!
    //! This function calculates the maximum number of bytes needed to decode a
    //! base64 string.
    //!
    //! \param n    number of bytes in the encoded base64 string which is going to be decoded.
    //!
    //! \returns
    //! This function returns the maximum number of bytes needed to decode a
    //! base64 string.
    static std::size_t max_decoded_size(std::size_t n)
    {
        return n / 4 * 3; // requires n&3==0, smaller
        //return 3 * n / 4;
    }

    //! \brief Get the maximum number of characters needed for an encoded string
    //!
    //! \param n    number of bytes of the unencoded string
    //!
    //! \returns
    //! This inline function returns the maximum number of characters
    //! needed to hold the encoded base64 string
    static std::size_t max_encoded_size(std::size_t n)
    {
        // (n+2)/3 gives the size, including the padded size
        return 4 * ((n + 2) / 3);
    }

    static bool encode_string(const std::string& in, std::string& out);
    static bool urlsafe_encode_string(const std::string& in, std::string& out);
    static bool encode_stream(std::istream& in, std::ostream& out);

    static bool decode_string(const std::string& in, std::string& out);
    static bool urlsafe_decode_string(const std::string& in, std::string& out);
    static bool decode_inplace(uint8_t* buffer);
};

}

/**@}*/

#endif
