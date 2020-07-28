#include "client.hpp"
#include "dh.hpp"

c_client::c_client(boost::asio::io_service &io_service) :
	m_socket(io_service)
{

}

c_session c_client::start_connect(const std::string &ip, unsigned short port)
{
	auto ipv4 = boost::asio::ip::address_v4::from_string(ip);
	boost::asio::ip::tcp::endpoint endpoint(ipv4, port);
	m_socket.connect(endpoint);
	c_dh dhpk;
	const auto pk = dhpk.pk();
	boost::asio::write(m_socket, boost::asio::buffer(pk));
	std::array<unsigned char, crypto_kx_PUBLICKEYBYTES> pk_srv;
	boost::asio::read(m_socket, boost::asio::buffer(pk_srv));
	auto keyserv = dhpk.generate_for_client(pk_srv);
	return c_session(std::move(m_socket), keyserv);
}
