package data

import (
	"time"

	"pentaledger.infinity-surge.com/internal/validator"
)

// Company represents a company in the system
type Company struct {
	ID               int64     `json:"id"`
	LegalName        string    `json:"legal_name"`
	EntityType       string    `json:"entity_type"`
	EIN              string    `json:"ein"`
	FiscalYearStart  string    `json:"fiscal_year_start"`
	Address          Address   `json:"address"`
	Contact          Contact   `json:"contact"`
	TaxYear          string    `json:"tax_year"`
	AccountingMethod string    `json:"accounting_method"`
	CreatedAt        time.Time `json:"created_at"`
	UpdatedAt        time.Time `json:"updated_at"`
}

// Address represents a company's address
type Address struct {
	Street  string `json:"street"`
	City    string `json:"city"`
	State   string `json:"state"`
	ZipCode string `json:"zip_code"`
}

// Contact represents a company's primary contact information
type Contact struct {
	Name  string `json:"name"`
	Email string `json:"email"`
	Phone string `json:"phone"`
}

func SampleCompany() Company {
	return Company{
		ID:              1,
		LegalName:       "Acme Corporation",
		EntityType:      "C Corporation",
		EIN:             "12-3456789",
		FiscalYearStart: "01-01",
		Address: Address{
			Street:  "123 Main Street",
			City:    "New York",
			State:   "NY",
			ZipCode: "10001",
		},
		Contact: Contact{
			Name:  "John Smith",
			Email: "john.smith@acmecorp.com",
			Phone: "212-555-0123",
		},
		TaxYear:          "2024",
		AccountingMethod: "Accrual",
		CreatedAt:        time.Now(),
		UpdatedAt:        time.Now(),
	}
}

func ValidateCompany(v *validator.Validator, company *Company) {
	v.Check(company.LegalName != "", "legal_name", "must be provided")
	v.Check(len(company.LegalName) <= 500, "legal_name", "must not be more than 500 bytes long")

	v.Check(company.EntityType != "", "entity_type", "must be provided")
	v.Check(len(company.EntityType) <= 500, "entity_type", "must not be more than 500 bytes long")

	v.Check(company.EIN != "", "ein", "must be provided")
	v.Check(len(company.EIN) <= 500, "ein", "must not be more than 500 bytes long")
}
