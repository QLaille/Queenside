#ifndef QUEENSIDE_CLIENT_HPP
#define QUEENSIDE_CLIENT_HPP

#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "Strings.hpp"

using boost::asio::ip::tcp;

/**
**
** Client class, defined by a socket and an ID generated at connection
**
*/

namespace Queenside {
class Client {
public:
	Client() = default;
	~Client() = default;
	Client(std::shared_ptr<tcp::socket>);

	void setClientID(std::string&);
	const std::string &getClientID();

	void setClientGameroom(std::string&);
	const std::string &getClientGameroom();

	const std::shared_ptr<tcp::socket> getSocket();
private:
	std::string _clientId;
	std::shared_ptr<tcp::socket> _socket;
	std::string _gameRoom = strings.noGameRoom;
	bool _inGameRoom = false;
};
};

#endif /* !QUEENSIDE_CLIENT_HPP */