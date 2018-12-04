#include "IDGenerator.hpp"

namespace Queenside {
std::string IDGenerator::generateIDClient()
{
		std::string id;

		id = "C" + std::to_string(std::time(NULL));
		id += std::to_string(std::rand() % 10000);
		return (id);
}

std::string IDGenerator::generateIDGame()
{
		std::string id;

		id = "R" + std::to_string(std::time(NULL));
		id += std::to_string(std::rand() % 10000);
		return (id);
}
};
