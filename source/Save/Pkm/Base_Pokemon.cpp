#include "./Base_Pokemon.hpp"

uint32_t Base_Pokemon::get_PID(void) {
	return m_PID;
}

uint16_t Base_Pokemon::get_dex_number() {
	return m_dex_number;
}

std::string& Base_Pokemon::get_name() {
	return m_name;
}
