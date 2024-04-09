#pragma once

#include <boost/json.hpp>
#include <boost/asio.hpp>
#include "person.hpp"

class PersonSerializer
{
public:
    static boost::json::object toJson(const Person &person);
    static Person fromJson(const boost::json::object &obj);
};
