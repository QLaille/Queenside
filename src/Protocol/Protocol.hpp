#ifndef QUEENSIDE_PROTOCOL_HPP
#define QUEENSIDE_PROTOCOL_HPP

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <iostream>

#include "SwitchWithStrings.hpp"

namespace Queenside {

typedef
enum request_type_s {
	unknown = 0,
	text,
	uci,
} request_type_t;

typedef
struct request_s {
	request_type_t _type;
	std::string _name;
	std::string _comment;
} request_t;

class Protocol {
public:
	Protocol() = default;
	~Protocol() = default;
	request_t getRequest(const std::string&);
	request_t inTextMode(const std::string &txt);
private:
};
};

#endif /* !QUEENSIDE_PROTOCOL_HPP */