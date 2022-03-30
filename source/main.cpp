#include <iostream>
#include "./Save/Game/SavePL.hpp"

int main(int argc, char** argv) {
	// Do not mind the hardcoded path, it's here to make debug easier
	SavePL save = SavePL("C:\\Users\\inkla\\AppData\\Roaming\\Citra\\sdmc\\PL.SAV");
	save.load();
	std::cout << save.get_current_box().get_pokemon_at(0).get_sprite() << std::endl;
	std::cout << save.get_current_box().get_pokemon_at(1).get_sprite() << std::endl;
	std::cout << save.get_current_box().get_pokemon_at(2).get_sprite() << std::endl;
	return 0;
}
