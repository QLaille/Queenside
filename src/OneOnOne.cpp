#include "OneOnOne.hpp"

namespace Queenside {

OneOnOne::OneOnOne(boost::asio::io_service& io_service)
	: _socket(std::make_shared<tcp::socket>(io_service))
{
}

std::shared_ptr<tcp::socket>& OneOnOne::socket()
{
	return (_socket);
}

OneOnOne::pointer OneOnOne::create(boost::asio::io_service& io)
{
	return pointer(new OneOnOne(io));
}


void OneOnOne::start(Client client)
{
	_clientID = client.getClientID();
//	asyncDoRead();
}

//TODO: Write the asyncDoRead Method and all async methods of OneOnOne
};
