#ifndef QUEENSIDE_SERVICE_GAMEMASTER_HPP
#define QUEENSIDE_SERVICE_GAMEMASTER_HPP

#include <string>
#include <utility>

#include "Chess.hpp"

/**
**
**	Gamemaster class
**
**	It's the referee class which rules a game of chess.
**
*/

namespace Queenside {
class GameMaster {
public:
	GameMaster(std::pair<std::string, std::string>);
	GameMaster() = default;
	~GameMaster() = default;

	void game();
	bool playPiece(bool player, std::pair<move_t, move_t> move);
	bool isCheck();
	bool isCheckmate();
	bool isDraw();
	void translateToFEN();
	void enPassant();
	void Castle(playerSide, boardSide);
	//read socket white or black
	//read request
private:
	ChessPlayer _white;
	ChessPlayer _black;
	ChessBoard_t _board;
};

class ChessPlayer {
public:
	ChessPlayer() = default;
	ChessPlayer(const std::string&);
	~ChessPlayer() = default;

	void getId();
	void setCastle();
	void addMaterial();
	void removeMaterial();
private:
	const std::string _id;
	std::string _material;
	std::string _castle;
};

	enum playerSide {
		black,
		white
	};
	enum boardSide {
		kingside,
		queenside
	};
};

#endif /* !QUEENSIDE_SERVICE_GAMEMASTER_HPP */