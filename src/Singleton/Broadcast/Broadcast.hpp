#ifndef QUEENSIDE_SERVICE_BROADCAST_HPP
#define QUEENSIDE_SERVICE_BROADCAST_HPP

#include "Client.hpp"

#include <string>
#include <unordered_map>

typedef std::string clientID;

namespace Queenside {
	class Broadcast {
		public:
			static Broadcast& getInstance();
			void addClient(Client::pointer&);
			void removeClient(const std::string &clientId);
		private:
			Broadcast() = default;

			std::unordered_map<clientID, Client::pointer> _clients;
			std::unordered_map<clientID, Client::pointer>::iterator _iterator;
	};
};

#endif /* !QUEENSIDE_SERVICE_BROADCAST_HPP */