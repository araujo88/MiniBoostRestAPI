#include "../include/router.hpp"

void Router::addRoute(http::verb method, const std::string &path,
                      HandlerFunc handler) {
  routes[{method, path}] = std::move(handler);
}

bool Router::route(const http::request<http::string_body> &req,
                   http::response<http::string_body> &res) {
  auto it = routes.find({req.method(), req.target()});
  if (it != routes.end()) {
    it->second(req, res);
    return true;
  }

  // If no specific method route is found, check for a method-agnostic handler
  it = routes.find({http::verb::unknown, req.target()});
  if (it != routes.end()) {
    it->second(req, res);
    return true;
  }

  return false; // Route not found
}
