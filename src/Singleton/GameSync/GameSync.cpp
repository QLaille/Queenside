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

const GameMaster &Gamesync::getGameMaster(const std::string &id)
{
	if (auto it = findGameMaster(id)) {
		return (_gamemasters[it.value()]);
	}
}

std::string Gamesync::createGameMaster(const std::string &idA, const std::string &idB)
{
	GameMaster gm({idA, idB});
	std::string gameId = generateGameID();

	_gamemasters.insert({gameId, gm});
	_gamemasters[gameId].startGame();
	return (gameId);
}

void Gamesync::removeGameMaster(const std::string &id)
{
	if (auto masterId = findGameMaster(id)) {
		if (_gamemasters[masterId.value()].isCheckmate())
			_gamemasters.erase(masterId.value());
	}
}

const std::string Gamesync::idToGameMaster(const std::string &gameId, const std::string &playerId, const std::string &command)
{
	return ("");
}

const std::string Gamesync::uciokToGameMaster(const std::string &gameId, const std::string &playerId, const std::string &command)
{
	return ("");
}

const std::string Gamesync::readyokToGameMaster(const std::string &gameId, const std::string &playerId, const std::string &command)
{
	return ("");
}

const std::string Gamesync::bestmoveToGameMaster(const std::string &gameId, const std::string &playerId, const std::string &command)
{
	auto bd = Broadcaster::getInstance();
	Move_t move;
	bool p;

	if (auto tmp = findGameMaster(gameId)) {
		auto master = getGameMaster(tmp.value());
		auto white = master.getWhite();
		auto black = master.getBlack();

		if (white.getId() == playerId) {
			if (!master.isWhiteTurn())
				return ("bestmove:KO");
			p = true;
			move.prevPos = {.x = (char)(command[0] - 65), .y = command[1] - 49};
			move.postPos = {.x = (char)(command[2] - 65), .y = command[3] - 49};
		} else if (black.getId() == playerId) {
			if (!master.isWhiteTurn())
				return ("bestmove:KO");
			p = false;
			move.prevPos = {.x = command[0] - 65, .y = command[1] - 49};
			move.postPos = {.x = command[2] - 65, .y = command[3] - 49};
		} else {
			return ("bestmove:KO");
		}
		if (master.validMove(master.getBoard(), move)) {
			master.playPiece(p, move);
			master.nextTurn();
			if (white.getId() == playerId)
				bd->writeToClient(black.getId(), master.translateToFEN());
			else
				bd->writeToClient(white.getId(), master.translateToFEN());
		}
	}
	return ("bestmove:OK");
}

const std::string Gamesync::infoToGameMaster(const std::string &gameId, const std::string &playerId, const std::string &command)
{
	//logs
	return ("");
}
}
