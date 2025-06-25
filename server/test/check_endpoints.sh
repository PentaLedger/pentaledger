#!/bin/bash
#

curl localhost:4000/v1/healthcheck

curl -X POST localhost:4000/v1/company

curl localhost:4000/v1/company/123