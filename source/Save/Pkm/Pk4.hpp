#ifndef PK4_HPP
#define PK4_HPP

#include <vector>
#include <utility>
#include <array>
#include "./Base_Pokemon.hpp"

class Pk4 : public Base_Pokemon {
public:
	void init(std::vector<char> data);
	void decrypt(std::vector<char> data);
	void read_data(std::array<uint8_t, 4> block_order, std::vector<char> data);

	static const int size = 136;

private:
	uint16_t m_unused_temp;
	uint16_t m_checksum;
	static const std::array<std::array<uint8_t, 4>, 24> shuffle_block_order;
	static const std::array<std::array<uint8_t, 4>, 24> unshuffle_block_order;
};

#endif // !PK4_HPP
