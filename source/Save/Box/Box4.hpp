#ifndef BOX4_HPP
#define BOX4_HPP

#include <string>
#include "../Pkm/PK4.hpp"
#include "./Base_Box.hpp"

class Box4 : public Base_Box {
public:
	void init_pkm(std::vector<char> data);

	static const int size = 30 * Pk4::size;
	static const int name_size = 40;
};

#endif // !BOX4_HPP
