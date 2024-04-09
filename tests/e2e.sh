#!/bin/bash

curl -X POST -H "Content-Type: application/json" -d '{"name": "John Doe", "age": 30}' http://localhost:6969/v1/person -v

curl -X PUT -H "Content-Type: application/json" -d '{"name": "John Doe", "age": 30}' http://localhost:6969/v1/person -v

curl http://localhost:6969/v1/person -v

curl http://localhost:6969/42 -v

curl http://localhost:6969/v1/person/0 -v

curl http://localhost:6969/v1/person/42 -v
