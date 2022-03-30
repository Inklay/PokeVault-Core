#include "./PK4.hpp"
#include "../../utils/utils.hpp"
#include "../../utils/utils4.hpp"

void Pk4::init(std::vector<char> data) {
	
	m_PID = utils::value_from_vector<uint32_t>(utils::slice<char>(
		data, 0x00, 0x03));
	if (m_PID == 0)
		return;
	m_unused_temp = utils::value_from_vector<uint16_t>(utils::slice<char>(
		data, 0x04, 0x05));
	m_checksum = utils::value_from_vector<uint16_t>(utils::slice<char>(
		data, 0x06, 0x07));
	decrypt(utils::slice<char>(data, 0x08, 0x87));
}

void Pk4::decrypt(std::vector<char> data) {
	uint32_t seed = m_checksum;
	for (int i = 0; i < 128; i += 2) {
		seed = (0x41C64E6D * seed) + 0x00006073;
		data.at(i) ^= (uint8_t)((seed & 0x00ff0000) >> 16);
		data.at(i + 1) ^= (uint8_t)(seed >> 24);
	}
	int block_order_idx = ((m_PID & 0x3E000) >> 0xD) % 24;
	std::array<uint8_t, 4> block_order = unshuffle_block_order[block_order_idx];
	read_data(block_order, data);
}

void Pk4::read_data(std::array<uint8_t, 4> block_order, std::vector<char> data) {
	std::vector<char> block_a = utils::slice(data, block_order[0], block_order[0] + 31);
	std::vector<char> block_b = utils::slice(data, block_order[1], block_order[1] + 31);
	std::vector<char> block_c = utils::slice(data, block_order[2], block_order[2] + 31);
	std::vector<char> block_d = utils::slice(data, block_order[3], block_order[3] + 31);
	m_dex_number = utils::value_from_vector<uint16_t>(utils::slice<char>(
		block_a, 0, 1));
	m_name = utils::gen4::data_to_string(utils::slice<char>(block_c, 0, 0x16));
	uint8_t forms = utils::value_from_vector<uint8_t>(utils::slice(block_b, 0x18, 0x18));
	if (forms & (1 << 1))
		m_gender = Gender::FEMALE;
	else if (forms & (1 << 2))
		m_gender = Gender::GENDERLESS;
	else
		m_gender = Gender::MALE;
	get_alternate_forms(forms & (31 << 3));
}

void Pk4::get_alternate_forms(uint8_t form) {
	form /= 8;
	switch (m_dex_number) {
		case 201:
			m_alternate_form = Pk4::unown_forms.at(form);
			return;
		case 386:
			m_alternate_form = Pk4::deoxys_forms.at(form);
			return;
		case 412:
		case 413:
			m_alternate_form = Pk4::burmy_wormadam_forms.at(form);
			return;
		case 422:
		case 423:
			m_alternate_form = Pk4::shellos_gastrodon_forms.at(form);
			return;
		case 479:
			m_alternate_form = Pk4::rotom_forms.at(form);
			return;
		case 487:
			m_alternate_form = Pk4::giratina_forms.at(form);
			return;
		case 492:
			m_alternate_form = Pk4::shaymin_forms.at(form);
			return;
		case 493:
			m_alternate_form = Pk4::arceus_forms.at(form);
			return;
		default:
			m_alternate_form = "";
			return;
	}
}

#ifndef PK4_TABLES
#define PK4_TABLES

const std::array<std::string, 28> Pk4::unown_forms = {{
	"", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
	"o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "exclamation", "question"
}};

const std::array<std::string, 4> Pk4::deoxys_forms = {{
	"", "attack", "defense", "speed"
}};

const std::array<std::string, 3> Pk4::burmy_wormadam_forms = {{
	"", "sandy", "trash"
}};

const std::array<std::string, 2> Pk4::shellos_gastrodon_forms = {{
	"", "east"
}};

const std::array<std::string, 6> Pk4::rotom_forms = {{
	"", "heat", "wash", "frost", "fan", "mow"
}};

const std::array<std::string, 2> Pk4::giratina_forms = {{
	"", "origin"
}};

const std::array<std::string, 2> Pk4::shaymin_forms = {{
	"", "sky"
}};

const std::array<std::string, 17> Pk4::arceus_forms = {{
	"", "fist", "sky", "toxic", "earth", "stone", "insect", "spooky", "iron",
	"flame", "splash", "meadow", "zap", "mind", "icicle", "draco", "dread"
}};

namespace block_offset {
	uint8_t A = 0;
	uint8_t B = 32;
	uint8_t C = 64;
	uint8_t D = 96;
}

using namespace block_offset;

const std::array<std::array<uint8_t, 4>, 24> Pk4::unshuffle_block_order = {{
	{ A, B, C, D },	// 0
	{ A, B, D, C },	// 1
	{ A, C, B, D }, // 2
	{ A, D, B, C }, // 3
	{ A, C, D, B }, // 4
	{ A, D, C, B }, // 5
	{ B, A, C, D }, // 6
	{ B, A, D, C }, // 7
	{ C, A, B, D }, // 8
	{ D, A, B, C }, // 9
	{ C, A, D, B }, // 10
	{ D, A, C, B }, // 11
	{ B, C, A, D }, // 12
	{ B, D, A, C }, // 13
	{ C, B, A, D }, // 14
	{ D, B, A, C }, // 15
	{ C, D, A, B }, // 16
	{ D, C, A, B }, // 17
	{ B, C, D, A }, // 18
	{ B, D, C, A }, // 19
	{ C, B, D, A }, // 20
	{ D, B, C, A }, // 21
	{ C, D, B, A }, // 22
	{ D, C, B, A }, // 23
}};

const std::array<std::array<uint8_t, 4>, 24> Pk4::shuffle_block_order = {{
	{ A, B, C, D },	// 0
	{ A, B, D, C },	// 1
	{ A, C, B, D }, // 2
	{ A, C, D, B }, // 3
	{ A, D, B, C }, // 4
	{ A, D, B, C }, // 5
	{ B, A, C, D }, // 6
	{ B, A, D, C }, // 7
	{ B, C, A, D }, // 8
	{ B, C, D, A }, // 9
	{ B, D, A, C }, // 10
	{ B, D, C, A }, // 11
	{ C, A, B, D }, // 12
	{ C, A, D, B }, // 13
	{ C, B, A, D }, // 14
	{ C, B, D, A }, // 15
	{ C, D, A, B }, // 16
	{ C, D, B, A }, // 17
	{ D, A, B, C }, // 18
	{ D, A, C, B }, // 19
	{ D, B, A, C }, // 20
	{ D, B, C, A }, // 21
	{ D, C, A, B }, // 22
	{ D, C, B, A }, // 23
}};

#endif // !PK4_TABLES
