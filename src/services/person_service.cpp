#include "../include/services/person_service.hpp"

void PersonService::addPerson(const Person &person) {
  persons.push_back(person);
}

std::vector<Person> PersonService::getAllPersons() { return persons; }

std::optional<Person> PersonService::getPersonById(unsigned int id) {
  for (auto &person : persons) {
    if (person.getId() == id)
      return person;
  }
  return std::nullopt;
}

bool PersonService::deletePersonById(unsigned int id) {
  for (auto it = persons.begin(); it != persons.end();) {
    if (it->getId() == id) {
      it = persons.erase(it);
      return true;
    } else {
      ++it;
    }
  }
  return false;
}