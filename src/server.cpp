#include "../include/server.hpp"

void Server::session(tcp::socket socket) {
  try {
    beast::flat_buffer buffer;
    http::request<http::string_body> request;
    http::read(socket, buffer, request);
    http::response<http::string_body> response;

    auto handlerIt = routeMap.find(request.target());
    if (handlerIt != routeMap.end()) {
      // Call the function handler directly
      handlerIt->second(request, response);
    } else {
      response.result(http::status::not_found);
      response.body() = "Route not found";
    }

    http::write(socket, response);
  } catch (std::exception const &e) {
    std::cerr << "Session error: " << e.what() << std::endl;
  }
}

void Server::run() {
  net::io_context io_context{1};
  tcp::acceptor acceptor{
      io_context, {tcp::v4(), static_cast<boost::asio::ip::port_type>(port)}};
  for (;;) {
    tcp::socket socket{io_context};
    acceptor.accept(socket);
    std::thread(&Server::session, this, std::move(socket)).detach();
  }
}

void Server::addRoute(
    const std::string &route,
    std::function<void(const http::request<http::string_body> &,
                       http::response<http::string_body> &)>
        handler) {
  routeMap[route] = handler;
}

short Server::getPort() { return port; }
