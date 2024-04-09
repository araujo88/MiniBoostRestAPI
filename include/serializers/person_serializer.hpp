#pragma once

#include "../models/person.hpp"
#include <boost/asio.hpp>
#include <boost/json.hpp>

class PersonSerializer {
public:
  static boost::json::object toJson(const Person &person);
  static Person fromJson(const boost::json::object &obj);
};
