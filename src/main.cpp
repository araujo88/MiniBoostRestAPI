#include "../include/person_controller.hpp"
#include "../include/person_service.hpp"
#include "../include/server.hpp"
#include <iostream>

int main(void) {
  try {
    auto server = Server(6969);
    auto personService = std::make_shared<PersonService>();
    auto personController = std::make_shared<PersonController>(personService);

    server.addRoute("/person", [personController](
                                   const http::request<http::string_body> &req,
                                   http::response<http::string_body> &res) {
      if (req.method() == http::verb::get) {
        personController->getPersons(req, res);
      } else if (req.method() == http::verb::post) {
        personController->createPerson(req, res);
      } else {
        res.result(http::status::not_found);
        res.body() = "Resource not found";
      }
    });

    std::cout << "Server starting on port " << server.getPort() << std::endl;
    server.run();
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
