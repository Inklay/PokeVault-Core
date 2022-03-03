#ifndef ASAVE
#define ASAVE

#include <string>
#include <vector>

class ASave {
public:
    ASave(void);
    enum class Game {
        DIAMOND,
        PEARL,
        PLATINUM
    };
    std::string &get_username(void);
    uint16_t get_trainer_id(void);
    virtual void load(void) = 0;
    virtual void init(std::string& path) = 0;

protected:
    std::vector<char> open_file(std::string& path);

    std::string m_username;
    uint16_t m_trainer_id;
    uint16_t m_hours;
    uint8_t m_minutes;
    uint8_t m_seconds;
    Game m_game;
};

#endif // !ASAVE