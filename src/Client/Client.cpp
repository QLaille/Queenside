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

void Client::setClientGameroom(std::string &room)
{
	if (room == strings.noGameRoom)
		_inGameRoom = false;
	else
		_inGameRoom = true;
	_gameRoom = room;
}

const std::string &Client::getClientGameroom()
{
	return (_gameRoom);
}

};