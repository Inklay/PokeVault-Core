#ifndef STORAGE4_HPP
#define STORAGE4_HPP

#include "../Box/Box4.hpp"

class Storage4 {
public:
	void init(std::vector<char> data);
	Base_Box& get_current_box(void);
	Base_Box& get_box(int idx);

protected:
	uint32_t m_current_box;
	std::array<Box4, 18> m_boxes;
};

#endif // !STORAGE4_HPP
