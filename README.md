# PentaLedger
Financial Accounting Application

> [!IMPORTANT]  
> This software is not ready for end-user usage, yet. Check back in the future. 

PentaLedger is envisioned to be a full featured accounting solution
for small business owners and investors.

Originally, each of the components were isolated into their own respective 
repositories.  All of the software is currently in the process of being 
merged into this, singular mono repository.

This repository contains:

- The user interface (Sveltekit website)
- The REST API server
- Documentation

## Branch and Release Philosophy

- `main` branch is stable and versioned release are released off of main.
- `next` branch is next working development release (unstable)
- Pull requests mandatory against next branch.

## Docker Images in GitHub Registry

This project generates several docker images that are stored in
the github registry.  A docker compose that pulls everything 
together is forthcoming.