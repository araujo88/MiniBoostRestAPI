#pragma once

#include <vector>
#include "person.hpp"

class IPersonService
{
public:
    virtual void addPerson(const Person &person) = 0;
    virtual std::vector<Person> getAllPersons() = 0;
};

class PersonService : public IPersonService
{
private:
    std::vector<Person> persons;

public:
    void addPerson(const Person &person);
    std::vector<Person> getAllPersons();
};