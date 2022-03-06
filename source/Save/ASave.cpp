#include "./ASave.hpp"
#include <fstream>
#include <vector>
#include <exception>

ASave::ASave(void) {}

std::vector<char> ASave::open_file(std::string& path) {
    // Opens the save file
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<char> data(size);
        file.read(data.data(), size);
        file.close();
        return data;
    }
    throw std::runtime_error("File does not exist");
}

std::string ASave::get_game_time(void) {
    return std::to_string(m_hours) + ":" + std::to_string(m_minutes);
}

std::string ASave::get_username(void) {
	return m_username;
}

uint16_t ASave::get_trainer_id(void) {
    return m_trainer_id;
}

int ASave::get_pokemon_caught(void) {
    return m_pokemon_caught;
}
