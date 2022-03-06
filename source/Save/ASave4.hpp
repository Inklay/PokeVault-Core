#ifndef ASAVE4
#define ASAVE4

#include "./ASave.hpp"
#include <array>
#include "./Block/Footer4.hpp"
#include <map>
#include "./Block/Storage4.hpp"

class ASave4 : public ASave {
public:
    ASave4(void);
    void load(void);
    Base_Box& get_current_box(void);
    Base_Box& get_box(int idx);

protected:
    int compare_save_count(uint32_t first_block, uint32_t second_bloc);
    uint16_t CRC(std::vector<char>& data);
    void get_general_footer(std::vector<char> data);
    void get_storage_footer(std::vector<char> data);
    void init(std::string& path);
    void get_general_data(std::vector<char> data);

    int m_storage_off;
    int m_storage_size;
    int m_pokedex_off;
    const size_t m_pokedex_region_size = 0x40;
    const int m_pair_off = 0x40000;
    const int m_footer_size = 0x14;
    const size_t m_max_dex_number = 493;
    int m_general_pair;
    int m_storage_pair;
    Footer4 m_general_footer;
    Footer4 m_storage_footer;
    static const std::array<uint16_t, 0x100> seeds;
    std::string m_save_path;
    Storage4 m_storage;
};

#endif // !ASAVE4
