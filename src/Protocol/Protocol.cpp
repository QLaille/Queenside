#include "Protocol.hpp"

namespace Queenside {
	Protocol::Protocol(int mode)
	: _mode(mode)
	{}

	request_t Protocol::getRequest(const std::string &request)
	{
		return (inTextMode(request));
	}

	request_t Protocol::inTextMode(const std::string &txt)
	{
		request_t req;
		std::vector<std::string> elems;

		boost::split(elems, txt,boost::is_any_of(":"));
		req._type = unknown;
		req._name = elems[1];
		req._comment = elems[2];
		if (elems.size() != 3)
			return (req);
		switch(hash(elems[0].c_str())) {
			case (hash("a")): req._type = joinRoom;
			case (hash("q")): req._type = quitRoom;
			case (hash("s")): req._type = roomInfo;
			case (hash("d")): req._type = declareReady;
			default: req._type = unknown;
		};
		return (req);
	}
	//TODO: specify the request type in the switch case
};
