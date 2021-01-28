#pragma once
#include <vector>

class GoL
{
	public:
		GoL(unsigned int);
		void step();
		void clear();
		void randomize();
		bool get_cell_state(unsigned int, unsigned int);
		void flip_cell_state(unsigned int, unsigned int);

	private:
		int dimension;
		std::vector<std::vector<bool>> grid;
		std::vector<std::vector<bool>> temp_grid;
};
