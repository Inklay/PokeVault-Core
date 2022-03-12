#include "./ASave4.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include "./Pkm/PK4.hpp"
#include "../utils/utils4.hpp"
#include <exception>

ASave4::ASave4(void) {}

Base_Pokemon& ASave4::get_pokemon_at(int idx) {
    return m_storage.get_current_box().get_pokemon_at(idx);
}

Base_Box& ASave4::get_current_box(void) {
    return m_storage.get_current_box();
}

Base_Box& ASave4::next_box(void) {
    int idx = m_storage.get_current_box_idx() + 1;
    if (idx == 18)
        idx = 0;
    m_storage.set_current_box_idx(idx);
    return m_storage.get_current_box();
}

Base_Box& ASave4::prev_box(void) {
    int idx = m_storage.get_current_box_idx() - 1;
    if (idx == -1)
        idx = 17;
    m_storage.set_current_box_idx(idx);
    return m_storage.get_current_box();
}

void ASave4::init(std::string& path) {
    std::vector<char> data = open_file(path);
    get_general_footer(data);
    get_storage_footer(data);
    get_general_data(utils::slice<char>(data, m_general_pair, m_general_pair + m_storage_off - 1));
    m_save_path = path;
}

void ASave4::get_general_data(std::vector<char> data) {
    m_trainer_id = utils::value_from_vector<uint16_t>(utils::slice<char>(
        data, 0x78, 0x79));
    m_hours = utils::value_from_vector<uint16_t>(utils::slice<char>(
        data, 0x8A, 0x8B));
    m_minutes = utils::value_from_vector<uint8_t>(utils::slice<char>(
        data, 0x8C, 0x8C));
    m_username = utils::gen4::data_to_string(utils::slice<char>(data, 0x68, 0x77));
    m_pokemon_caught = 0;
    for (size_t byte = 0; byte < m_pokedex_region_size; byte++) {
        for (size_t bit = 0; bit < 8; bit++) {
            if (byte * 8 + bit < m_max_dex_number)
                m_pokemon_caught += (data.at(m_pokedex_off + 4 + byte) >> bit) & 1;
        }
    }
}

int ASave4::compare_save_count(uint32_t first_block, uint32_t second_block)
{
	uint32_t comp = first_block - second_block;
	if (comp >= 0)
		return 0;
	return 1;
}

uint16_t ASave4::CRC(std::vector<char>& data) {
	uint16_t sum = 0xFFFF;

    for (char c : data) {
        sum = (sum << 8) ^ seeds[((uint8_t)c ^ (uint8_t)(sum >> 8))];
    }
	return sum;
}

void ASave4::get_general_footer(std::vector<char> data) {
    std::vector<Footer4> footers;
    for (int i = 0; i < 2; i++) {
        Footer4 footer;
        footer.init(utils::slice<char>(data,
            m_storage_off + i * m_pair_off - m_footer_size,
            m_storage_off + i * m_pair_off - 1)
        );
        footers.emplace_back(footer);
    }

    // Get general block footer
    int idx = compare_save_count(
        footers.at(0).get_save_count(),
        footers.at(1).get_save_count()
    );
    m_general_pair = idx * 0x40000;

    // Check sum of general block
    std::vector<char> block = utils::slice<char>(data,
        m_general_pair,
        m_general_pair + m_storage_off - m_footer_size - 1);
    uint16_t sum = CRC(block);
    if (sum != footers.at(idx).get_checksum()) {
        idx = utils::inverse_index(idx);
        m_general_pair = idx * 0x40000;

        // Check sum for the other block
        std::vector<char> generalBlock = utils::slice<char>(data,
            m_general_pair,
            m_general_pair + m_storage_off - m_footer_size - 1);
        uint16_t generalSum = CRC(generalBlock);
        if (generalSum != footers.at(idx).get_checksum())
            // Both general blocks are corrupted, can't open the save
            throw std::runtime_error("Save file is corrupted and can not be openned");
    }
    m_general_footer = footers.at(idx);
}

void ASave4::get_storage_footer(std::vector<char> data) {
    std::vector<Footer4> footers;
    for (int i = 0; i < 2; i++) {
        Footer4 footer;
        footer.init(utils::slice<char>(data,
            m_storage_size + m_storage_off + m_pair_off * i - m_footer_size,
            m_storage_size + m_storage_off + m_pair_off * i - 1)
        );
        footers.emplace_back(footer);
    }
    int idx = 0;
    if (footers.at(1).get_storage_id() == m_general_footer.get_storage_id())
        idx = 1;
    m_storage_pair = idx * 0x40000;
    // Check sum of general block
    std::vector<char> block = utils::slice<char>(data,
        m_storage_off + m_storage_pair,
        m_storage_off + m_storage_pair + m_storage_size - m_footer_size - 1);
    uint16_t sum = CRC(block);
    if (sum != footers.at(idx).get_checksum())
        throw std::runtime_error("Save file is corrupted and can not be openned");
    m_storage_footer = footers.at(idx);
}

void ASave4::load(void) {
    std::ifstream file;
    file.open(m_save_path, std::ios::in | std::ios::binary);
    file.seekg(m_storage_off + m_storage_pair);
    std::vector<char> data(m_storage_size);
    file.read(data.data(), m_storage_size);
    file.close();
    m_storage.init(data);
}

#ifndef GEN_4_TABLES
#define GEN_4_TABLES

const std::array<uint16_t, 0x100> ASave4::seeds = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

#endif // !GEN_4_TABLES
