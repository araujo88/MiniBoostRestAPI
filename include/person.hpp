#pragma once

#include <string>
#include <boost/json.hpp>
#include <boost/asio.hpp>

class Person
{
public:
    std::string name;
    int age;

    Person() = default;
    Person(std::string name, int age) : name(name), age(age) {}
};
