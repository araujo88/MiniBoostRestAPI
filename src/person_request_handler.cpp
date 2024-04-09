#include "../include/person_request_handler.hpp"

void PersonRequestHandler::handleRequest(
    const http::request<http::string_body> &request,
    http::response<http::string_body> &response) {

  std::cout << request.method_string() << " " << request.target() << " "
            << request.body() << std::endl;

  if (request.method() == http::verb::get && request.target() == "/person") {
    try {
      auto persons = personService->getAllPersons();
      boost::json::array jsonArray;
      for (const auto &person : persons) {
        jsonArray.push_back(PersonSerializer::toJson(person));
      }
      std::string jsonString = boost::json::serialize(jsonArray);
      response.result(http::status::ok);
      response.body() = jsonString;
      response.set(http::field::content_type, "application/json");
    } catch (const std::exception &e) {
      response.result(http::status::internal_server_error);
      response.body() = "{\"error\": \"Failed to serialize persons.\"}";
      response.set(http::field::content_type, "application/json");
    }
  } else if (request.method() == http::verb::post &&
             request.target() == "/person") {
    try {
      auto json = boost::json::parse(request.body());
      auto person = PersonSerializer::fromJson(json.as_object());
      personService->addPerson(person);
      response.result(http::status::created);
      response.body() = "Person added";
    } catch (const std::exception &e) {
      response.result(http::status::bad_request);
      response.body() = "Invalid JSON payload";
    }
  } else {
    response.result(http::status::not_found);
    response.body() = "Not found";
  }
}
