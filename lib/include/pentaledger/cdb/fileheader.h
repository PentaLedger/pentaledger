/**
 *  @file: fileheader.h
 *
 *  Copyright (C) 2018  Joe Turner <joe@agavemountain.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef _FILE_HEADER_H_
#define _FILE_HEADER_H_
#include <stdint.h>

//! \brief Record Pointer
//! This is the record pointer and as a 32 bit entity, we can support
//! 2^32 possible records.  This is used as a b-tree node and file
//! address.
typedef uint32_t RPTR;

//! \brief File Header structure
//!
typedef struct fhdr {
    uint32_t first_record;

    //! Next available record.  This may be at the end of the file
    //! or may be pointing to a record previously marked for deletion.
    uint32_t next_record;

    //! Record length.
    uint16_t record_length;

    //! Initialize the structure.  These are the initial values for
    //! a newly created file.
    void init(uint16_t len)
    {
        next_record = 1;
        first_record = 0;
        record_length = len;
    }

} FHEADER;

//! Calculate the record location.
//! file header + record index * number
#define flocate(r,l) \
    ((uint32_t)( sizeof(FHEADER) + ( ( (r) -1 ) * (l) ) ) )
#endif
