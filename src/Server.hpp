#ifndef QUEENSIDE_SERVER_HPP
#define QUEENSIDE_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

#include "SwitchWithStrings.hpp"
#include "IDGenerator.hpp"
#include "Client.hpp"
#include "Broadcast.hpp"
#include "Coordinator.hpp"

#define SERVER_PORT 4242

using boost::asio::ip::tcp;

namespace Queenside {
class Server {
public:
	Server() = default;
	Server(boost::asio::io_service&, std::size_t);
private:
	void startAccept();
	void handleAccept(Client::pointer, const boost::system::error_code&);

	tcp::acceptor _acceptor;
//	std::list<GameMaster> _games;
};
};

#endif /* !QUEENSIDE_SERVER_HPP */