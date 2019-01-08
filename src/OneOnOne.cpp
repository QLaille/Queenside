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
	std::string ret;

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
			{
				ret = _protocol.processReady(_clientID, req);
				if (ret == strings.roomReady)
					initiateGame();
				msg = strings.state + ":" + ret;
				break;
			}
			default:
				msg = ("UNKNOWN:COMMAND");
				break;
		}
	}
	msg = "TEXT:" + msg;
	doWrite(msg);
}

void OneOnOne::initiateGame()
{
	auto gs = Gamesync::getInstance();
	auto cd = Coordinator::getInstance();
	auto bc = Broadcaster::getInstance();
	std::vector<std::string> players;
	Client client;

	if (auto room = cd->findRoomOfClient(_clientID))
		players = cd->dumpPlayerFromRoom(room.value());
	if (players.size() == 2) {
		_inGameRoom = true;
		auto gameRoom = gs->createGameMaster(players[0], players[1]);
		if (auto cli = bc->getClient(players[0]))
			client = cli.value();
			client.setClientGameroom(gameRoom);
		if (auto cli = bc->getClient(players[1]))
			client = cli.value();
			client.setClientGameroom(gameRoom);
	}
}

void OneOnOne::processClientUCI(const request_t &req)
{
	std::string msg = "GAME:NOT_IN_GAME";
	auto bc = Broadcaster::getInstance();
	auto gs = Gamesync::getInstance();
	Client client;

	if (auto cli = bc->getClient(_clientID)) {
		client = cli.value();
		switch (hash(req._name.c_str())) {
			case hash("id"):
				msg = gs->idToGameMaster(client.getClientGameroom(), _clientID, req._comment);
				break;
			case hash("uciok"):
				msg = gs->uciokToGameMaster(client.getClientGameroom(), _clientID, req._comment);
				break;
			case hash("readyok"):
				msg = gs->readyokToGameMaster(client.getClientGameroom(), _clientID, req._comment);
				break;
			case hash("bestmove"):
				msg = gs->bestmoveToGameMaster(client.getClientGameroom(), _clientID, req._comment);
				break;
			case hash("info"):
				msg = gs->infoToGameMaster(client.getClientGameroom(), _clientID, req._comment);
				break;
			case hash("option"):
				msg = strings.unavailable;
				break;
			case hash("registration"):
				msg = strings.unavailable;
				break;
			case hash("copyprotection"):
				msg = strings.unavailable;
				break;
			default:
				msg = strings.unknown_uci_command;
				break;
		}
	}
	msg = "UCI:" + msg;
	doWrite(msg);
}

};