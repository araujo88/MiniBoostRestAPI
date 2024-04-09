#pragma once

#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <map>

namespace http = boost::beast::http;

class Context {
private:
  const http::request<http::string_body> &request;
  http::response<http::string_body> &response;
  std::map<std::string, std::string> params;

public:
  // Constructor
  Context(const http::request<http::string_body> &req,
          http::response<http::string_body> &res)
      : request(req), response(res) {}

  // Getters for the request and response to provide read/write access
  const http::request<http::string_body> &getRequest();
  http::response<http::string_body> &getResponse();

  // Add more functionality as needed, such as setting response status, headers,
  // etc. For example, a helper function to easily set the response result and
  // body
  void setResponseResult(http::status status, const std::string &body);
  std::string getParam(const std::string &key) const;
  void setParam(const std::string &key, const std::string &value);
};
