#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include "request_handler.hpp"

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class Server
{
private:
    short port;

public:
    Server(short port) : port(port) {}
    void session(tcp::socket socket, std::shared_ptr<IRequestHandler> handler);
    void run(std::shared_ptr<IRequestHandler> handler);
    short getPort();
};