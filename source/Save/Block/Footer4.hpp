#ifndef FOOTER4
#define FOOTER4

#include <vector>
#include "../../utils/utils.hpp"

class Footer4{
public:
	void init(std::vector<char> data);
	uint32_t get_storage_id(void);
	uint32_t get_save_count(void);
	uint16_t get_checksum(void);
	uint32_t m_block_size;

private:
	uint32_t m_storage_id;
	uint32_t m_save_count;
	
	uint32_t m_k;
	uint16_t m_t;
	uint16_t m_checksum;
};

#endif // !FOOTER4
