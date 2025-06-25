#!/bin/bash
#

curl -i localhost:4000/v1/healthcheck

curl -X POST localhost:4000/v1/company

curl -i localhost:4000/v1/company/123

# errors
echo "Testing error responses"
curl -i localhost:4000/fooxzq

curl -i localhost:4000/v1/company/abc

curl -i -X PUT localhost:4000/v1/healthcheck