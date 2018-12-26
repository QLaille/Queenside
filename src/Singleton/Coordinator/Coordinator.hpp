#ifndef QUEENSIDE_SERVICE_COORDINATOR_HPP
#define QUEENSIDE_SERVICE_COORDINATOR_HPP

#include <unordered_map>
#include <algorithm>
#include <list>
#include <optional>
#include <ctime>

#include <iostream>

#include "Client.hpp"
#include "IDGenerator.hpp"
#include "Strings.hpp"

#define NO_ROOM "NoRoom"

namespace Queenside {

typedef std::array<std::pair<std::string, bool>, 2> Players;
typedef std::array<std::pair<std::string, bool>, 2>::iterator PlayersIt;

/**
**
**	Coordinator class
**
**	Class managing Clients not in Games, will pass to GameMaster when a room is ready
*/

class Coordinator {
public:
			static Coordinator *getInstance();

			/* Find */
			const std::optional<std::string> findPlayer(const std::string &);
			const std::optional<std::string> findRoom(const std::string &);
			const std::optional<std::string> findPlayerInRooms(const std::string &);
			const std::optional<std::string> findPlayerNoRoom(const std::string &);
			const std::optional<std::string> findRoomOfClient(const std::string&);

			/* Clients Management */
			void addClient(const std::string&);
			bool removeClient(const std::string&);
			const std::optional<std::string> moveClientToRoom(const std::string&, const std::string&);
			bool removeClientFromRoom(const std::string&);
			bool changeClientState(const std::string&, bool);

			/* Room Management */
			const std::string addRoom();
			bool removeRoom(const std::string&);

			/* Get Infos */
			bool isRoomReady(const std::string&);
			std::list<std::string> dumpRooms();
			std::list<std::string> dumpPlayerFromRoom(const std::string&);
			const std::list<std::string> &dumpPlayerNotInRoom();

private:
			Coordinator() = default;
			static Coordinator *_singleton;

			std::list<std::string> _notInRoom;
			std::list<std::string>::iterator _notInRoomIt;
			std::unordered_map<std::string, Players> _rooms;
			std::unordered_map<std::string, Players>::iterator _roomsIt;
};
};

#endif /* !QUEENSIDE_SERVICE_COORDINATOR_HPP */