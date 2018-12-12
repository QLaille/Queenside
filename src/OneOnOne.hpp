#ifndef QUEENSIDE_ONEONONE_HPP
# define QUEENSIDE_ONEONONE_HPP

#include "Client.hpp"
#include "Protocol.hpp"

#include <string>
#include <memory>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/regex.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>

using boost::asio::ip::tcp;

namespace Queenside {
class OneOnOne: public boost::enable_shared_from_this<OneOnOne> {
public:
	typedef boost::shared_ptr<OneOnOne> pointer;
	void start(Client);
	static pointer create(boost::asio::io_service&);
	std::shared_ptr<tcp::socket>& socket();
private:
	OneOnOne(boost::asio::io_service&);

	/* Terminate */
	void close();
	/* Communicate */
	void asyncDoRead(const boost::system::error_code& er);
	void doWrite(std::string);

	/* Process Request */
	void extractRequest(const boost::system::error_code& er, std::size_t len);
	void processRequest(const request_t&);
	void processPlayerText(const request_t &req);
	void processPlayerUCI(const request_t &req);

	std::shared_ptr<tcp::socket> _socket;
	std::string _clientID;
	boost::asio::streambuf _streamBuf;
	Protocol _protocol;
};
};

#endif /* !QUEENSIDE_ONEONONE_HPP */