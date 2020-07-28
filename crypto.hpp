#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include "keys.hpp"
#include <vector>
#include <cstddef>
#include <string>

class c_crypto {
		s_keys m_key_pair;
		std::array<unsigned char, crypto_secretbox_NONCEBYTES> nonce;
	public:
		std::vector<std::byte> encrypt(std::string & msg);
		std::string decrypt(std::vector<std::byte> & enc);
		c_crypto(s_keys & keys);
};

#endif // CRYPTO_HPP
