#include "Protocol.hpp"

namespace Queenside {
	Protocol::Protocol(int mode)
	: _mode(mode)
	{}

	request_t Protocol::getRequest(const std::string&)
	{}

	request_t Protocol::inTextMode()
	{}

	request_t Protocol::inBinaryMode()
	{}
};

//TODO: Write the methods