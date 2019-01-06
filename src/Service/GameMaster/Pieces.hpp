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
		static bool validMove(ChessBoard_t chess, Move_t move);
		static bool hasNotMoved(ChessBoard_t chess, Pos_t pos);
	};

	class Rook {
	public:
		static bool validMove(ChessBoard_t chess, const Move_t move);
	};

	class Knight {
	public:
		static bool validMove(ChessBoard_t chess, Move_t move);
	};

	class Bishop {
	public:
		static bool validMove(ChessBoard_t chess, Move_t move);
	};

	class Queen {
	public:
		static bool validMove(ChessBoard_t chess, Move_t move);
	};

	class King {
	public:
		static bool validMove(ChessBoard_t chess, Move_t move);
		static bool isPosInCheck(ChessBoard_t chess, Move_t move);
		static bool isInCheck(ChessBoard_t chess, Pos_t pos);
	};

	class Logic {
	public:
		static bool			isWhite(ChessBoard_t chess, Pos_t pos);
		static bool			isBlack(ChessBoard_t chess, Pos_t pos);
		static bool			isPiece(ChessBoard_t chess, Pos_t pos);
		static bool			isOpponent(ChessBoard_t chess, Move_t move);
		static bool			isAlly(ChessBoard_t chess, Move_t move);
		static std::vector<Pos_t>	getAllHorizontal(ChessBoard_t chess, Pos_t pos);
		static std::vector<Pos_t>	getAllVertical(ChessBoard_t chess, Pos_t pos);
		static std::vector<Pos_t>	getAllDiagonal(ChessBoard_t chess, Pos_t pos);
	};
}