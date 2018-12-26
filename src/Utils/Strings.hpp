#ifndef QUEENSIDE_STRINGS_HPP
# define QUEENSIDE_STRINGS_HPP

#include <string>

namespace Queenside {
static struct String_s {
	const std::string newRoom = "NEWROOM";
	const std::string joinRoom = "JOINROOM";
	const std::string quitRoom = "QUITROOM";
	const std::string roomInfo = "ROOMINFO";
	const std::string allRoom = "ALLROOM";
	const std::string state = "STATE";
	const std::string unavailable = "UNAVAILABLE";
	const std::string notInRoom = "NOT_IN_ROOM";
	const std::string removed = "REMOVED";
	const std::string impossible = "IMPOSSIBLE";
	const std::string cannotJoin = "CANNOT_JOIN";
	const std::string none = "NONE";
	const std::string readyRoom = "ROOMREADY";
	const std::string welcome = "WELCOME";
	const std::string unknown_request = "UNKNOWN_REQUEST";
	const std::string unknown_uci_command = "UNKNOWN UCI COMMAND";
	const std::string text = "TEXT";
	const std::string roomReady = "ROOMREADY";
} strings;
};

#endif /* !QUEENSIDE_STRINGS_HPP */