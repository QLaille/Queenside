#ifndef QUEENSIDE_HPP
#define QUEENSIDE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include <list>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace Queenside
{
	enum Client_Type_e {
		PLAYER_WHITE,
		PLAYER_BLACK,
	};

	struct Cell_s {
		int y;	// letter
		int x;	// number
	};

	class IMaterial {
		public:
			virtual void move(/* new cell to move to*/);
			virtual bool isMovePossible(/*suggested cell*/);
	};

	class Board {
		public:
			Board() = default;
			~Board();
			std::string toFEN();
			bool isMovePossible(/* suggested cell by user */);
			void move(/*from cell to cell*/);
		private:
			bool _move;
			int _castleW;
			int _castleB;
			std::list<IMaterial> _whiteMats;
			std::list<IMaterial> _blackMats;
	};

	class Client {
		public:
			Client() = default;
			~Client();
		private:
			Client_Type_e _type;
//			Socket _socket;
	};

	class GameRoom {
		public:
			GameRoom() = default;
			~GameRoom();
		private:
			Client _white;
			Client _black;
			Board _board;
	};

	//singleton, creates GameRooms and handles clients not in game rooms
	class Lobby {
		public:
			Lobby() = default;
			~Lobby();
			void createGameRoom();
			void waitForInput();
		private:
			std::unordered_map<std::string, Client> clients_;
	};
};

#endif /* !QUEENSIDE_HPP */