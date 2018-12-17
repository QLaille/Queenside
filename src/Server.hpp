#ifndef QUEENSIDE_SERVER_HPP
#define QUEENSIDE_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>

#include "SwitchWithStrings.hpp"
#include "IDGenerator.hpp"
#include "OneOnOne.hpp"

#include "Broadcaster.hpp"
#include "Coordinator.hpp"

#define SERVER_PORT 4242

using boost::asio::ip::tcp;

/**
**
**	Server class
**
**	"Entry point" of the server, accepts new connection and opens a OneOnOne
**
*/

namespace Queenside {
class Server {
public:
	Server() = default;
	Server(boost::asio::io_service&, std::size_t);
private:
	void startAccept();
	void handleAccept(OneOnOne::pointer newConnection, const boost::system::error_code& er);

	tcp::acceptor _acceptor;
//	std::list<GameMaster> _games;
};
};

#endif /* !QUEENSIDE_SERVER_HPP */