#ifndef BOX4
#define BOX4

#include <string>
#include "../Pkm/PK4.hpp"

class Box4 {
public:
	void init_pkm(std::vector<char> data);
	void set_name(std::string name);

	static const int size = 30 * Pk4::size;
	static const int name_size = 40;

protected:
	std::array<Pk4, 30> m_pokemons;
	std::string m_name;
};

#endif // !BOX4
