#pragma once

#include "context.hpp"
#include <boost/beast.hpp>
#include <functional>
#include <map>
#include <memory>
#include <regex>
#include <string>

namespace http = boost::beast::http;

class Router {
private:
  struct RouteInfo {
    http::verb method;
    std::string pathPattern;
    std::function<void(Context &)> handler;
  };

  std::vector<RouteInfo> routes;
  std::string prefix;

  std::vector<std::string> splitPath(const std::string &path);

public:
  void addRoute(http::verb method, const std::string &pathPattern,
                std::function<void(Context &)> handler);
  bool route(Context &ctx);
  void setPrefix(const std::string &prefix);
};
