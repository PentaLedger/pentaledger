package main

import (
	"fmt"
	"net/http"
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

	fmt.Fprintf(w, "show the details of movie %d\n", id)
}
