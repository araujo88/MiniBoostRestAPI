#pragma once

#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <string>

class Person {
private:
  static unsigned int num_instances;
  unsigned int id;
  std::string name;
  unsigned int age;

public:
  Person(std::string name, unsigned int age);
  unsigned int getId() const;
  std::string getName() const;
  unsigned int getAge() const;
};
