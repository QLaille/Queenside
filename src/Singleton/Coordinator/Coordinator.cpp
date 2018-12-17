#include "Coordinator.hpp"

namespace Queenside {
Coordinator& Coordinator::getInstance()
{
	static Coordinator theInstance;

	return (theInstance);
}


/* Find */
void Coordinator::findPlayer(const std::string &Id)
{
	findPlayerNoRoom(Id);
	findPlayerInRooms(Id);
}

const std::optional<std::string> Coordinator::findRoom(const std::string &roomId)
{
	_roomsIt = _rooms.find(roomId);

	if (_roomsIt != _rooms.end())
		return (_roomsIt->first);
	return (std::nullopt);
}

const std::optional<std::string> Coordinator::findPlayerInRooms(const std::string &Id)
{
	PlayersIt playersIt;

	for (auto it: _rooms) {
		playersIt = it.second.find(Id);
		if (playersIt != it.second.end())
			return (playersIt->first);
	}
	return (std::nullopt);
}

const std::optional<std::string> Coordinator::findPlayerNoRoom(const std::string &Id)
{
	_notInRoomIt = std::find(_notInRoom.begin(), _notInRoom.end(), Id);

	if (_notInRoomIt != _notInRoom.end())
		return (*_notInRoomIt);
	return (std::nullopt);
}

/* Clients Management */
void Coordinator::addClient(const std::string &Id)
{
	//check if client is already here but not in a room
	if (findPlayerNoRoom(Id) == std::nullopt)
	_notInRoomIt = std::find(_notInRoom.begin(), _notInRoom.end(), Id);

	if (_notInRoomIt != _notInRoom.end())
		_notInRoom.push_front(Id);
}


bool Coordinator::removeClient(const std::string &Id)
{
	_notInRoomIt = std::find(_notInRoom.begin(), _notInRoom.end(), Id);

	if (_notInRoomIt != _notInRoom.end()) {
		_notInRoom.remove(Id);
		return (true);
	}
	return (false);
}

bool Coordinator::moveClientToRoom(const std::string &clientId, const std::string &RoomId)
{
	_roomsIt = _rooms.find(RoomId);

	if (_roomsIt != _rooms.end() && removeClient(clientId)) {
		_roomsIt->second.insert({clientId, false});
		return (true);
	}
	return (false);
}

bool Coordinator::removeClientFromRoom(const std::string &Id)
{
	PlayersIt playersIt;

	for (auto it: _rooms) {
		playersIt = it.second.find(Id);
		if (playersIt != it.second.end()) {
			it.second.erase(Id);
			return (true);
		}
	}
	return (false);
}

void Coordinator::changeClientState(const std::string &Id)
{
	PlayersIt playersIt;

	for (auto it: _rooms) {
		playersIt = it.second.find(Id);
		if (playersIt != it.second.end()) {
			playersIt->second = true;
			return;
		}
	}
	return;

}

/* Room Management */
const std::string Coordinator::addRoom()
{
	std::string id;

	id = "C" + std::to_string(std::time(NULL)) + std::to_string(std::rand() % 10000);
	_rooms[id];
	return (id);
}

bool Coordinator::removeRoom(const std::string &roomId)
{
	_roomsIt = _rooms.find(roomId);

	if (_roomsIt != _rooms.end()) {
		_rooms.erase(roomId);
		return (true);
	}
	return (false);
}

/* Get Infos */
std::list<std::string> Coordinator::dumpRooms()
{
	std::list<std::string> ret = {0};

	for (auto it: _rooms)
		ret.push_front(it.first);
	return (ret);
}

std::list<std::string> Coordinator::dumpPlayerFromRoom(const std::string &roomId)
{
	std::list<std::string> ret = {0};
	auto it = _rooms.find(roomId);

	if (it != _rooms.end()) {
		for (auto playerIt: it->second)
			ret.push_front(playerIt.first);
	}
	return (ret);
}

const std::list<std::string> &Coordinator::dumpPlayerNotInRoom()
{
	return (_notInRoom);
}
};