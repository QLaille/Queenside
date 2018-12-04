#ifndef QUEENSIDE_ONEONONE_HPP
# define QUEENSIDE_ONEONONE_HPP

#include "Client.hpp"
#include "Protocol.hpp"

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

namespace Queenside {
class OneOnOne {
public:
	typedef boost::shared_ptr<OneOnOne> pointer;
	void start(Client);
	static pointer create(boost::asio::io_service&);
	std::shared_ptr<tcp::socket>& socket();
private:
	OneOnOne(boost::asio::io_service&);

	std::shared_ptr<tcp::socket> _socket;
	std::string _clientID;
};
};

#endif /* !QUEENSIDE_ONEONONE_HPP */