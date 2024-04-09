# MiniBoostRestAPI

This project is a simple HTTP server application written in C++ that demonstrates handling HTTP requests for managing `Person` entities using the Boost ASIO and Beast libraries. It showcases RESTful API design principles, implementing endpoints to retrieve and create person entities.

## Features

- RESTful API to manage person entities.
- Uses Boost libraries for network and HTTP functionalities.
- Demonstrates clean architecture, dependency injection, and SOLID principles.
- Simple CMake setup for easy building and configuration.
- e2e tests in Python.
- Powerful router.

## Prerequisites

Before you begin, ensure you have met the following requirements:

- C++20 compatible compiler (GCC, Clang, MSVC, etc.)
- [CMake](https://cmake.org/download/) version 3.14 or higher
- [Boost](https://www.boost.org/users/download/) libraries, version 1.71.0 or higher

## Building the Project

1. **Clone the repository:**

```bash
git clone https://github.com/araujo88/MiniBoostRestAPI.git
cd MiniBoostRestAPI
```

2. **Configure the project with CMake:**

```bash
mkdir build && cd build
cmake ..
```

3. **Build the project:**

```bash
cmake --build .
```

This will generate an executable file in the `build` directory.

## Running the Server

After building the project, you can run the server with the following command from the `build` directory:

```bash
./MiniBoostRestAPI  # or MiniBoostRestAPI.exe on Windows
```

By default, the server listens on port 6969. You can interact with the server using any HTTP client, such as `curl` or Postman, targeting the available endpoints.

## Available Endpoints

- `GET /person`: Retrieves a list of all person entities.
- `POST /person`: Creates a new person entity.
- `GET /person/{id}`: Retrieve a person entity by id.
- `DELETE /person/{id}`: Delete a person entity by id.

## License

This project is licensed under the MIT License - see the `LICENSE` file in the repository for details.
