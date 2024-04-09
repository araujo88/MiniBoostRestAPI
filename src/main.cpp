#include "../include/person_request_handler.hpp"
#include "../include/person_service.hpp"
#include "../include/server.hpp"
#include <iostream>

int main(void) {
  try {
    auto server = Server(6969);
    auto personService = std::make_shared<PersonService>();
    auto handler = std::make_shared<PersonRequestHandler>(personService);
    std::cout << "Server starting on port " << server.getPort() << std::endl;
    server.run(handler);
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
