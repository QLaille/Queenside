#ifndef QUEENSIDE_PROTOCOL_HPP
#define QUEENSIDE_PROTOCOL_HPP

#include <string>

#include "SwitchWithStrings.hpp"

namespace Queenside {

typedef
enum request_type_s {
	unknown = 0,
	joinRoom,
	quitRoom,
	roomInfo,
	declareReady,
	declareMove
} request_type_t;

typedef
struct request_s {
	request_type_t _type;
	std::string _name;
	std::string _comment;
} request_t;

class Protocol {
public:
	Protocol(int);
	~Protocol() = default;
	request_t getRequest(const std::string&);
	request_t inTextMode();
	request_t inBinaryMode();
private:
	int _mode;
};
};

#endif /* !QUEENSIDE_PROTOCOL_HPP */