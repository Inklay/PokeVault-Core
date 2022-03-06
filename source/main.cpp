#include <iostream>
#include "./Save/Game/SavePL.hpp"

int main(int argc, char** argv) {
	// Do not mind the hardcoded path, it's here to make debug easier
	SavePL save = SavePL("C:\\Users\\inkla\\Desktop\\PL.SAV");
	save.load();
	std::cout << save.get_current_box().get_name() << std::endl;
	return 0;
}
