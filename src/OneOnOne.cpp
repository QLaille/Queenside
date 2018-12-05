#include "OneOnOne.hpp"

namespace Queenside {

OneOnOne::OneOnOne(boost::asio::io_service& io_service)
	: _socket(std::make_shared<tcp::socket>(io_service))
{}

std::shared_ptr<tcp::socket>& OneOnOne::socket()
{
	return (_socket);
}

OneOnOne::pointer OneOnOne::create(boost::asio::io_service& io)
{
	return pointer(new OneOnOne(io));
}

void OneOnOne::close()
{
	//remove client from broadcast
	_socket->close();
}

void OneOnOne::start(Client client)
{
	_clientID = client.getClientID();
	doWrite(std::string("WELCOME"));
}

void OneOnOne::doWrite(std::string msg)
{
	boost::asio::async_write(*_socket,
		boost::asio::buffer(msg + "\n"),
		boost::bind(&OneOnOne::asyncDoRead,
			shared_from_this(),
			boost::asio::placeholders::error)
	);
}

void OneOnOne::asyncDoRead(const boost::system::error_code& er)
{
	if (!er) {
		boost::asio::async_read_until(*_socket,
			_streamBuf,
			"\n",
			boost::bind(&OneOnOne::extractRequest,
				shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);
	} else
		close();
}

void OneOnOne::extractRequest(const boost::system::error_code& er, std::size_t len)
{
	std::string msg;
	request_t request;

	if (!er) {
		std::copy_n(boost::asio::buffers_begin(_streamBuf.data()), len, std::back_inserter(msg));
		request = _protocol.getRequest(msg);
		_streamBuf.consume(len);
		if (request._type == unknown)
			doWrite("UNKNOWN REQUEST");
		else
			processRequest(request);
	} else
		close();
}

void OneOnOne::processRequest(const request_t &req)
{
	if (req._type == uci)
		processPlayerUCI(req);
	else
		doWrite("REQUEST TYPE NOT SUPPORTED ATM");
//	else
//		processClient(req);
}

void OneOnOne::processPlayerUCI(const request_t &req)
{
	switch (hash(req._name.c_str())) {
		case hash("id"):
			doWrite("ID COMMAND");
			break;
		case hash("uciok"):
			doWrite("PLAYER HAS SENT ALL INFOS AND OPTIONS");
			break;
		case hash("readyok"):
			doWrite("PLAYER IS READY TO PLAY");
			break;
		case hash("bestmove"):
			doWrite("PLAYING" + req._comment);
			break;
		case hash("info"):
			doWrite("USED FOR LOGS");
			break;
		case hash("option"):
			doWrite("NOT AVAILABLE ATM");
			break;
		case hash("registration"):
			doWrite("NOT AVAILABLE ATM");
			break;
		case hash("copyprotection"):
			doWrite("NOT AVAILABLE ATM");
			break;
		default:
			doWrite("UNKNOWN UCI COMMAND");
			break;
	}
}

};