#include "Broadcaster.hpp"

namespace Queenside {
	Broadcaster& Broadcaster::getInstance()
	{
		static Broadcaster instance;

		return (instance);
	}

	void Broadcaster::addClient(Client &client)
	{
		_iterator = _clients.find(client.getClientID());
		if (_iterator != _clients.end())
			_clients.insert(std::pair<std::string, Client>(client.getClientID(), client));
	}

	void Broadcaster::removeClient(const std::string &clientId)
	{
		_iterator = _clients.find(clientId);
		if (_iterator != _clients.end())
			_clients.erase(clientId);
	}

	std::optional<Client> Broadcaster::getClient(const std::string &clientId)
	{
		std::optional<Client> ret;

		_iterator = _clients.find(clientId);
		if (_iterator != _clients.end())
			ret = _iterator->second;
		return (ret);
	}

/* Communication */
void Broadcaster::Broadcast(std::string &msg)
{}

void Broadcaster::WriteToClient(const std::string &id, std::string &msg)
{}
}

//TODO: finish writing the methods to write to clients