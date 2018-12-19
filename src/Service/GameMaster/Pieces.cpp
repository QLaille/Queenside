/*
** EPITECH PROJECT, 2018
** Queenside
** File description:
** Pieces.cpp
*/

#include <cctype>
#include <algorithm>

#include "Pieces.hpp"

namespace Queenside {

	// Pawn

	bool Pawn::validMove(ChessBoard_t chess, Move_t move)
	{
		int dir = (Logic::isWhite(chess, move.prevPos) ? 1 : -1);
		if (Logic::isAlly(chess, move)) {
			return false;
		} else if (	move.postPos.y == move.prevPos.y &&
				move.postPos.x == move.prevPos.x + 1 * dir) {
			// simple move
			return true;
		} else if (	hasNotMoved(chess, move.prevPos) &&
				move.postPos.y == move.prevPos.y &&
				move.postPos.x == move.prevPos.x + 2 * dir) {
			// double move
			return true;
		} else if (	chess._board[move.postPos.y][move.postPos.x] ==
				chess._board[move.prevPos.y - 1 * dir][move.prevPos.x + 1] ||
				chess._board[move.postPos.y][move.postPos.x] ==
				chess._board[move.prevPos.y - 1 * dir][move.prevPos.x - 1]) {
			// attack
			if (Logic::isOpponent(chess, move)) {
				return true;
			}
		}
		// TODO en passant
		return false;
	}

	bool Pawn::hasNotMoved(ChessBoard_t chess, Pos_t pos)
	{
		if (Logic::isWhite(chess, pos) && pos.y == line(1)) {
			return true;
		} else if (Logic::isBlack(chess, pos) && pos.y == line(6)) {
			return true;
		}
		return false;
	}

	// Rook

	bool	Rook::validMove(ChessBoard_t chess, Move_t move)
	{
		if (Logic::isAlly(chess, move)) {
			return false;
		}
		std::vector<Pos_t>	allHorizontal = Logic::getAllHorizontal(chess, move.prevPos);
		std::vector<Pos_t>	allVertical = Logic::getAllVertical(chess, move.prevPos);
		if (std::find(allHorizontal.begin(), allHorizontal.end(), move.postPos) != allHorizontal.end()) {
			return true;
		} else if (std::find(allVertical.begin(), allVertical.end(), move.postPos) != allVertical.end()){
			return true;
		}
		return false;
	}

	// Knight

	bool	Knight::validMove(ChessBoard_t chess, Move_t move)
	{
		if (Logic::isAlly(chess, move)) {
			return false;
		} else if (	move.postPos.x == move.prevPos.x + 1 &&
				(move.postPos.y == move.prevPos.y + 2 ||
				move.postPos.y == move.prevPos.y - 2)) {
			// UP UP RIGHT or DOWN DOWN RIGHT
			return true;
		} else if (	move.postPos.y == move.prevPos.y + 1 &&
				(move.postPos.x == move.prevPos.x + 2 ||
				move.postPos.x == move.prevPos.x - 2)) {
			// UP RIGHT RIGHT or DOWN RIGHT RIGHT
			return true;
		} else if (	move.postPos.x == move.prevPos.x - 1 &&
				(move.postPos.y == move.prevPos.y + 2 ||
				move.postPos.y == move.prevPos.y - 2)) {
			// UP UP LEFT or DOWN DOWN LEFT
			return true;
		} else if (	move.postPos.y == move.prevPos.y - 1 &&
				(move.postPos.x == move.prevPos.x + 2 ||
				move.postPos.x == move.prevPos.x - 2)) {
			// UP LEFT LEFT or DOWN LEFT LEFT
			return true;
		}
		return false;
	}

	// Bishop

	bool	Bishop::validMove(ChessBoard_t chess, Move_t move)
	{
		if (Logic::isAlly(chess, move)) {
			return false;
		}
		std::vector<Pos_t>	allPos = Logic::getAllDiagonal(chess, move.prevPos);
		if (find(allPos.begin(), allPos.end(), move.postPos) != allPos.end()) {
			return true;
		}
		return false;
	}

	// Queen

	bool	Queen::validMove(ChessBoard_t chess, Move_t move)
	{
		if (Logic::isAlly(chess, move)) {
			return false;
		}
		std::vector<Pos_t>	allHorizontal = Logic::getAllHorizontal(chess, move.prevPos);
		std::vector<Pos_t>	allVertical = Logic::getAllVertical(chess, move.prevPos);
		std::vector<Pos_t>	allDiagonal = Logic::getAllDiagonal(chess, move.prevPos);
		if (std::find(allHorizontal.begin(), allHorizontal.end(), move.postPos) != allHorizontal.end()) {
			return true;
		} else if (std::find(allVertical.begin(), allVertical.end(), move.postPos) != allVertical.end()){
			return true;
		} else if (find(allDiagonal.begin(), allDiagonal.end(), move.postPos) != allDiagonal.end()) {
			return true;
		}
		return false;
	}

	// King

	bool	King::validMove(ChessBoard_t chess, Move_t move) {
		if (isInCheck(chess, move.postPos)) {
			return false;
		} else if (Logic::isAlly(chess, move) {
			return false;
		} else if (	(move.postPos.x == move.prevPos.x + 1 ||
				move.postPos.x == move.prevPos.x - 1) &&
				move.postPos.y == move.prevPos.y) {
			// LEFT or RIGHT
			return true;
		} else if (	(move.postPos.y == move.prevPos.y + 1 ||
				move.postPos.y == move.prevPos.y - 1) &&
				move.postPos.x == move.prevPos.x) {
			// UP or DOWN
			return true;
		} else if (	(move.postPos.x == move.prevPos.x + 1 ||
				move.postPos.x == move.prevPos.x - 1) &&
				move.postPos.y == move.prevPos.y + 1) {
			// UP LEFT or UP RIGHT
			return true;
		} else if (	(move.postPos.x == move.prevPos.x + 1 ||
				move.postPos.x == move.prevPos.x - 1) &&
				move.postPos.y == move.prevPos.y - 1) {
			// DOWN LEFT or DOWN RIGHT
			return true;
		}
		// TODO castle
		return false;
	}

	// TODO isInCheck()

	// Logic

	bool	Logic::isWhite(ChessBoard_t chess, Pos_t pos)
	{
		if (isupper(chess._board[pos.y][pos.x])) {
			return true;
		}
		return false;
	}

	bool	Logic::isBlack(ChessBoard_t chess, Pos_t pos)
	{
		if (islower(chess._board[pos.y][pos.x])) {
			return true;
		}
		return false;
	}

	bool	Logic::isPiece(ChessBoard_t chess, Pos_t pos)
	{
		if (chess._board[pos.y][pos.x] == EMPTY_CELL) {
			return false;
		}
		return true;
	}

	bool	Logic::isOpponent(ChessBoard_t chess, Move_t move)
	{
		if (	Logic::isWhite(chess, move.prevPos) &&
			Logic::isBlack(chess, move.postPos)) {
			return true;
		} else if (	Logic::isBlack(chess, move.prevPos) &&
				Logic::isWhite(chess, move.postPos)) {
			return true;
		}
		return false;
	}

	bool	Logic::isAlly(ChessBoard_t chess, Move_t move)
	{
		if (	Logic::isWhite(chess, move.prevPos) &&
			Logic::isWhite(chess, move.postPos)) {
			return true;
		} else if (	Logic::isBlack(chess, move.prevPos) &&
				Logic::isBlack(chess, move.postPos)) {
			return true;
		}
		return false;
	}

	std::vector<Pos_t>	Logic::getAllHorizontal(ChessBoard_t chess, Pos_t pos)
	{
		std::vector<Pos_t>	allPos;

		for (int i = 1; pos.x + i < 8; i++) {
			if (Logic::isAlly(chess, {pos.x + i, pos.y})) {
				break;
			}
			allPos.push_back({pos.x + i, pos.y});
			if (Logic::isOpponent(chess, {pos.x + i, pos.y})) {
				break;
			}
		}
		for (int i = 1; pos.x - i >= 0; i++) {
			if (Logic::isAlly(chess, {pos.x - i, pos.y})) {
				break;
			}
			allPos.push_back({pos.x - i, pos.y});
			if (Logic::isOpponent(chess, {pos.x - i, pos.y})) {
				break;
			}
		}
		return allPos;
	}

	std::vector<Pos_t>	Logic::getAllVertical(ChessBoard_t chess, Pos_t pos)
	{
		std::vector<Pos_t>	allPos;

		for (int i = 1; pos.y + i < 8; i++) {
			if (Logic::isAlly(chess, {pos.x, pos.y + i})) {
				break;
			}
			allPos.push_back({pos.x, pos.y + i});
			if (Logic::isOpponent(chess, {pos.x, pos.y + i})) {
				break;
			}
		}
		for (int i = 1; pos.y - i >= 0; i++) {
			if (Logic::isAlly(chess, {pos.x, pos.y - i})) {
				break;
			}
			allPos.push_back({pos.x, pos.y - i});
			if (Logic::isOpponent(chess, {pos.x, pos.y - i})) {
				break;
			}
		}
		return allPos;
	}

	std::vector<Pos_t>	Logic::getAllDiagonal(ChessBoard_t chess, Pos_t pos)
	{
		std::vector<Pos_t>	allPos;

		for (int i = 1, j = 1; pos.x + i < 8 && pos.y + j < 8; i++ && j++) {
			if (Logic::isAlly(chess, {pos.x + i, pos.y + j})) {
				break;
			}
			allPos.push_back({pos.x + i, pos.y + j});
			if (Logic::isOpponent(chess, {pos.x + i, pos.y + j})) {
				break;
			}
		}
		for (int i = 1, j = 1; pos.x - i >= 0 && pos.y - j >= 0; i++ && j++) {
			if (Logic::isAlly(chess, {pos.x - i, pos.y - j})) {
				break;
			}
			allPos.push_back({pos.x - i, pos.y - j});
			if (Logic::isOpponent(chess, {pos.x - i, pos.y - j})) {
				break;
			}
		}
		for (int i = 1, j = 1; pos.x + i < 8 && pos.y - j >= 0; i++ && j++) {
			if (Logic::isAlly(chess, {pos.x + i, pos.y - j})) {
				break;
			}
			allPos.push_back({pos.x + i, pos.y - j});
			if (Logic::isOpponent(chess, {pos.x + i, pos.y - j})) {
				break;
			}
		}
		for (int i = 1, j = 1; pos.x - i >= 0 && pos.y + j < 8; i++ && j++) {
			if (Logic::isAlly(chess, {pos.x - i, pos.y + j})) {
				break;
			}
			allPos.push_back({pos.x - i, pos.y + j});
			if (Logic::isOpponent(chess, {pos.x - i, pos.y + j})) {
				break;
			}
		}
		return allPos;
	}
}