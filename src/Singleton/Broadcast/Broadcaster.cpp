#include "Broadcaster.hpp"

namespace Queenside {
	Broadcaster *Broadcaster::_singleton = NULL;

	Broadcaster *Broadcaster::getInstance()
	{
		if (_singleton == NULL)
			_singleton = new Broadcaster;
		return (_singleton);
	}

	void Broadcaster::addClient(Client &client)
	{
		_iterator = _clients.find(client.getClientID());
		if (_iterator == _clients.end())
			_clients.insert(std::pair<std::string, Client>(client.getClientID(), client));
	}

	void Broadcaster::removeClient(const std::string &clientId)
	{
		_iterator = _clients.find(clientId);
		if (_iterator != _clients.end())
			_clients.erase(clientId);
	}

	/* Get Infos*/
	std::optional<Client> Broadcaster::getClient(const std::string &clientId)
	{
		std::optional<Client> ret = std::nullopt;

		_iterator = _clients.find(clientId);
		if (_iterator != _clients.end())
			ret = _iterator->second;
		return (ret);
	}

/* Communication */
void Broadcaster::Broadcast(std::string &msg)
{
	for (auto it: _clients) {
		writeToClient(it.first, msg);
	}
}

void Broadcaster::writeToClient(const std::string &id, const std::string &msg)
{
	_iterator = _clients.find(id);
	if (_iterator != _clients.end())
		boost::asio::write(*_clients[id].getSocket(), boost::asio::buffer(msg + "\n"));
}
}
