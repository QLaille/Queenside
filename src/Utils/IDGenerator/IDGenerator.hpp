#ifndef QUEENSIDE_SERVICE_IDGENERATOR_HPP
#define QUEENSIDE_SERVICE_IDGENERATOR_HPP

#include <ctime>
#include <string>

/**
**
**	IDGenerator class
**	Will generate an ID based on:
**	Its type: G for GameRoom and C for Client
**	A Timestamp
**	A call of rand modulo 10000
**
*/

namespace Queenside {
	class IDGenerator {
		public:
			std::string generateIDClient();
			std::string generateIDGame();
	};
};

#endif /* !QUEENSIDE_SERVICE_IDGENERATOR_HPP */