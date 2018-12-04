#ifndef QUEENSIDE_SERVICE_IDGENERATOR_HPP
#define QUEENSIDE_SERVICE_IDGENERATOR_HPP

#include <ctime>
#include <string>

namespace Queenside {
	class IDGenerator {
		public:
			std::string generateIDClient();
			std::string generateIDGame();
	};
};

#endif /* !QUEENSIDE_SERVICE_IDGENERATOR_HPP */