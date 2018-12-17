#include "Client.hpp"

namespace Queenside {

Client::Client(std::shared_ptr<tcp::socket> socket)
: _socket(socket)
{}

const std::string &Client::getClientID()
{
	return (_clientId);
}

void Client::setClientID(std::string &id)
{
	_clientId = id;
}

const std::shared_ptr<tcp::socket> Client::getSocket()
{
	return(_socket);
}
};