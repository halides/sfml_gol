#include "gol.h"
#include <random>

GoL::GoL(unsigned int size)
{
	dimension = size;
	grid = new unsigned char[size*size];
	temp_grid = new unsigned char[size*size];
}

GoL::~GoL()
{
	delete[] grid;
	delete[] temp_grid;
}

void GoL::step()
{
	for (unsigned int j = 0; j < dimension; j++) {
		for (unsigned int i = 0; i < dimension; i++) {

			unsigned char neighbor_sum = 0;
			for (char k = -1; k < 2; k++) {
				for (char l = -1; l < 2; l++) {
					if (k==0 && l ==0) continue;
					unsigned int where = i+k+(j*dimension)+(l*dimension);

					if ((j == 0) && (l == -1)) where += dimension*(dimension);
					else if ((j == (dimension-1)) && (l == 1)) where -= dimension*(dimension);

					if (i == 0 && k == -1) where += dimension;
					else if (i == (dimension-1) && k == 1) where -= dimension;

					neighbor_sum += grid[where] & 0x01 ? 1 : 0;	
				}
			}

			if (get_cell_state(i,j) && (neighbor_sum == 2 || neighbor_sum == 3))
				temp_grid[i+j*dimension] |= 0x01;
			else if (!get_cell_state(i,j) && neighbor_sum == 3)
				temp_grid[i+j*dimension] |= 0x01;
			else
				temp_grid[i+j*dimension] &= ~0x01;
		}
	}

	unsigned char* tmp = grid;
	grid = temp_grid;
	temp_grid = tmp;
}

void GoL::clear()
{
	for (int i = 0; i < dimension*dimension; i++)
		grid[i] = 0;
}

void GoL::randomize()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1,10);

	for (int i = 0; i < dimension*dimension; i++)
		grid[i] = (dist(rng) < 3) ? 1 : 0;
}

bool GoL::get_cell_state(unsigned int x, unsigned int y)
{
	return grid[x+y*dimension] & 1;
}

void GoL::flip_cell_state(unsigned int x, unsigned int y)
{
	unsigned char state = grid[x+y*dimension];
	grid[x+y*dimension] = get_cell_state(x,y)? state &= ~0x01 : state |= 0x01;
}
