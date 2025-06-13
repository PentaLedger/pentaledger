package main

import (
	"fmt"
	"net/http"

	"pentaledger.infinity-surge.com/internal/data" // New import
)

// Add a createCompanyHandler for the "POST /v1/company" endpoint. For now we simply
// return a plain-text placeholder response.
func (app *application) createCompanyHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintln(w, "create a new company")
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

	// Encode the struct to JSON and send it as the HTTP response.
	err = app.writeJSON(w, http.StatusOK, company, nil)
	if err != nil {
		app.logger.Error(err.Error())
		http.Error(w, "The server encountered a problem and could not process your request", http.StatusInternalServerError)
	}

}
