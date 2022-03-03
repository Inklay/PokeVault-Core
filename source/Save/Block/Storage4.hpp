#ifndef STORAGE4
#define STORAGE4

#include "./Box4.hpp"

class Storage4 {
public:
	void init(std::vector<char> data);
	uint32_t get_current_box(void);

protected:
	uint32_t m_current_box;
	std::array<Box4, 18> m_boxes;
};

#endif // !STORAGE4
