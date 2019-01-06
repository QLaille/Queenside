#include "GameMaster.hpp"

#include "FENConvertor.hpp"

namespace Queenside {

GameMaster::GameMaster(std::pair<std::string, std::string> players)
: _white(players.first), _black(players.second)
{}

bool	GameMaster::validMove(ChessBoard_t const &chess, Move_t const &move)
{
	switch (chess._board[move.prevPos.y][move.prevPos.x]) {
		case 'p':
		case 'P':
			return Pawn::validMove(chess, move);
			break;
		case 'r':
		case 'R':
			return Rook::validMove(chess, move);
			break;
		case 'n':
		case 'N':
			return Knight::validMove(chess, move);
			break;
		case 'b':
		case 'B':
			return Rook::validMove(chess, move);
			break;
		case 'q':
		case 'Q':
			return Queen::validMove(chess, move);
			break;
		case 'k':
		case 'K':
			return King::validMove(chess, move);
			break;
		default:
			return false;
	}
}

void GameMaster::game()
{
	while(/*no game ending (1-0 or 1/2-1/2)*/1) {
		//wait for correct move (no time involved yet)
		//do the move
		//check mates
		//modify FEN string
	}
}

bool GameMaster::playPiece(bool player, std::pair<move_t, move_t> move)
{
	ChessPlayer gm = (bool)player ? _white : _black;

	//is there a piece from player on this tile
	//is there a piece on the way to the tile
	//check if move doesnt check yourself
	_board._board; // move to next tile
	_board._board; // get prev tile empty
	return (true);
}

bool GameMaster::isDraw()
{
	return (true);
}

bool GameMaster::isCheckmate()
{
	return(true);
	return(false);
}

bool GameMaster::isCheck()
{
	return(true);
	return(false);
}

void GameMaster::translateToFEN()
{
	convertToFenStr(_board);
}

void GameMaster::enPassant()
{

}

void GameMaster::Castle(playerSide p, boardSide b)
{
	//move king by 2 tiles
	//get rook next to it
}
};