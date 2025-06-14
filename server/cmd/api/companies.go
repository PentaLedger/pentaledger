package main

import (
	"fmt"
	"net/http"

	"pentaledger.infinity-surge.com/internal/data" // New import
	"pentaledger.infinity-surge.com/internal/validator"
)

// Add a createCompanyHandler for the "POST /v1/company" endpoint. For now we simply
// return a plain-text placeholder response.
func (app *application) createCompanyHandler(w http.ResponseWriter, r *http.Request) {
	var input data.Company

	err := app.readJSON(w, r, &input)
	if err != nil {
		app.badRequestResponse(w, r, err)
		return
	}

	// Initialize a new Validator instance.
	v := validator.New()

	// Use the Check() method to execute our validation checks. This will add the
	// provided key and error message to the errors map if the check does not evaluate
	// to true. For example, in the first line here we "check that the title is not
	// equal to the empty string". In the second, we "check that the length of the title
	// is less than or equal to 500 bytes" and so on.

	v.Check(input.LegalName != "", "legal_name", "must be provided")
	v.Check(len(input.LegalName) <= 500, "legal_name", "must not be more than 500 bytes long")

	v.Check(input.EntityType != "", "entity_type", "must be provided")
	v.Check(len(input.EntityType) <= 500, "entity_type", "must not be more than 500 bytes long")

	v.Check(input.EIN != "", "ein", "must be provided")
	v.Check(len(input.EIN) <= 500, "ein", "must not be more than 500 bytes long")

	// Use the Valid() method to see if any of the checks failed. If they did, then use
	// the failedValidationResponse() helper to send a response to the client, passing
	// in the v.Errors map.
	if !v.Valid() {
		app.failedValidationResponse(w, r, v.Errors)
		return
	}

	fmt.Fprintf(w, "%+v\n", input)
	fmt.Fprintf(w, "%+v\n", input)
}

// Add a showCompanyHandler for the "GET /v1/company/:id" endpoint. For now, we retrieve
// the interpolated "id" parameter from the current URL and include it in a placeholder
// response.
func (app *application) showCompanyHandler(w http.ResponseWriter, r *http.Request) {

	id, err := app.readIDParam(r)
	if err != nil {
		http.NotFound(w, r)
		return
	}

	app.logger.Debug("company %d\n", id)
	// Create a new instance of the Movie struct, containing the ID we extracted from
	// the URL and some dummy data. Also notice that we deliberately haven't set a
	// value for the Year field.
	company := data.SampleCompany()

	err = app.writeJSON(w, http.StatusOK, envelope{"company": company}, nil)
	if err != nil {
		// Use the new serverErrorResponse() helper.
		app.serverErrorResponse(w, r, err)
	}

}
