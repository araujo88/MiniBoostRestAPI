#include "../include/controllers/person_controller.hpp"
#include "../include/router.hpp"
#include "../include/server.hpp"
#include "../include/services/person_service.hpp"
#include <iostream>

int main(void) {
  try {
    auto router = std::make_shared<Router>();
    auto server = Server(6969, router);
    auto personService = std::make_shared<PersonService>();
    auto personController = std::make_shared<PersonController>(personService);

    router->setPrefix("/v1");

    router->addRoute(http::verb::get, "/person", [personController](auto &ctx) {
      personController->getPersons(ctx);
    });

    router->addRoute(
        http::verb::post, "/person",
        [personController](auto &ctx) { personController->createPerson(ctx); });

    router->addRoute(http::verb::get, "/person/{id}",
                     [personController](auto &ctx) {
                       personController->getPersonsById(ctx);
                     });

    std::cout << "Server starting on port " << server.getPort() << std::endl;
    server.run();
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
