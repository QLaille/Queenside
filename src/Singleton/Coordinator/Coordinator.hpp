#ifndef QUEENSIDE_SERVICE_COORDINATOR_HPP
#define QUEENSIDE_SERVICE_COORDINATOR_HPP

#include <unordered_map>
#include <algorithm>
#include <list>
#include <optional>
#include <ctime>

#include "Client.hpp"

namespace Queenside {

typedef std::unordered_map<std::string, bool> Players;
typedef std::unordered_map<std::string, bool>::iterator PlayersIt;

/**
**
**	Coordinator class
**
**	Class managing Clients not in Games, will pass to GameMaster when a room is ready
*/

class Coordinator {
public:
			static Coordinator& getInstance();

			/* Find */
			void findPlayer(const std::string &);
			const std::optional<std::string> findRoom(const std::string &);
			const std::optional<std::string> findPlayerInRooms(const std::string &);
			const std::optional<std::string> findPlayerNoRoom(const std::string &);

			/* Clients Management */
			void addClient(const std::string&);
			bool removeClient(const std::string&);
			bool moveClientToRoom(const std::string&, const std::string&);
			bool removeClientFromRoom(const std::string&);
			void changeClientState(const std::string&);

			/* Room Management */
			const std::string addRoom();
			bool removeRoom(const std::string&);

			/* Get Infos */
			std::list<std::string> dumpRooms();
			std::list<std::string> dumpPlayerFromRoom(const std::string&);
			const std::list<std::string> &dumpPlayerNotInRoom();

private:
			Coordinator() = default;

			std::list<std::string> _notInRoom;
			std::list<std::string>::iterator _notInRoomIt;
			std::unordered_map<std::string, Players> _rooms;
			std::unordered_map<std::string, Players>::iterator _roomsIt;
};
};

#endif /* !QUEENSIDE_SERVICE_COORDINATOR_HPP */