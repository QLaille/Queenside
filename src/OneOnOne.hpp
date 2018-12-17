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
#include <numeric>

#include "Broadcaster.hpp"
#include "Coordinator.hpp"


using boost::asio::ip::tcp;

/**
**
**	OneOnOne class
**
**	Some would call it PeerToPeer, but this is the class used to communicate with a single client
**	Managed by boost, it continuously loops between doRead and methods to parse a request
*/

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
	void processClientText(const request_t &req);
	void processClientUCI(const request_t &req);

	/* Do Request */
	void processJoin(const std::string&);
	void processQuit(const std::string&);
	void processInfoRoom(const std::string&);
	void processInfoAllRoom(const std::string&);
	void processReady(const std::string&);

	std::shared_ptr<tcp::socket> _socket;
	std::string _clientID;
	boost::asio::streambuf _streamBuf;
	Protocol _protocol;
};
};

#endif /* !QUEENSIDE_ONEONONE_HPP */