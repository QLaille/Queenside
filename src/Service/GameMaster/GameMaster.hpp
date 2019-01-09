#ifndef QUEENSIDE_SERVICE_GAMEMASTER_HPP
#define QUEENSIDE_SERVICE_GAMEMASTER_HPP

#include <string>
#include <utility>

#include "Broadcaster.hpp"

#include "Chess.hpp"
#include "Pieces.hpp"

/**
**
**	Gamemaster class
**
**	It's the referee class which rules a game of chess.
**
*/

namespace Queenside {

	typedef
	enum playerSide {
		black,
		white
	} playerSide;

	typedef
	enum boardSide {
		kingside,
		queenside
	} boardSide;

class ChessPlayer {
public:
	ChessPlayer() = default;
	ChessPlayer(const std::string &a):_id(a) {};
	~ChessPlayer() = default;

	const std::string &getId() {return _id;};
	void setCastle() {};
	void addMaterial() {};
	void removeMaterial() {};
private:
	const std::string _id;
	std::string _material;
	std::string _castle;
};


class GameMaster {
public:
	GameMaster(std::pair<std::string, std::string>);
	GameMaster() = default;
	~GameMaster() = default;

	static bool validMove(ChessBoard_t const &chess, Move_t const &move);

	void startGame();
	void game();
	bool playPiece(bool, Move_t);
	bool isCheck();
	bool isCheckmate();
	bool isDraw();
	const std::string translateToFEN();
	void enPassant();
	void Castle(playerSide, boardSide);
	const ChessBoard_t &getBoard();
	const ChessPlayer &getWhite();
	const ChessPlayer &getBlack();
	const bool &isWhiteTurn();
	void nextTurn();
private:
	bool _whiteTurn;
	ChessPlayer _white;
	ChessPlayer _black;
	ChessBoard_t _board;
};
};

#endif /* !QUEENSIDE_SERVICE_GAMEMASTER_HPP */