// SPDX-License-Identifier: GPL-2.0-only
/**
 * \file codec.hpp
 * \brief Base codec interface
 *
 * This file is part of the PentaLedger distribution (https://github.com/PentaLedger/pentaledger).
 * Copyright (c) 2025 Joe Turner
 *
 *  PentaLedger is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PentaLedger is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libRFC.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#ifndef _CODEC_HPP_
#define _CODEC_HPP_ 
#include <string>


namespace pentaledger {

    //! \brief Conversion of data formats
    namespace converter {

        class Converter {
            public:

            //
            virtual bool encode_string(const std::string &in, std::string &out) = 0;
            virtual bool encode_stream(std::istream &in, std::ostream &out) = 0;

            virtual bool decode_string(const std::string &in, std::string &out) = 0;
            virtual bool decode_inplace(uint8_t *buffer) = 0;
        };

    };
}



#endif