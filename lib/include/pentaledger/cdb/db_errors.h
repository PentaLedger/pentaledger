/**
 *  @file: db_errors.h
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
#ifndef _DB_ERRORS_H_
#define _DB_ERRORS_H_


//! DBMS error codes
enum dberrors {
    D_NF = 1,   // record not found
    D_PRIOR,    // no prior record for this request
    D_EOF,      // end of file
    D_BOF,      // beginning of file
    D_DUPL,     // primary key already exists
    D_OM,       // out of memory
    D_INDXC,    // index curruption
    D_IOERR,    // I/O error
};

#endif
