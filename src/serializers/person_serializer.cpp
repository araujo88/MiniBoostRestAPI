#include "../include/serializers/person_serializer.hpp"

boost::json::object PersonSerializer::toJson(const Person &person) {
  boost::json::object obj;
  obj["name"] = person.name;
  obj["age"] = person.age;
  return obj;
}

Person PersonSerializer::fromJson(const boost::json::object &obj) {
  std::string name = obj.at("name").as_string().c_str();
  unsigned int age = obj.at("age").as_int64();
  return Person{name, age};
}
