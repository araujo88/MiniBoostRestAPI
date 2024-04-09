#pragma once

#include "context.hpp"
#include "router.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

#define GET (http::verb::get)
#define POST (http::verb::post)
#define PUT (http::verb::put)
#define PATCH (http::verb::patch)
#define DELETE (http::verb::delete_)

class Server {
private:
  short port;
  std::shared_ptr<Router> router;
  net::io_context io_context{1};

public:
  Server(short port, std::shared_ptr<Router> router)
      : port(port), router(std::move(router)) {}
  void session(tcp::socket socket);
  void run();
  short getPort();
};