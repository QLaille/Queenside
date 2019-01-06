#include "GameSync.hpp"

namespace Queenside {
Gamesync *Gamesync::_singleton = NULL;

Gamesync *Gamesync::getInstance()
{
	if (_singleton == NULL)
		_singleton = new Gamesync;
	return (_singleton);
}

const std::optional<std::string> Gamesync::findGameMaster(const std::string &id)
{
	if (_gamemasters.find(id) != _gamemasters.end())
		return (id);
	return (std::nullopt);
}

void Gamesync::createGameMaster(const std::string &idA, const std::string &idB)
{
	GameMaster gm;
	std::string gameId = generateGameID();

	_gamemasters.insert({gameId, gm});
	return; //gameID
}

		// to be closed, a game must be over
		//which means all players are gone
		//for testing we only check if game is over
void Gamesync::removeGameMaster(const std::string &id)
{
	if (auto masterId = findGameMaster(id)) {
		if (_gamemasters[masterId.value()].isCheckmate())
			_gamemasters.erase(masterId.value());
	}
}

const std::string Gamesync::idToGameMaster(const std::string &id, const std::string &command)
{
	return ("");
}

const std::string Gamesync::uciokToGameMaster(const std::string &id, const std::string &command)
{
	return ("");
}

const std::string Gamesync::readyokToGameMaster(const std::string &id, const std::string &command)
{
	return ("");
}

const std::string Gamesync::bestmoveToGameMaster(const std::string &id, const std::string &command)
{
	//play
	return ("");
}

const std::string Gamesync::infoToGameMaster(const std::string &id, const std::string &command)
{
	//logs
	return ("");
}
}
