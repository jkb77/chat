#include "dh.hpp"

std::array<unsigned char, crypto_kx_PUBLICKEYBYTES> c_dh::pk() {
	return m_pk;
}

c_dh::c_dh() {
	crypto_kx_keypair(m_pk.data(), m_sk.data());
}

s_keys c_dh::generate_for_client(const std::array<unsigned char, crypto_kx_PUBLICKEYBYTES> & server_pk){
	s_keys ret_key;
	crypto_kx_client_session_keys(ret_key.m_key_receive.data(), ret_key.m_key_transmit.data(), m_pk.data(), m_sk.data(), server_pk.data());
	return ret_key;
}

s_keys c_dh::generate_for_server(const std::array<unsigned char, crypto_kx_PUBLICKEYBYTES> & client_pk){
	s_keys ret_key;
	crypto_kx_server_session_keys(ret_key.m_key_receive.data(), ret_key.m_key_transmit.data(), m_pk.data(), m_sk.data(), client_pk.data());
	return ret_key;
}
