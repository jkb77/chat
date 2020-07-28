#ifndef SESSION_HPP
#define SESSION_HPP

#include "crypto.hpp"
#include <boost/asio.hpp>
#include <queue>
#include <mutex>

class c_session {
	private:
		boost::asio::ip::tcp::socket m_socket;
		std::vector<std::byte> m_read;
		const size_t m_msg_size = 100;
		std::string m_write;
		void write_handler();
		void read_handler();
		std::queue<std::vector<std::byte>> m_outgoing;
		std::mutex m_thr_msg;
		c_crypto m_enc;

	public:
		c_session(boost::asio::ip::tcp::socket&& m_socket, s_keys & keypair);
		void write(std::string & msg);
		void start();
};

#endif // SESSION_HPP
