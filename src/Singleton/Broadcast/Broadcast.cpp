#include "Broadcast.hpp"

namespace Queenside {
	Broadcast& Broadcast::getInstance()
	{
		static Broadcast instance;

		return (instance);
	}

	void Broadcast::addClient(Client &client)
	{
		_iterator = _clients.find(client.getClientID());
		if (_iterator != _clients.end())
			_clients.insert(std::pair<std::string, Client>(client.getClientID(), client));
	}

	void Broadcast::removeClient(const std::string &clientId)
	{
		_iterator = _clients.find(clientId);
		if (_iterator != _clients.end())
			_clients.erase(clientId);
	}

	std::optional<Client> Broadcast::getClient(const std::string &clientId)
	{
		std::optional<Client> ret;

		_iterator = _clients.find(clientId);
		if (_iterator != _clients.end())
			ret = _iterator->second;
		return (ret);
	}

}