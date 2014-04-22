#ifndef CLIENT_SELECTOR_HPP
#define CLIENT_SELECTOR_HPP

#include "data/server/Client.hpp"

class ClientSelector {

	public:
	ClientSelector(const std::vector<Client*>& data);
	Client* next();

	private:
	const std::vector<Client*>& data;
};

#endif
