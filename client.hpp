#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "session.hpp"

class c_client {
	private:
		boost::asio::ip::tcp::socket m_socket;

	public:
		c_client(boost::asio::io_service & io_service);
		c_session start_connect(const std::string & ip, unsigned short port);

};


#endif // CLIENT_HPP
