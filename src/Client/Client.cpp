#include "Client.hpp"

namespace Queenside {

Client::Client(boost::asio::io_service& io_service)
	:_socket(std::make_shared<tcp::socket>(io_service))
{}

std::shared_ptr<tcp::socket>& Client::socket()
{
	return (_socket);
}


Client::pointer Client::create(boost::asio::io_service& io)
{
	return pointer(new Client(io));
}

const std::string &Client::getClientID()
{
	return (_clientId);
}

const std::shared_ptr<tcp::socket> &Client::getClientSocket()
{
	return (_socket);
}

void Client::setClientID(std::string &id)
{
	_clientId = id;
}

};