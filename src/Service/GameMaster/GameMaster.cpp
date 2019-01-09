#include "GameMaster.hpp"

#include "FENConvertor.hpp"

namespace Queenside {

GameMaster::GameMaster(std::pair<std::string, std::string> players)
: _white(players.first), _black(players.second)
{
	_whiteTurn = true;
//	_board._board[0] = std::array<char,9>("RNBQKBNR");
	_board._board[0] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
	_board._board[1] = {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'};
	_board._board[2] = {'_', '_', '_', '_', '_', '_', '_', '_'};
	_board._board[3] = {'_', '_', '_', '_', '_', '_', '_', '_'};
	_board._board[4] = {'_', '_', '_', '_', '_', '_', '_', '_'};
	_board._board[5] = {'_', '_', '_', '_', '_', '_', '_', '_'};
	_board._board[6] = {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'};
	_board._board[7] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
	// _board._board =
	// {"RNBQKBNR",
	// "PPPPPPPP",
	// "________",
	// "________",
	// "________",
	// "________",
	// "pppppppp",
	// "rnbqkbnr"};
}

const bool &GameMaster::isWhiteTurn()
{
	return (_whiteTurn);
}

void GameMaster::nextTurn()
{
	_whiteTurn = !_whiteTurn;
}


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

void GameMaster::startGame()
{
	std::cerr << "Starting game between " << _white.getId() << " and " << _black.getId() << std::endl;
}

bool GameMaster::playPiece(bool player, Move_t move)
{
	ChessPlayer cp = (bool)player ? _white : _black;

	//check if move doesnt check yourself
	_board._board[move.postPos.y][move.postPos.x] = _board._board[move.prevPos.y][move.prevPos.x];
	_board._board[move.prevPos.y][move.prevPos.x] = EMPTY_CELL;
	_board._halfMoves += 1;
	if (player)
		_board._move += 1;
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

const std::string GameMaster::translateToFEN()
{
	return (convertToFenStr(_board));
}

void GameMaster::enPassant()
{

}

void GameMaster::Castle(playerSide p, boardSide b)
{
	//move king by 2 tiles
	//get rook next to it
}

const ChessBoard_t &GameMaster::getBoard()
{
	return (_board);
}

const ChessPlayer &GameMaster::getWhite()
{
	return (_white);
}

const ChessPlayer &GameMaster::getBlack()
{
	return (_black);
}

};