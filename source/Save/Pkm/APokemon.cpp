#include "./APokemon.hpp"

uint32_t APokemon::get_PID(void) {
	return m_PID;
}

uint16_t APokemon::get_dex_number() {
	return m_dex_number;
}

std::string& APokemon::get_name() {
	return m_name;
}
