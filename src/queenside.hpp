#ifndef QUEENSIDE_HPP
#define QUEENSIDE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

namespace Queenside
{
	class Board {
	//list of materials of white and black
	// board state
	//can convert to FEN
	};

	class Ipiece {
	// defined by its possible moves
	};

	class Client {
		// Type (white, black, spectator)
		// Socket
	};

	//when destroyed, a gameroom returns the clients to the lobby
	class GameRoom {
	// client1
	// client2
	// spectators
	// board
	private:
		Client _white;
		Client _black;
		Board _board;
	};

	//singleton, creates GameRooms and handles lone clients
	class Lobby {
	//array of Clients not in GameRoom
	};
}

#endif /* !QUEENSIDE_HPP */