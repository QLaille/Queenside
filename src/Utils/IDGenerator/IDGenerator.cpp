#include "IDGenerator.hpp"

namespace Queenside {
std::string generateClientID()
{
		std::string id;

		id = "C" + std::to_string(std::time(NULL));
		id += std::to_string(std::rand() % 10000);
		return (id);
}

std::string generateRoomID()
{
		std::string id;

		id = "R" + std::to_string(std::time(NULL));
		id += std::to_string(std::rand() % 10000);
		return (id);
}

std::string generateGameID()
{
		std::string id;

		id = "G" + std::to_string(std::time(NULL));
		id += std::to_string(std::rand() % 10000);
		return (id);
}
};
