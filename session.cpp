#include "session.hpp"
#include <iostream>

void c_session::write(std::string &msg) {
	m_write = msg;
	m_write.resize(m_msg_size);
	auto msg_enc =m_enc.encrypt(m_write);
	std::lock_guard<std::mutex> guard_msg(m_thr_msg);
	m_outgoing.push(msg_enc);
	write_handler();
}

void c_session::start() {
	read_handler();
}

void c_session::write_handler() {
	boost::asio::async_write(m_socket, boost::asio::buffer(m_outgoing.front()), [this] (boost::system::error_code error, std::size_t bytes_transferred) {
		if (error) {
			std::cout<<error<<std::endl;
			return;
		}
		std::lock_guard<std::mutex> guard_msg(m_thr_msg);
		assert(!m_outgoing.empty());
		m_outgoing.pop();
	});
}

void c_session::read_handler() {
	m_read.resize(m_msg_size+crypto_secretbox_MACBYTES);
	boost::asio::async_read(m_socket, boost::asio::buffer(m_read.data(), m_read.size()), [this] (boost::system::error_code error, std::size_t bytes_transferred) {
		auto msg_dec = m_enc.decrypt(m_read);
		std::string msg(reinterpret_cast<char*>(msg_dec.data()), msg_dec.size());
		if (error) {
			std::cout<<error<<std::endl;
			return;
		}
		std::cout << msg << std::endl;
		read_handler();
	});
}

c_session::c_session(boost::asio::ip::tcp::socket &&m_socket, s_keys &keypair) :
	m_socket(std::move(m_socket)), m_read() , m_write(), m_enc(keypair)
{

}
