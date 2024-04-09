#pragma once

#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <string>

class Person {
public:
  std::string name;
  unsigned int age;

  Person() = default;
  Person(std::string name, unsigned int age) : name(name), age(age) {}
};
