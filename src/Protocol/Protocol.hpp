#ifndef QUEENSIDE_PROTOCOL_HPP
#define QUEENSIDE_PROTOCOL_HPP

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <iostream>

#include "SwitchWithStrings.hpp"
#include "Coordinator.hpp"
#include "Strings.hpp"

/**
**
**	Protocol class,
**		Defined by its ability to parse a request sent by a client via a socket
**		Either in TEXT or UCI mode.
**	We translate the TEXT mode as a Client request, and the UCI mode as a Player one.
**	No binary mode yet implemented, we want to provide something usable by beginners.
**
*/

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

	/* Parse request */
	void processClientText(const request_t&);
	void processClientUCI();
	request_t getRequest(const std::string&);
	request_t inTextMode(const std::string &txt);

	/* Process Request */
	bool processNewRoom(const std::string &);
	const std::string processJoin(const std::string&, const request_t&);
	std::string processQuit(const std::string&, const request_t&);
	std::string processInfoRoom(const std::string&, const request_t&);
	std::string processInfoAllRoom(const std::string&, const request_t&);
	std::string processReady(const std::string&, const request_t&);

private:
};
};

#endif /* !QUEENSIDE_PROTOCOL_HPP */