#ifndef BASE_BOX_HPP
#define BASE_BOX_HPP

#include <string>
#include <array>
#include "../Pkm/Base_Pokemon.hpp"

class Base_Box {
public:
	std::string get_name(void);
	Base_Pokemon& get_pokemon_at(int idx);
	void set_name(std::string name);

protected:
	std::array<Base_Pokemon, 30> m_pokemons;
	std::string m_name;
};

#endif // !BASE_BOX_HPP