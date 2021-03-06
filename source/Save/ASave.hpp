#ifndef ASAVE
#define ASAVE

#include <string>
#include <vector>
#include "./Box/Base_Box.hpp"

class ASave {
public:
    ASave(void);
    enum class Game {
        SOULSILVER,
        HEARTGOLD,
        PLATINUM,
        PEARL,
        DIAMOND
    };
    std::string get_username(void);
    uint16_t get_trainer_id(void);
    int get_pokemon_caught(void);
    virtual void load(void) = 0;
    virtual void init(std::string& path) = 0;
    std::string get_game_time(void);
    virtual Base_Box& get_current_box(void) = 0;
    virtual Base_Box& next_box(void) = 0;
    virtual Base_Box& prev_box(void) = 0;
    virtual Base_Pokemon& get_pokemon_at(int idx) = 0;

protected:
    std::vector<char> open_file(std::string& path);

    std::string m_username;
    int m_pokemon_caught;
    uint16_t m_trainer_id;
    uint16_t m_hours;
    uint8_t m_minutes;
    Game m_game;
};

#endif // !ASAVE