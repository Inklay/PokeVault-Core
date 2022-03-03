#include "./Footer4.hpp"

void Footer4::init(std::vector<char> data) {
	m_storage_id = utils::value_from_vector<uint32_t>(utils::slice<char>(
		data, 0x00, 0x03));
	m_save_count = utils::value_from_vector<uint32_t>(utils::slice<char>(
		data, 0x04, 0x07));
	m_block_size = utils::value_from_vector<uint32_t>(utils::slice<char>(
		data, 0x08, 0x0B));
	m_k = utils::value_from_vector<uint32_t>(utils::slice<char>(
		data, 0x0C, 0x0F));
	m_t = utils::value_from_vector<uint16_t>(utils::slice<char>(
		data, 0x10, 0x11));
	m_checksum = utils::value_from_vector<uint16_t>(utils::slice<char>(
		data, 0x12, 0x13));
}

uint32_t Footer4::get_save_count(void) {
	return m_save_count;
}

uint32_t Footer4::get_storage_id(void) {
	return m_storage_id;
}

uint16_t Footer4::get_checksum(void) {
	return m_checksum;
}
