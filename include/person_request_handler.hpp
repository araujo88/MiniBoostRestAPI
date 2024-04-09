#pragma once

#include "request_handler.hpp"
#include "person_service.hpp"
#include "person_serializer.hpp"

class PersonRequestHandler : public IRequestHandler
{
private:
    std::shared_ptr<IPersonService> personService;

public:
    PersonRequestHandler(std::shared_ptr<IPersonService> service) : personService(service) {}
    void handleRequest(const http::request<http::string_body> &request, http::response<http::string_body> &response) override;
};
