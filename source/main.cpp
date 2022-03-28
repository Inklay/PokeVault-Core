#include <iostream>
#include "./Save/Game/SavePL.hpp"

int main(int argc, char** argv) {
	// Do not mind the hardcoded path, it's here to make debug easier
	SavePL save = SavePL("C:\\Users\\inkla\\AppData\\Roaming\\Citra\\sdmc\\PL.SAV");
	save.load();
	std::cout << (int)save.get_current_box().get_pokemon_at(0).get_gender() << std::endl;
	std::cout << (int)save.get_current_box().get_pokemon_at(1).get_gender() << std::endl;
	std::cout << (int)save.get_current_box().get_pokemon_at(2).get_gender() << std::endl;
	return 0;
}
