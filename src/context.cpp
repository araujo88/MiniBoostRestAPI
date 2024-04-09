#include "../include/context.hpp"

const http::request<http::string_body> &Context::getRequest() {
  return request;
}

http::response<http::string_body> &Context::getResponse() { return response; }

void Context::setResponseResult(http::status status, const std::string &body) {
  response.result(status);
  response.body() = body;
  response.prepare_payload(); // Ensure headers like Content-Length are set
}

void Context::setParam(const std::string &key, const std::string &value) {
  params[key] = value;
}

std::string Context::getParam(const std::string &key) const {
  auto it = params.find(key);
  if (it != params.end()) {
    return it->second;
  }
  return ""; // or throw, based on how you want to handle missing params
}