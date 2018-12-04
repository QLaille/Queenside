#ifndef QUEENSIDE_SERVICE_GAMEMASTER_HPP
#define QUEENSIDE_SERVICE_GAMEMASTER_HPP

#include <string>
#include <utility>

namespace Queenside {
class GameMaster {
public:
	GameMaster(std::pair<std::string, std::string>);
	GameMaster() = default;
	~GameMaster() = default;

	void playPiece();
	bool isCheckmate();
	void translateToFEN();
	void enPassant();
	void Castle(playerSide, boardSide);
	//read socket white or black
	//read request
private:
	//socket white
	//socket black
	ChessPlayer _white;
	ChessPlayer _black;

	bool _turn;
	std::string _pawnMove;	//used for En passant with the FEN
	int _turns;
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
	const std::string &_id;
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