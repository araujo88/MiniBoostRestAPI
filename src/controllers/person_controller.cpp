#include "../include/controllers/person_controller.hpp"

void PersonController::getPersons(
    const http::request<http::string_body> &request,
    http::response<http::string_body> &response) {
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
}

void PersonController::createPerson(
    const http::request<http::string_body> &request,
    http::response<http::string_body> &response) {
  try {
    auto json = boost::json::parse(request.body());
    auto person = PersonSerializer::fromJson(json.as_object());
    personService->addPerson(person);
    response.result(http::status::created);
    response.body() = "Person created";
  } catch (const std::exception &e) {
    response.result(http::status::bad_request);
    response.body() = "Invalid JSON payload";
  }
}
