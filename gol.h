#pragma once

class GoL
{
	public:
		GoL(unsigned int);
		~GoL();
		void step();
		void clear();
		void randomize();
		bool get_cell_state(unsigned int, unsigned int);
		void flip_cell_state(unsigned int, unsigned int);

	private:
		int dimension;
		unsigned char* grid;
		unsigned char* temp_grid;
};
