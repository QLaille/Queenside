#ifndef QUEENSIDE_CLIENT_HPP
#define QUEENSIDE_CLIENT_HPP

#include <string>

namespace Queenside {
class Client {
public:
	Client() = default;
	~Client() = default;

	void setClientID(std::string&);
	const std::string &getClientID();
private:
	std::string _clientId;
};
};

#endif /* !QUEENSIDE_CLIENT_HPP */