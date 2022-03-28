#include "./Base_Pokemon.hpp"
#include <sstream>

uint32_t Base_Pokemon::get_PID(void) {
	return m_PID;
}

uint16_t Base_Pokemon::get_dex_number(void) {
	return m_dex_number;
}

std::string& Base_Pokemon::get_name(void) {
	return m_name;
}

std::string Base_Pokemon::get_sprite(void) {
	std::stringstream ss;
	if (m_dex_number < 10)
		ss << "00";
	else if (m_dex_number < 100)
		ss << "0";
	ss << m_dex_number;
	return ss.str();
}

Base_Pokemon::Gender Base_Pokemon::get_gender(void) {
	return m_gender;
}
