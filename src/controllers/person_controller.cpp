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
    res.body() = "{\"success\": \"Person created.\"}";
    res.set(http::field::content_type, "application/json");
  } catch (const std::exception &e) {
    res.result(http::status::bad_request);
    res.body() = "Invalid JSON payload";
  }
}

void PersonController::getPersonById(Context &ctx) {
  auto &res = ctx.getResponse();

  try {
    unsigned int id = std::atoi(ctx.getParam("id").c_str());
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

void PersonController::deletePersonById(Context &ctx) {
  auto &res = ctx.getResponse();

  try {
    unsigned int id = std::atoi(ctx.getParam("id").c_str());

    if (personService->deletePersonById(id)) {
      res.result(http::status::no_content);
    } else {
      res.result(http::status::not_found);
      res.body() = "{\"error\": \"Person not found.\"}";
      res.set(http::field::content_type, "application/json");
    }
  } catch (const std::exception &e) {
    res.result(http::status::internal_server_error);
  }
}
