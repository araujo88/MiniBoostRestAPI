#include "../include/controllers/person_controller.hpp"

void PersonController::getPersons(Context &ctx) {
  auto &res = ctx.getResponse();

  try {
    auto persons = personService->getAllPersons();
    boost::json::array jsonArray;
    for (const auto &person : persons) {
      jsonArray.push_back(PersonSerializer::toJson(person));
    }
    std::string jsonString = boost::json::serialize(jsonArray);
    res.result(http::status::ok);
    res.body() = jsonString;
    res.set(http::field::content_type, "application/json");
  } catch (const std::exception &e) {
    res.result(http::status::internal_server_error);
    res.body() = "{\"error\": \"Failed to serialize persons.\"}";
    res.set(http::field::content_type, "application/json");
  }
}

void PersonController::createPerson(Context &ctx) {
  auto &req = ctx.getRequest();
  auto &res = ctx.getResponse();

  try {
    auto json = boost::json::parse(req.body());
    auto person = PersonSerializer::fromJson(json.as_object());
    personService->addPerson(person);
    res.result(http::status::created);
    res.body() = "Person created";
  } catch (const std::exception &e) {
    res.result(http::status::bad_request);
    res.body() = "Invalid JSON payload";
  }
}

void PersonController::getPersonsById(Context &ctx) {
  auto &req = ctx.getRequest();
  auto &res = ctx.getResponse();

  try {
    // Convert the target to a standard string for easier manipulation
    std::string target = std::string(req.target());

    // Assuming the target format is "/person/{id}"
    std::size_t startPos =
        target.find("/person/") + 8; // +8 to move past "/person/"
    std::size_t endPos = target.find(
        '/', startPos); // Find the next slash in case there's more to the path

    // If there's no additional slash, endPos will be std::string::npos, and
    // substr will work correctly by default
    std::string idStr = target.substr(startPos, endPos - startPos);

    // Convert the extracted part to an unsigned int
    // Note: You might want to use a safer conversion method that can handle
    // errors.
    unsigned int id = std::atoi(idStr.c_str());

    auto person = personService->getPersonById(id);
    if (person) {
      std::string jsonString =
          boost::json::serialize(PersonSerializer::toJson(person.value()));
      res.result(http::status::ok);
      res.body() = jsonString;
      res.set(http::field::content_type, "application/json");
    } else {
      res.result(http::status::not_found);
      res.body() = "{\"error\": \"Person not found.\"}";
      res.set(http::field::content_type, "application/json");
    }
  } catch (const std::exception &e) {
    res.result(http::status::internal_server_error);
    res.body() = "{\"error\": \"Failed to serialize persons.\"}";
    res.set(http::field::content_type, "application/json");
  }
}
