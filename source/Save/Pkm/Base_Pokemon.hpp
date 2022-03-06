#ifndef BASE_POKEMON
#define BASE_POKEMON

#include <string>

class Base_Pokemon {
public:
	uint32_t get_PID();
	uint16_t get_dex_number();
	std::string& get_name();

protected:
	uint32_t m_PID;
	uint16_t m_dex_number;
	std::string m_name;
};

#endif // !BASE_POKEMON
