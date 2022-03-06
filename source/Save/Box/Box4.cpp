#include "./Box4.hpp"
#include "../../utils/utils.hpp"

void Box4::init_pkm(std::vector<char> data) {
	for (int i = 0; i < 30; i++)
		static_cast<Pk4&>(m_pokemons[i]).init(utils::slice(data, i * Pk4::size, (i + 1) * Pk4::size - 1));
}

