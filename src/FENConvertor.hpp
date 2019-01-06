#ifndef QUEENSIDE_FEN_CONVERTOR_HPP
#define QUEENSIDE_FEN_CONVERTOR_HPP

#include <string>
#include <sstream>
#include <array>

#include "Chess.hpp"

std::string lineToString(std::array<char, 8> ar)
{
	std::stringstream ret;
	int i = 0;

	for (int j = 0; j < 8; j++) {
		if (ar[j] == EMPTY_CELL) {
			i += 1;
		} else {
			if (i != 0)
				ret << i;
			ret << ar[j];
			i = 0;
		}
	}
	return (ret.str());
}

std::string boardToString(std::array<std::array<char, 8>, 8> board)
{
	std::stringstream ret;

	for (int i = 0; i < 8; i++) {
		ret << lineToString(board[i]);
		if (i != 7)
			ret << "/";
	}
	return (ret.str());
}

std::string moveToString(const move_t &move)
{
	std::string ret("");

//	ret += move._col;
//	ret += std::to_string(move._line);
	return (ret);
}

std::string castlesToString(const castle_t &castles)
{
	std::string ret("");

	ret += castles._whiteK ? "K" : "";
	ret += castles._whiteQ ? "Q" : "";
	ret += castles._blackK ? "k" : "";
	ret += castles._blackQ ? "q" : "";
	ret = ret.length() == 0 ? "-" : ret;
	return (ret);
}

std::string convertToFenStr(ChessBoard_t &board)
{
	std::stringstream ret;

	ret << boardToString(board._board) << " "
	<< (board._turn == true ? "w" : "b") << " "
	<< castlesToString(board._castles) << " "
	<< moveToString(board._enPassant) << " "
	<< std::to_string(board._halfMoves) << " "
	<< std::to_string(board._move);
	return (ret.str());
}

#endif /* !QUEENSIDE_FEN_CONVERTOR_HPP */