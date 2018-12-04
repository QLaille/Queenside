#ifndef QUEENSIDE_SERVICE_BROADCAST_HPP
#define QUEENSIDE_SERVICE_BROADCAST_HPP

#include "Client.hpp"

#include <string>
#include <optional>
#include <unordered_map>

typedef std::string clientID;

namespace Queenside {
	class Broadcast {
		public:
			static Broadcast& getInstance();
			void addClient(Client&);
			void removeClient(const std::string &clientId);
			std::optional<Client> getClient(const std::string &clientID);
		private:
			Broadcast() = default;

			std::unordered_map<clientID, Client> _clients;
			std::unordered_map<clientID, Client>::iterator _iterator;
	};
};
//TODO: Add methods to communicate with clients, room, broadcast

#endif /* !QUEENSIDE_SERVICE_BROADCAST_HPP */