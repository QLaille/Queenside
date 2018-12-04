#include "Broadcast.hpp"

namespace Queenside {
	Broadcast& Broadcast::getInstance()
	{
		static Broadcast instance;

		return (instance);
	}

	void Broadcast::addClient(Client::pointer&)
	{}

	void Broadcast::removeClient(const std::string &clientId)
	{}
}
