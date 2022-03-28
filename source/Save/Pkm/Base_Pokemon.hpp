#ifndef BASE_POKEMON
#define BASE_POKEMON

#include <string>

class Base_Pokemon {
public:
	enum class Gender {
		MALE,
		FEMALE,
		GENDERLESS
	};

	uint32_t get_PID(void);
	uint16_t get_dex_number(void);
	std::string& get_name(void);
	std::string get_sprite(void);
	Gender get_gender(void);

protected:
	uint32_t m_PID;
	uint16_t m_dex_number;
	std::string m_name;
	Gender m_gender;
};

#endif // !BASE_POKEMON
