#ifndef KEYS_HPP
#define KEYS_HPP

#include <sodium.h>
#include <array>

struct s_keys {
	std::array<unsigned char, crypto_kx_SESSIONKEYBYTES> m_key_receive;
	std::array<unsigned char, crypto_kx_SESSIONKEYBYTES> m_key_transmit;
};


#endif // KEYS_HPP
