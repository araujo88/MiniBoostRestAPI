#pragma once

#include <boost/beast.hpp>
#include <functional>
#include <map>
#include <memory>

namespace http = boost::beast::http;

class Router {
private:
    using HandlerFunc = std::function<void(const http::request<http::string_body>&, http::response<http::string_body>&)>;
    std::map<std::string, HandlerFunc> routes;

public:
    void addRoute(const std::string& path, HandlerFunc handler);
    bool route(const http::request<http::string_body>& req, http::response<http::string_body>& res);
};
