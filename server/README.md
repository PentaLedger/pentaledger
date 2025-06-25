# PentaLedger API server

## Running application

`go run ./cmd/api`

## Command line arguments 

To specify port, and environment:

` go run ./cmd/api -port=3030 -env=production`

## Building docker image

```
docker build -t pentaledger-api-server .
```