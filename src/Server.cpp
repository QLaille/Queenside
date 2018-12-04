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
		Client::pointer new_connection = Client::create(_acceptor.get_io_service());

		_acceptor.async_accept(*new_connection->socket(),
			boost::bind(&Server::handleAccept, this, new_connection,
				boost::asio::placeholders::error));
	}

	void Server::handleAccept(Client::pointer client, const boost::system::error_code& er)
	{
//		std::string idc = IDGenerator::getInstance().generateIDClient();
		Broadcast bd = Broadcast::getInstance();
		Coordinator cd = Coordinator::getInstance();
		std::string idc = "r";

		client->setClientID(idc);
		bd.addClient(client);
		cd.addClient(client->getClientID());
		startAccept();
//		OneOnOne::start(client);
	}
};
