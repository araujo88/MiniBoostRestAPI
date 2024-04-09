#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;	// from <boost/beast/http.hpp>
namespace net = boost::asio;	// from <boost/asio.hpp>
using tcp = net::ip::tcp;		// from <boost/asio/ip/tcp.hpp>

class Person
{
public:
	std::string name;
	int age;

	// Constructor from a JSON object
	Person(const boost::json::object &obj)
	{
		name = obj.at("name").as_string().c_str();
		age = obj.at("age").as_int64();
	}
	boost::json::object to_json() const
	{
		boost::json::object obj;
		obj["name"] = name;
		obj["age"] = age;
		return obj;
	}
};

std::vector<Person> persons;

void handle_request(http::request<http::string_body> &request, http::response<http::string_body> &response)
{
	std::cout << request.method_string() << " "
			  << request.target() << " " << request.body() << std::endl;

	// Here you would dispatch based on the URI and HTTP method
	if (request.method_string() == "GET" && request.target() == "/")
	{
		response.result(http::status::ok);
		response.body() = "Hello, world!";
	}
	else if (request.method_string() == "GET" && request.target() == "/person")
	{
		try
		{
			// Create a JSON array
			boost::json::array jsonPersons;

			// Iterate through the vector of Person objects
			for (const auto &person : persons)
			{
				// Convert each Person to a JSON object and add to the array
				jsonPersons.push_back(person.to_json());
			}

			// Serialize the JSON array to a string
			std::string jsonString = boost::json::serialize(jsonPersons);

			// Set the response
			response.result(http::status::ok);
			response.body() = jsonString;
			response.set(http::field::content_type, "application/json");
		}
		catch (const std::exception &e)
		{
			// Handle any errors
			response.result(http::status::internal_server_error);
			response.body() = "{\"error\": \"Failed to serialize persons.\"}";
			response.set(http::field::content_type, "application/json");
		}
	}
	else if (request.method_string() == "POST" && request.target() == "/person")
	{
		try
		{
			// Parse the JSON body from the request
			auto json = boost::json::parse(request.body());

			// Instantiate the Person class with the parsed JSON
			Person person(json.as_object());
			persons.push_back(person);

			// Do something with the person object
			// For demonstration, let's just set the response body to the received name
			response.result(http::status::ok);
			response.body() = "Received: " + person.name;
		}
		catch (const std::exception &e)
		{
			// Handle any parsing errors
			response.result(http::status::bad_request);
			response.body() = "Invalid JSON payload";
		}
	}
	else
	{
		response.result(http::status::internal_server_error);
		response.body() = "Internal server error";
	}
	response.prepare_payload();
}

void session(tcp::socket socket)
{
	try
	{
		beast::flat_buffer buffer;

		// Set up an HTTP request parser
		http::request<http::string_body> request;
		http::read(socket, buffer, request);

		// Handle the request
		http::response<http::string_body> response;
		handle_request(request, response);

		// Send the response
		http::write(socket, response);
	}
	catch (std::exception const &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void run_server(short port)
{
	net::io_context io_context{1};

	tcp::acceptor acceptor{io_context, {tcp::v4(), static_cast<boost::asio::ip::port_type>(port)}};
	for (;;)
	{
		tcp::socket socket{io_context};
		acceptor.accept(socket);

		// Handle each session in a separate thread
		std::thread{session, std::move(socket)}.detach();
	}
}

int main()
{
	try
	{
		short port = 6969;
		std::cout << "Server starting on port " << port << std::endl;
		run_server(port);
	}
	catch (std::exception const &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}