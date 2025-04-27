/**
 *  @file: datafile.h
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
#ifndef _DATAFILE_H_
#define _DATAFILE_H_
#include <stdio.h>
#include <string.h>

#include "fileheader.h"

// This file is based in part from Al Steven's Book C Database Development

/**
 * \brief Database flat file
 *
 * This class contains the code necessary to create and maintain
 * a simple random access data file.
 */
class DataFile
{
public:
    DataFile();
    ~DataFile();

    /**
     * Read the file header from the file.
     *
     * \returns
     *  true if successful, false if failed.
     */
    inline bool read_header();

    /**
     * Write the file header to the file.
     *
     * \returns
     *  true if successful, false if failed.
     */
    inline bool write_header();

    /**
     * Given a logical record number, seek to the physical
     * record's location on disk.
     *
     * \param rcdno logical record number
     */
    inline void seek_record_number(RPTR rcdno);

    /**
     * \brief create a data file
     *
     * This function is used to create a data file and is called
     * from the database initialization routines when the files
     * for the database are initialized.  The name pointer points
     * to a filename of the intended data file.
     *
     * \param name  name of the data file to be created
     * \param len   record length
     *
     * \returns
     *  true if successful, false if failed.
     */
    bool create(char *name, int len);

    /**
     * \brief Open an existing data file
     *
     * This function opens an existing data file, one that was previously
     * created by create.
     *
     * \param name  name of the data file to be opened
     *
     * \returns
     * true if successful, false if failed.
     */
    bool open(char *name);

    /** \brief Close data file
     *
     * This function closes a data file.
     */
    void close();

    /**
     * \brief Read a record
     *
     * This function retrieves a record that was previously stored in the
     * data file.  The record_number is the logical record number where
     * the record is known to be stored.
     *
     * \param record_number logical record number
     * \param buffer  pointer to where the record will be stored.
     *
     * \returns
     * true if successful, false if failed.
     */
    bool read_record(RPTR record_number, void *buffer);

    /**
     * \brief Write a record
     *
     * This function writes/rewrites a record to the file and is used
     * when the record has been changed.  The record_number is the
     * logical record number where the record is to be stored.  The
     * buffer pointer points to the buffer from which the record will
     * be written
     *
     * \param record_number logical record number
     * \param buffer  pointer to where the record will be stored.
     *
     * \returns
     * true if successful, false if failed.
     */
    bool write_record(RPTR record_number, void *buffer);

    /**
     * \brief Delete a record
     *
     * This function deletes the record located at the logical record
     * position.  The record space is placed into a linked list for the file
     * so that later it can be overwritten by a newer record.
     */
    int delete_record(RPTR record_number);

    RPTR new_record(void *buffer);

private:
    FILE *fp;   //!< file pointer
    FHEADER hd; //!< cached file header
};

#endif
