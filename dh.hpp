#ifndef DH_HPP
#define DH_HPP

#include "keys.hpp"

class c_dh {
		std::array<unsigned char, crypto_kx_PUBLICKEYBYTES> m_pk;
		std::array<unsigned char, crypto_kx_SECRETKEYBYTES> m_sk;

	public:
		s_keys generate_for_client(const std::array<unsigned char, crypto_kx_PUBLICKEYBYTES> & server_pk);
		s_keys generate_for_server(const std::array<unsigned char, crypto_kx_PUBLICKEYBYTES> & client_pk);
		std::array<unsigned char, crypto_kx_PUBLICKEYBYTES> pk();
		c_dh();
};

#endif // DH_HPP
