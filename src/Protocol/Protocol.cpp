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
	Coordinator cd = Coordinator::getInstance();

	if (cd.moveClientToRoom(clientId, cd.addRoom()))
		return(true);
	return(false);
}

/* Process Request */
bool Protocol::processJoin(const std::string &clientId, const request_t &req)
{
	Coordinator cd = Coordinator::getInstance();
	std::string roomId = req._comment;

	if (cd.moveClientToRoom(clientId, roomId))
		return (true);
	return (false);
}

void Protocol::processQuit(const std::string &Id, const request_t &req)
{
	Coordinator cd = Coordinator::getInstance();

	cd.removeClientFromRoom(Id);
	//write to client
}

void Protocol::processInfoRoom(const std::string &Id, const request_t &req)
{
	Coordinator cd = Coordinator::getInstance();
	std::string roomId;

	//roomID
	cd.findPlayerInRooms(Id);
	//write to client
	cd.dumpPlayerFromRoom(roomId);
}

void Protocol::processInfoAllRoom(const std::string &Id, const request_t &req)
{
	Coordinator cd = Coordinator::getInstance();

	//write to client
	cd.dumpRooms();
}

void Protocol::processReady(const std::string &Id, const request_t &req)
{
	Coordinator cd = Coordinator::getInstance();

	cd.changeClientState("");
}
};
