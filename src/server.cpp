#include "../include/server.hpp"

void Server::session(tcp::socket socket) {
  try {
    beast::flat_buffer buffer;
    http::request<http::string_body> request;
    http::read(socket, buffer, request);
    http::response<http::string_body> response;

    // Delegate the routing to the Router instance
    if (!router->route(request, response)) {
      // If no route matches, respond with Not Found
      response.result(http::status::not_found);
      response.body() = "Resource not found";
    }
    response.prepare_payload();

    http::write(socket, response);
  } catch (std::exception const &e) {
    std::cerr << "Session error: " << e.what() << std::endl;
  }
}

void Server::run() {
  tcp::acceptor acceptor{
      io_context, {tcp::v4(), static_cast<boost::asio::ip::port_type>(port)}};
  for (;;) {
    tcp::socket socket{io_context};
    acceptor.accept(socket);
    std::thread(&Server::session, this, std::move(socket)).detach();
  }
}

short Server::getPort() { return port; }
