#include "Coordinator.hpp"

namespace Queenside {
Coordinator& Coordinator::getInstance()
{
	static Coordinator theInstance;

	return (theInstance);
}

void Coordinator::addClient(const std::string &Id)
{
	_notInRoom.push_front(Id);
}
};