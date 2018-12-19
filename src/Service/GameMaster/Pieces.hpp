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
	class Piece {
	public:
		virtual bool validMove(ChessBoard_t chess, Move_t move);
	};

	class Pawn : public Piece {
	public:
		bool validMove(ChessBoard_t chess, Move_t move);
		bool hasNotMoved(ChessBoard_t chess, Pos_t pos);
	};

	class Rook : public Piece {
	public:
		bool validMove(ChessBoard_t chess, Move_t move);
	};

	class Knight : public Piece {
	public:
		bool validMove(ChessBoard_t chess, Move_t move);
	};

	class Bishop : public Piece {
	public:
		bool validMove(ChessBoard_t chess, Move_t move);
	};

	class Queen : public Piece {
	public:
		bool validMove(ChessBoard_t chess, Move_t move);
	};

	class King : public Piece {
	public:
		bool validMove(ChessBoard_t chess, Move_t move);
		bool isInCheck(ChessBoard_t chess, Pos_t pos);
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
		static std::vector<Pos_t>	getAllVertical(ChessBoard_t chess, Pos_t pos);
	};
}