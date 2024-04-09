#pragma once

#include "../serializers/person_serializer.hpp"
#include "../services/person_service.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class PersonController {
private:
  std::shared_ptr<IPersonService> personService;

public:
  PersonController(std::shared_ptr<IPersonService> service)
      : personService(service) {}

  void getPersons(const http::request<http::string_body> &request,
                  http::response<http::string_body> &response);
  void createPerson(const http::request<http::string_body> &request,
                    http::response<http::string_body> &response);
};
