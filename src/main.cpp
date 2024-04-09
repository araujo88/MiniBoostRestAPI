#include "../include/person_controller.hpp"
#include "../include/person_service.hpp"
#include "../include/router.hpp"
#include "../include/server.hpp"
#include <iostream>

int main(void) {
  try {
    auto router = std::make_shared<Router>();
    auto server = Server(6969, router);
    auto personService = std::make_shared<PersonService>();
    auto personController = std::make_shared<PersonController>(personService);

    router->addRoute(http::verb::get, "/person",
                     [personController](const auto &req, auto &res) {
                       personController->getPersons(req, res);
                     });
    router->addRoute(http::verb::post, "/person",
                     [personController](const auto &req, auto &res) {
                       personController->createPerson(req, res);
                     });

    std::cout << "Server starting on port " << server.getPort() << std::endl;
    server.run();
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
