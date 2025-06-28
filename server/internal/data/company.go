// Copyright (c) 2025 Infinity Surge Inc.
// SPDX-License-Identifier: GPL-2.0
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; If not, see <http://www.gnu.org/licenses/>.
package data

import (
	"database/sql"
	"time"
)

type Company struct {
	ID        int64     `json:"id"`         // Unique integer ID for the company
	CreatedAt time.Time `json:"created_at"` // Timestamp for when the company is added to our database
	Name      string    `json:"name"`       // Company name
	Year      int32     `json:"year"`       // Year the company was founded
	Version   int32     `json:"version"`    // The version number starts at 1 and will be incremented each
	// time the Company information is updated
}

type CompanyModel struct {
	DB *sql.DB
}

func (m CompanyModel) Insert(Company *Company) error {
	return nil
}

func (m CompanyModel) Get(id int64) (*Company, error) {
	return nil, nil
}

func (m CompanyModel) Update(Company *Company) error {
	return nil
}

func (m CompanyModel) Delete(id int64) error {
	return nil
}
