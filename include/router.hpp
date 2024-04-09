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
  struct RouteKey {
    http::verb method;
    std::regex pathRegex;
    std::string pattern;

    // Constructor for easy route key creation
    RouteKey(http::verb method, const std::string &pathPattern)
        : method(method), pathRegex(std::regex(pathPattern)),
          pattern(pathPattern) {}
  };

  // Custom compare for the map to use regex
  struct RouteKeyCompare {
    bool operator()(const RouteKey &lhs, const RouteKey &rhs) const {
      if (lhs.method < rhs.method)
        return true;
      if (lhs.method > rhs.method)
        return false;
      // Compare the stored pattern strings
      return lhs.pattern < rhs.pattern;
    }
  };

  using HandlerFunc = std::function<void(Context &ctx)>;
  std::map<RouteKey, HandlerFunc, RouteKeyCompare> routes;
  std::string prefix;

public:
  void addRoute(http::verb method, const std::string &path,
                HandlerFunc handler);
  bool route(Context &ctx);
  void setPrefix(const std::string &prefix);
};
