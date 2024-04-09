#pragma once

#include "../context.hpp"
#include "../serializers/person_serializer.hpp"
#include "../services/person_service.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <cstdlib>

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

  void getPersons(Context &ctx);
  void createPerson(Context &ctx);
  void getPersonById(Context &ctx);
  void deletePersonById(Context &ctx);
};
