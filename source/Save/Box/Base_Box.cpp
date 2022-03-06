#include "Base_Box.hpp"

std::string Base_Box::get_name(void) {
	return m_name;
}

Base_Pokemon& Base_Box::get_pokemon_at(int idx) {
	return m_pokemons[idx];
}

void Base_Box::set_name(std::string name) {
	m_name = name;
}
