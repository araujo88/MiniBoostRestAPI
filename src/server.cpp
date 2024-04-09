#include "../include/server.hpp"

void Server::session(tcp::socket socket,
                     std::shared_ptr<IRequestHandler> handler) {
  try {
    beast::flat_buffer buffer;
    http::request<http::string_body> request;
    http::read(socket, buffer, request);
    http::response<http::string_body> response;
    handler->handleRequest(request, response);
    http::write(socket, response);
  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void Server::run(std::shared_ptr<IRequestHandler> handler) {
  net::io_context io_context{1};
  tcp::acceptor acceptor{
      io_context, {tcp::v4(), static_cast<boost::asio::ip::port_type>(port)}};
  for (;;) {
    tcp::socket socket{io_context};
    acceptor.accept(socket);
    std::thread(&Server::session, this, std::move(socket), handler).detach();
  }
}

short Server::getPort() { return port; }
