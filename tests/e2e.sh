#!/bin/bash

curl -X POST -H "Content-Type: application/json" -d '{"name": "John Doe", "age": 30}' http://localhost:6969/person -v

curl http://localhost:6969/person -v
