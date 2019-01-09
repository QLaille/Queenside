#ifndef QUEENSIDE_SERVICE_BROADCASTER_HPP
#define QUEENSIDE_SERVICE_BROADCASTER_HPP

#include "Client.hpp"

#include <string>
#include <optional>
#include <unordered_map>
#include <iostream>

typedef std::string clientID;

/**
**
**	Broadcaster class
**
**	Used to communicate to said client, gameRoom or to all clients.
*/

namespace Queenside {
	class Broadcaster {
		public:
			static Broadcaster *getInstance();

			/* Clients Management */
			void addClient(Client&);
			void removeClient(const std::string &clientId);
			void setClient(Client&);

			/* Communication */
			void Broadcast(std::string&);
			void writeToClient(const std::string&, const std::string&);

			/* Get Infos*/
			std::optional<Client> getClient(const std::string &clientID);
		private:
			Broadcaster() = default;
			static Broadcaster *_singleton;

			std::unordered_map<clientID, Client> _clients;
			std::unordered_map<clientID, Client>::iterator _iterator;
	};
};
//TODO: Add methods to communicate with clients, room, broadcast

#endif /* !QUEENSIDE_SERVICE_BROADCASTER_HPP */