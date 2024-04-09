#include "../include/person_service.hpp"

void PersonService::addPerson(const Person &person)
{
    persons.push_back(person);
}

std::vector<Person> PersonService::getAllPersons()
{
    return persons;
}