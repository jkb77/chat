#include "crypto.hpp"

std::vector<std::byte> c_crypto::encrypt(std::string & msg) {
	std::vector<std::byte> ciphertext;
	ciphertext.resize(crypto_secretbox_MACBYTES+msg.size());
	auto *ciper = reinterpret_cast<unsigned char *>(ciphertext.data());
	const auto *message = reinterpret_cast<const unsigned char *>(msg.data());
	crypto_secretbox_easy(ciper, message, msg.size(), nonce.data(), m_key_pair.m_key_transmit.data());
	return ciphertext;
}

std::string c_crypto::decrypt(std::vector<std::byte> & enc) {
	auto *message = reinterpret_cast<unsigned char *>(enc.data());
	std::vector<unsigned char>decrypt;
	decrypt.resize(enc.size()-crypto_secretbox_MACBYTES); //todo
	crypto_secretbox_open_easy(decrypt.data(), message, enc.size(), nonce.data(), m_key_pair.m_key_receive.data());
	std::string msg(reinterpret_cast<const char *>(decrypt.data()));
	return msg;
}

c_crypto::c_crypto(s_keys &keys) {
	nonce.fill(0);
	m_key_pair = keys;
}
