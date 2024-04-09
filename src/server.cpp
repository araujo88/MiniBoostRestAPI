#include "../include/server.hpp"

void Server::session(tcp::socket socket) {
  try {
    beast::flat_buffer buffer;
    http::request<http::string_body> req;
    http::read(socket, buffer, req);
    http::response<http::string_body> res;
    auto ctx = Context(req, res);

    // Delegate the routing to the Router instance
    if (!router->route(ctx)) {
      // If no route matches, respond with Not Found
      res.result(http::status::not_found);
      res.body() = "Resource not found";
    }
    if (res.body().length() != 0)
      res.prepare_payload();

    http::write(socket, res);
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
