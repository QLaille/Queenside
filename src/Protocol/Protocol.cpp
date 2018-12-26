#include "Protocol.hpp"

namespace Queenside {
request_t Protocol::getRequest(const std::string &request)
{
	return (inTextMode(request));
}

request_t Protocol::inTextMode(const std::string &txt)
{
	std::vector<std::string> elems;
	request_t req;

	boost::split(elems, txt,boost::is_any_of(":"));
	req._type = unknown;
	if (elems.size() == 3) {
		switch(hash(elems[0].c_str())) {
			case (hash("TEXT")):
				req._type = text;
				break;
			case (hash("UCI")):
				req._type = uci;
				break;
			default:
				req._type = unknown;
				break;
		}
		req._name = elems[1];
		req._comment = elems[2];
	}
	return (req);
}

bool Protocol::processNewRoom(const std::string &clientId)
{
	Coordinator *cd = Coordinator::getInstance();

	if (cd->moveClientToRoom(clientId, "NEWROOM"))
		return(true);
	return(false);
}

/* Process Request */
const std::string Protocol::processJoin(const std::string &clientId, const request_t &req)
{
	Coordinator *cd = Coordinator::getInstance();
	std::string roomId = req._comment;

	if (auto id = cd->moveClientToRoom(clientId, roomId))
		return (id.value());
	return (strings.impossible);
}

std::string Protocol::processQuit(const std::string &Id, const request_t &req)
{
	Coordinator *cd = Coordinator::getInstance();

	if (auto ret = cd->removeClientFromRoom(Id))
		return (strings.removed);
	return (strings.notInRoom);
}

std::string Protocol::processInfoRoom(const std::string &clientId, const request_t &req)
{
	Coordinator *cd = Coordinator::getInstance();
	std::list<std::string> list;
	std::string msg;

	if (auto res = cd->findRoomOfClient(clientId))
		list = cd->dumpPlayerFromRoom(res.value());
		for (auto x: list)
			msg = msg + (msg.size() == 0 ? "": "\nTEXT:ROOMINFO:") + x;
		return (msg);
	return ("NONE");
}

std::string Protocol::processInfoAllRoom(const std::string &Id, const request_t &req)
{
	Coordinator *cd = Coordinator::getInstance();
	std::list<std::string> list = cd->dumpRooms();
	std::string msg;

	for (auto x: list)
		msg = msg + (msg.size() == 0 ? "": "\nTEXT:ALLROOM:") + x;
	return (msg);
}

std::string Protocol::processReady(const std::string &Id, const request_t &req)
{
	Coordinator *cd = Coordinator::getInstance();

	if (cd->changeClientState(Id, req._comment == "READY" ? true : false)) {
		if (auto roomId = cd->findRoomOfClient(Id))
			if (cd->isRoomReady(roomId.value()))
				return (strings.roomReady);
		return (req._comment);
	}
	return (strings.notInRoom);
}
};
