/**
 *  @file: datafile.c
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
#include <stdlib.h>

#include "datafile.h"

DataFile::DataFile() : fp(NULL)
{

}

DataFile::~DataFile()
{

}
void DataFile::close()
{
    if (fp != NULL)
    {
        write_header();
        fclose(fp);
        fp = NULL;
    }
}

bool DataFile::write_header()
{
    fseek(fp, 0L, SEEK_SET);
    int bytes = fwrite((char *)&hd, sizeof(hd), 1, fp);
    return true ? bytes == sizeof(hd) : false;
}

bool DataFile::read_header()
{
    fseek(fp, 0L, SEEK_SET);
    int bytes = fread((char *)&hd, sizeof(FHEADER), 1, fp);
    return true ? bytes == sizeof(hd) : false;
}

bool DataFile::create(char *name, int len)
{
    bool success = false;

    remove(name);
    fp = fopen(name, "wb");
    if (fp != NULL)
    {
        hd.init(len);
        write_header();
        close();
        success = true;
    }
    return success;
}

bool DataFile::open(char *name)
{
    bool success = false;
    close();
    fp = fopen(name, "rb+");
    if (fp != NULL)
    {
        read_header();
        success = true;
    }
    return success;
}

void DataFile::seek_record_number(RPTR record_number)
{
    fseek(fp, flocate(record_number, hd.record_length), SEEK_SET);
}

bool DataFile::read_record(RPTR record_number, void *buffer)
{
    bool success = false;

    if (record_number >= hd.next_record)
    {
        // error.
        return false;
    }
    seek_record_number(record_number);
    fread(buffer, hd.record_length, 1, fp);
    success = false;

    return success;
}

bool DataFile::write_record(RPTR record_number, void *buffer)
{
    bool success = false;
    if (record_number > hd.next_record)
    {
        // error.
        return false;
    }

    seek_record_number(record_number);
    fwrite(buffer, hd.record_length, 1, fp);
    success = true;

    return success;
}

int DataFile::delete_record(RPTR record_number)
{
    FHEADER *buffer = NULL;

    if (record_number > hd.next_record)
    {
        // error - can't delete a record that doesn't exist.
        return -1;
    }

    buffer = (FHEADER *)malloc(hd.record_length);
    if (buffer == NULL)
    {
        // out of memory
        return -1;
    }

    memset(buffer, '\0', hd.record_length);

    buffer->next_record = hd.first_record;
    buffer->first_record = -1;
    hd.first_record = record_number;
    write_record(record_number, buffer);

    free(buffer);
    return 0;
}

int stub_for_testing()
{
    return 0;
}
