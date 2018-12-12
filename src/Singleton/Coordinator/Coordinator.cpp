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
	PlayersIt playersIt;
	//check if client is already here but not in a room
	_notInRoomIt = std::find(_notInRoom.begin(), _notInRoom.end(), Id);

	if (_notInRoomIt != _notInRoom.end())
		return;

	for (auto it: _rooms) {
		playersIt = it.second.find(Id);
		if (playersIt != it.second.end())
			return;
	}
	return;
}

void Coordinator::findRoom(const std::string &roomId)
{
	_roomsIt = _rooms.find(roomId);

	if (_roomsIt != _rooms.end())
		return;
	return;
}

/* Clients Management */
void Coordinator::addClient(const std::string &Id)
{
	//check if client is already here but not in a room
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
	} else
		return (false);
}

bool Coordinator::moveClientToRoom(const std::string &Id, const std::string &RoomId)
{
	_roomsIt = _rooms.find(RoomId);

	if (_roomsIt != _rooms.end() && removeClient(Id)) {
		_roomsIt->second.insert({Id, false});
		return (true);
	} else
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

/* Room Management */
const std::string &Coordinator::addRoom()
{}

bool Coordinator::removeRoom(const std::string &roomId)
{
	_roomsIt = _rooms.find(roomId);

	if (_roomsIt != _rooms.end()) {
		_rooms.erase(roomId);
		return (true);
	} else
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

std::list<std::string> Coordinator::dumpPlayerNotInRoom()
{
	std::list<std::string> ret = {0};

	for (auto it: _notInRoom)
		ret.push_front(it);
	return (ret);
}
};