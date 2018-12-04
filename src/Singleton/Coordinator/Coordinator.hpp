#ifndef QUEENSIDE_SERVICE_COORDINATOR_HPP
#define QUEENSIDE_SERVICE_COORDINATOR_HPP

#include "Client.hpp"

#include <unordered_map>
#include <list>

namespace Queenside {
typedef std::unordered_map<std::string, bool> Players;

class Coordinator {
public:
			static Coordinator& getInstance();
			void addClient(const std::string&);
private:
			Coordinator() = default;


			std::list<std::string> _notInRoom;
			std::list<std::string>::iterator _notInRoomIt;
			std::unordered_map<std::string, Players> _rooms;
			std::unordered_map<std::string, Players>::iterator _roomsIt;
};
};

//TODO: Expand the method

#endif /* !QUEENSIDE_SERVICE_COORDINATOR_HPP */