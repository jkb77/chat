#include "server.hpp"

c_server::c_server(boost::asio::io_service &io_service ) :
	m_socket(io_service)
{

}

c_session c_server::start_accept(unsigned short port)
{
	boost::asio::io_service & io_service=m_socket.get_io_service();
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port); //address
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
	acceptor.accept(m_socket);
	c_dh dhpk;
	const auto pk = dhpk.pk();
	boost::asio::write(m_socket, boost::asio::buffer(pk));
	std::array<unsigned char, crypto_kx_PUBLICKEYBYTES> pk_cli;
	boost::asio::read(m_socket, boost::asio::buffer(pk_cli));
	auto keyserv = dhpk.generate_for_server(pk_cli);
	return c_session(std::move(m_socket), keyserv);
}
