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

	company := &input

	if data.ValidateCompany(v, company); !v.Valid() {
		app.failedValidationResponse(w, r, v.Errors)
		return
	}
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
