#include "./Storage4.hpp"
#include "../../utils/utils.hpp"
#include "../../utils/utils4.hpp"

void Storage4::init(std::vector<char> data) {
	m_current_box = utils::value_from_vector<uint32_t>(utils::slice<char>(
		data, 0x00, 0x03));

	for (int i = 0; i < 18; i++) {
		m_boxes[i].init_pkm(utils::slice(data, 4 + i * Box4::size, 4 + (i + 1) * Box4::size - 1));
		m_boxes[i].set_name(utils::gen4::data_to_string(utils::slice(data,
			4 + Box4::size * 18 + Box4::name_size * i,
			4 + Box4::size * 18 + Box4::name_size * (i + 1) - 1)));
	}
}

Base_Box& Storage4::get_current_box(void) {
	return static_cast<Base_Box&>(m_boxes[m_current_box]);
}

void Storage4::set_current_box(int idx) {
	m_current_box = idx;
}
