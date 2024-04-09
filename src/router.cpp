#include "../include/router.hpp"

void Router::addRoute(const std::string &path, HandlerFunc handler) {
  routes[path] = std::move(handler);
}

bool Router::route(const http::request<http::string_body> &req,
                   http::response<http::string_body> &res) {
  const auto &path = req.target();
  auto it = routes.find(path);
  if (it != routes.end()) {
    it->second(req, res);
    return true;
  }

  return false; // Route not found
}
