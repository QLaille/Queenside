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
	Broadcaster *bd = Broadcaster::getInstance();
	Coordinator *cd = Coordinator::getInstance();

	bd->removeClient(_clientID);
	cd->removeClient(_clientID);
	_socket->close();
}

void OneOnOne::start(Client client)
{
	_clientID = client.getClientID();
	doWrite(std::string(strings.text + ":" + strings.welcome + ":" + _clientID));
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
		));
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
		if (request._type == unknown)
			doWrite(strings.unknown_request);
		else
			processRequest(request);
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
	std::string msg = "INGAME:NOT_AVAILABLE";

	if (!_inGameRoom) {
		switch (hash(req._name.c_str())) {
			case hash("JOINROOM"):
				msg = strings.joinRoom + ":" + _protocol.processJoin(_clientID, req);
				break;
			case hash("QUITROOM"):
				msg =  strings.quitRoom + ":" + _protocol.processQuit(_clientID, req);
				break;
			case hash("ROOMINFO"):
				msg = strings.roomInfo + ":" + _protocol.processInfoRoom(_clientID, req);
				break;
			case hash("ALLROOM"):
				msg = strings.allRoom + ":" + _protocol.processInfoAllRoom(_clientID, req);
				break;
			case hash("STATE"):
				auto ret = _protocol.processReady(_clientID, req);
				if (ret == strings.roomReady)
					_inGameRoom = true;
				msg = strings.state + ":" + ret;
				break;
			default:
				msg = ("UNKNOWN:COMMAND");
				break;
		}
	}
	msg = "TEXT:" + msg;
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
			doWrite(strings.unavailable);
			break;
		case hash("registration"):
			doWrite(strings.unavailable);
			break;
		case hash("copyprotection"):
			doWrite(strings.unavailable);
			break;
		default:
			doWrite(strings.unknown_uci_command);
			break;
	}
}

};