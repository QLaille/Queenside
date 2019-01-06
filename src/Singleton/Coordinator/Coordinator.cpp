#include "Coordinator.hpp"

namespace Queenside {

Coordinator *Coordinator::_singleton = NULL;

Coordinator *Coordinator::getInstance()
{
	if (_singleton == NULL)
		_singleton = new Coordinator;
	return (_singleton);
}

/* Find */
const std::optional<std::string> Coordinator::findPlayer(const std::string &Id)
{

	if (auto noRoom = findPlayerNoRoom(Id))
		return (NO_ROOM);
	if (auto roomId = findPlayerInRooms(Id))
		return (roomId.value());
	return (std::nullopt);
}

const std::optional<std::string> Coordinator::findRoom(const std::string &roomId)
{
	_roomsIt = _rooms.find(roomId);

	if (_roomsIt != _rooms.end())
		return (_roomsIt->first);
	return (std::nullopt);
}

/* Find player and return its ID if found */
const std::optional<std::string> Coordinator::findPlayerInRooms(const std::string &clientId)
{
	PlayersIt playersIt;

	for (auto it: _rooms) {
		if ((it.second[0].first == clientId) || (it.second[1].first == clientId))
			return (clientId);
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

const std::optional<std::string> Coordinator::findRoomOfClient(const std::string &clientId)
{
	for (auto roomIt: _rooms) {
		if ((roomIt.second[0].first == clientId)
		|| (roomIt.second[1].first == clientId))
			return (roomIt.first);
	}
	return (std::nullopt);
}

/* Clients Management */
void Coordinator::addClient(const std::string &Id)
{
	if (findPlayer(Id) == std::nullopt)
		_notInRoom.push_front(Id);
}

/* Can remove client only if not in Room, if as a client you want to remove yourself, get out of the room first */
bool Coordinator::removeClient(const std::string &Id)
{
	if (findPlayerNoRoom(Id) == NO_ROOM) {
		_notInRoom.remove(Id);
		return (true);
	}
	return (false);
}

const std::optional<std::string> Coordinator::moveClientToRoom(const std::string &clientId, const std::string &RoomId)
{
	Players players;

	if (RoomId == strings.newRoom) {
		auto newRoom = addRoom();
		players[0].first = clientId;
		players[0].second = false;
		players[1].first = "EMPTY";
		players[1].second = false;
		_rooms[newRoom] = players;
		return (newRoom);
	}
	_roomsIt = _rooms.find(RoomId);
	if (_roomsIt != _rooms.end()) {
		if (auto prevRoom = findRoomOfClient(clientId)) {
			if (prevRoom.value() == RoomId)
				return (RoomId);
			removeClientFromRoom(clientId);
		}
		if (_roomsIt->second[0].first == "EMPTY")
			_roomsIt->second[0] = {clientId, false};
		else if (_roomsIt->second[1].first == "EMPTY")
			_roomsIt->second[1] = {clientId, false};
		else
			return (std::nullopt);
		return (RoomId);
	}
	return (std::nullopt);
}

bool Coordinator::removeClientFromRoom(const std::string &clientId)
{
	if (auto roomId = findRoomOfClient(clientId)) {
		if (_rooms[roomId.value()][0].first == clientId) {
			_rooms[roomId.value()][0].first = "EMPTY";
			if (_rooms[roomId.value()][1].first == "EMPTY")
				_rooms.erase(roomId.value());
			return (true);
		} else if (_rooms[*roomId][1].first == clientId) {
			_rooms[*roomId][1].first = "EMPTY";
			if (_rooms[roomId.value()][0].first == "EMPTY")
				_rooms.erase(roomId.value());
			return (true);
		}
	}
	return (false);
}

/* Returns the ready state if we could attribute it to the player */
bool Coordinator::changeClientState(const std::string &clientId, bool state)
{
	if (auto roomId = findRoomOfClient(clientId)) {
		if (_rooms[roomId.value()][0].first == clientId)
			_rooms[roomId.value()][0].second = state;
		else if (_rooms[roomId.value()][1].first == clientId)
			_rooms[roomId.value()][1].second = state;
		return (state);
	}
	return (!state);
}

/* Room Management */
const std::string Coordinator::addRoom()
{
	std::string id = generateGameID();

	while(_rooms.find(id) != _rooms.end())
		id = generateGameID();
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
bool Coordinator::isRoomReady(const std::string &RoomId)
{
	auto room = _rooms.find(RoomId);
	if (room != _rooms.end()) {
		if ((room->second[0].first != "EMPTY" && room->second[1].first != "EMPTY")
		&& (room->second[0].second && room->second[1].second))
			return (true);
	}
	return (false);
}


std::list<std::string> Coordinator::dumpRooms()
{
	std::list<std::string> ret;

	for (auto it: _rooms)
		ret.push_front(it.first);
	return (ret);
}

std::list<std::string> Coordinator::dumpPlayerFromRoom(const std::string &roomId)
{
	std::list<std::string> ret;
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