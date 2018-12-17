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
	Broadcaster bd = Broadcaster::getInstance();
	Coordinator cd = Coordinator::getInstance();

	bd.removeClient(_clientID);
	cd.removeClient(_clientID);
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
		std::copy_n(boost::asio::buffers_begin(_streamBuf.data()), len - 1, std::back_inserter(msg));
		request = _protocol.getRequest(msg);
		_streamBuf.consume(len);
		std::cerr << "=============" << std::endl;
		std::cerr << request._type << "\n" << request._name << "\n" << request._comment << std::endl;
		std::cerr << "=====" << std::endl;
		if (request._type == unknown)
			doWrite("UNKNOWN REQUEST");
		else
			processRequest(request);
		std::cerr << "=============" << std::endl;
	} else
		close();
}

void OneOnOne::processRequest(const request_t &req)
{
	if (req._type == uci)
		processClientUCI(req);
	else if (req._type == text)
		processClientText(req);
	else
		doWrite("I DO NOT UNDERSTAND THIS REQUEST TYPE");
}

void OneOnOne::processClientText(const request_t &req)
{
	std::string msg;

	switch (hash(req._name.c_str())) {
		case hash("JOINROOM"):
			_protocol.processJoin(_clientID, req);
			msg = "Added in room";
			break;
		case hash("QUITROOM"):
			_protocol.processQuit(_clientID, req);
			break;
		case hash("ROOMINFO"):
			_protocol.processInfoRoom(_clientID, req);
			break;
		case hash("ALLROOM"):
			_protocol.processInfoAllRoom(_clientID, req);
			break;
		case hash("READY"):
			_protocol.processReady(_clientID, req);
			break;
		default:
			msg = ("UNKNOWN UCI COMMAND");
			break;
	}
	doWrite(msg);
}

void OneOnOne::processClientUCI(const request_t &req)
{
	switch (hash(req._name.c_str())) {
		case hash("id"):
			doWrite("ID COMMAND");
			break;
		case hash("uciok"):
			doWrite("Client HAS SENT ALL INFOS AND OPTIONS");
			break;
		case hash("readyok"):
			doWrite("Client IS READY TO PLAY");
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