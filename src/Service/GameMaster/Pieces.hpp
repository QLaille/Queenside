/*
** EPITECH PROJECT, 2018
** Queenside
** File description:
** Pieces.hpp
*/

#pragma once

#include <vector>

#include "Chess.hpp"

namespace Queenside {
	class Pawn {
	public:
		static bool validMove(ChessBoard_t const &chess, Move_t const &move);
		static bool hasNotMoved(ChessBoard_t const &chess, Pos_t const &pos);
	};

	class Rook {
	public:
		static bool validMove(ChessBoard_t const &chess, Move_t const &move);
	};

	class Knight {
	public:
		static bool validMove(ChessBoard_t const &chess, Move_t const &move);
	};

	class Bishop {
	public:
		static bool validMove(ChessBoard_t const &chess, Move_t const &move);
	};

	class Queen {
	public:
		static bool validMove(ChessBoard_t const &chess, Move_t const &move);
	};

	class King {
	public:
		static bool validMove(ChessBoard_t const &chess, Move_t const &move);
		static bool isPosInCheck(ChessBoard_t const &chess, Move_t const &move);
		static bool isInCheck(ChessBoard_t const &chess, Pos_t const &pos);
	};

	class Logic {
	public:
		static bool			isWhite(ChessBoard_t const &chess, Pos_t const &pos);
		static bool			isBlack(ChessBoard_t const &chess, Pos_t const &pos);
		static bool			isPiece(ChessBoard_t const &chess, Pos_t const &pos);
		static bool			isOpponent(ChessBoard_t const &chess, Move_t const &move);
		static bool			isAlly(ChessBoard_t const &chess, Move_t const &move);
		static std::vector<Pos_t>	getAllHorizontal(ChessBoard_t const &chess, Pos_t const &pos);
		static std::vector<Pos_t>	getAllVertical(ChessBoard_t const &chess, Pos_t const &pos);
		static std::vector<Pos_t>	getAllDiagonal(ChessBoard_t const &chess, Pos_t const &pos);
	};
}