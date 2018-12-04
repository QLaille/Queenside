#include "Client.hpp"

namespace Queenside {

const std::string &Client::getClientID()
{
	return (_clientId);
}

void Client::setClientID(std::string &id)
{
	_clientId = id;
}

};