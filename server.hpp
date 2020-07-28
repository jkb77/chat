#ifndef SERVER_HPP
#define SERVER_HPP

#include "session.hpp"
#include "dh.hpp"

class c_server {
	private:
		boost::asio::ip::tcp::socket m_socket;

	public:
		c_server(boost::asio::io_service & io_service);
		c_session start_accept(unsigned short port);
};

#endif // SERVER_HPP
