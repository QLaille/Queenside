#ifndef CHESS_HPP
#define CHESS_HPP
/*
** THIS SERVER ONLY USES THE ENGLISH NOTATION FOR NOW
*/
#include <string>
#include <cstddef>
#include <array>

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
	aa = '1',
	bb = '2',
	cc = '3',
	dd = '4',
	ee = '5',
	ff = '6',
	gg = '7',
	hh = '8'
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
	std::array<std::array<char, 9>, 9> _board;
	bool		_turn;
	std::size_t	_move = 0;
	move_t		_enPassant;
	castle_t	_castles;
	std::size_t	_halfMoves = 0;
} ChessBoard_t;

///////////// GF



typedef class Pos {
public:
	std::size_t	x;
	std::size_t	y;

	friend bool	operator==(Pos const &pos1, Pos const &pos2)
	{
		return pos1.x == pos2.x && pos1.y == pos2.y;
	}
} Pos_t;

typedef struct {
	Pos_t	prevPos;
	Pos_t	postPos;
} Move_t;


#endif /* !CHESS_HPP */