#include "./SavePL.hpp"

SavePL::SavePL(std::string path) {
    // Sets block offsets for Platinum save
    m_storage_off = 0x0CF2C;
    m_storage_size = 0x121E4;
    m_pokedex_off = 0x01328;

    m_game = Game::PLATINUM;

    init(path);
}
