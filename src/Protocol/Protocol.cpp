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
	//TODO: specify the request type in the switch case
};
