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

    router->addRoute("/person", [personController](
                                    const http::request<http::string_body> &req,
                                    http::response<http::string_body> &res) {
      if (req.method() == http::verb::get) {
        personController->getPersons(req, res);
      } else if (req.method() == http::verb::post) {
        personController->createPerson(req, res);
      } else {
        res.result(http::status::method_not_allowed);
        res.body() = "Method Not Allowed";
        res.prepare_payload();
      }
    });

    std::cout << "Server starting on port " << server.getPort() << std::endl;
    server.run();
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
