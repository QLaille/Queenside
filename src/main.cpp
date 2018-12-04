#include "Server.hpp"

int main(int ac, char **av)
{
	boost::asio::io_service io;
	Queenside::Server server(io, SERVER_PORT);

	io.run();
	return (0);
}