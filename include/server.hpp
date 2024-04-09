#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class Server {
private:
  std::map<std::string,
           std::function<void(const http::request<http::string_body> &,
                              http::response<http::string_body> &)>>
      routeMap;
  short port;

public:
  Server(short port) : port(port) {}
  void addRoute(const std::string &route,
                std::function<void(const http::request<http::string_body> &,
                                   http::response<http::string_body> &)>
                    handler);
  void session(tcp::socket socket);
  void run();
  short getPort();
};