#ifndef CHESS_HPP
#define CHESS_HPP
/*
** THIS SERVER ONLY USES THE ENGLISH NOTATION FOR NOW
*/
#include <string>

#define WHITE_KING K
#define WHITE_QUEEN Q
#define WHITE_ROOK R
#define WHITE_BISHOP B
#define WHITE_KNIGHT N
#define WHITE_PAWN P

#define BLACK_KING k
#define BLACK_QUEEN q
#define BLACK_ROOK r
#define BLACK_BISHOP b
#define BLACK_KNIGHT n
#define BLACK_PAWN p

#define EMPTY_CELL '_'

enum column {
	a = 'a',
	b = 'b',
	c = 'c',
	d = 'd',
	e = 'e',
	f = 'f',
	g = 'g',
	h = 'h'
};

enum line {
	a = 1,
	b = 2,
	c = 3,
	d = 4,
	e = 5,
	f = 6,
	g = 7,
	h = 8
};

typedef
struct move_s {
	column	_col;
	line	_line;
} move_t;

typedef
struct castle_s {
	bool _whiteK;
	bool _whiteQ;
	bool _blackK;
	bool _blackQ;
} castle_t;

typedef
struct ChessBoard_s {
//	std::string	_board;
	std::array<std::array<char, 8>, 8> _board;
	bool		_turn;
	std::size_t	_move;
	move_t		_enPassant;
	castle_t	_castles;
	std::size_t	_halfMoves;
} ChessBoard_t;


#endif /* !CHESS_HPP */