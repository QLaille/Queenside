#include "Server.hpp"

namespace Queenside {

	Server::Server(boost::asio::io_service& io, std::size_t port)
	: _acceptor(io, tcp::endpoint(tcp::v4(), port))
	{
		std::srand(std::time(nullptr));
		startAccept();
	}

	void Server::startAccept()
	{
		OneOnOne::pointer new_connection = OneOnOne::create(_acceptor.get_io_service());

		_acceptor.async_accept(*new_connection->socket(),
			boost::bind(&Server::handleAccept, this, new_connection,
				boost::asio::placeholders::error));
	}

	void Server::handleAccept(OneOnOne::pointer newConnection, const boost::system::error_code& er)
	{
		Broadcaster bd = Broadcaster::getInstance();
		Coordinator *cd = Coordinator::getInstance();
		Client client(newConnection->socket());
		std::string idc = generateClientID();

		while (bd.getClient(idc) != std::nullopt)
			idc = generateClientID();
		client.setClientID(idc);
		bd.addClient(client);
		cd->addClient(client.getClientID());
		startAccept();
		newConnection->start(client);
	}
};
