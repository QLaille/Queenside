#ifndef QUEENSIDE_CLIENT_HPP
#define QUEENSIDE_CLIENT_HPP

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

#include <iostream>

using boost::asio::ip::tcp;

namespace Queenside {


class Client {
public:
	typedef boost::shared_ptr<Client> pointer;
	Client(boost::asio::io_service&);
	Client() = default;
	~Client() = default;
	static pointer create(boost::asio::io_service&);
	std::shared_ptr<tcp::socket>& socket();

	void setClientID(std::string&);
	const std::string &getClientID();
	const std::shared_ptr<tcp::socket> &getClientSocket();
private:
	std::string _clientId;
	std::shared_ptr<tcp::socket> _socket;
};
};

#endif /* !QUEENSIDE_CLIENT_HPP */