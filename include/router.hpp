#pragma once

#include <boost/beast.hpp>
#include <functional>
#include <map>
#include <memory>

namespace http = boost::beast::http;

class Router {
private:
  using HandlerFunc =
      std::function<void(const http::request<http::string_body> &,
                         http::response<http::string_body> &)>;
  // Use a pair of method and path as the key
  std::map<std::pair<http::verb, std::string>, HandlerFunc> routes;
  std::string prefix;

public:
  void addRoute(http::verb method, const std::string &path,
                HandlerFunc handler);
  bool route(const http::request<http::string_body> &req,
             http::response<http::string_body> &res);
  void setPrefix(const std::string &prefix);
};
