# e2e tests

This directory contains end-to-end tests for the MiniBoostRestAPI project, ensuring that all components work together correctly and the API behaves as expected. The tests are written using the `pytest` framework, with the `pytest-order` plugin to manage the execution order of certain tests where dependencies exist.

## Prerequisites

Before running the tests, ensure you have the following installed:

- Python 3.6 or newer
- `pytest`
- `pytest-order`
- `requests` library

You can install the necessary Python packages by running:

```sh
pip install -r requirements.txt
```

Ensure that the MiniBoostRestAPI server is running and accessible at the expected address (default: `http://localhost:6969`).

## Running the Tests

To run all tests, navigate to the root directory of the MiniBoostRestAPI project and execute the following command:

```sh
pytest
```

To run tests in verbose mode, which includes more detailed output, use the `-v` flag:

```sh
pytest -v
```

## Test Files

- `e2e_test.py`: Contains end-to-end tests verifying the functionality of the entire API, from creating and retrieving persons to deleting them. These tests are intended to simulate real-world usage of the API and ensure that all components of the application work together as expected.

## Test Structure

Tests are organized to reflect the API's structure, covering:

- POST requests to create new persons.
- GET requests to retrieve existing persons.
- PUT requests to update person details (not included in the initial example but can be added following the existing pattern).
- DELETE requests to remove persons from the system.

Tests that depend on the creation of resources (like retrieving or deleting a person) are executed in a specific order, leveraging the `pytest-order` plugin to ensure consistency and reliability of test outcomes.

## Contributing Tests

When contributing new tests or modifying existing ones:

- Ensure that new tests are as independent as possible, avoiding dependencies on the execution order of other tests.
- Follow the naming conventions (`test_*.py` for test files and `test_*` for test functions) to ensure `pytest` discovers and executes all tests.
- Document any new dependencies or setup requirements in this README.

## Further Information

For more details on `pytest` and writing tests, refer to the [pytest documentation](https://docs.pytest.org/en/latest/).
