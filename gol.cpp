#include "gol.h"
#include <random>

GoL::GoL(unsigned int size)
{
	dimension = size;
	std::vector<std::vector<bool>> grid(size,std::vector<bool>(size));
	std::vector<std::vector<bool>> temp_grid(size,std::vector<bool>(size));
}

void GoL::step()
{
	//update temp_grid from grid
	for (unsigned int j = 0; j < dimension; j++) {
		for (unsigned int i = 0; i < dimension; i++) {

			//sort of ugly with a "four deep for" but it really isn't "four deep": we just want to point to all the 8 squares around and count the neighbors
			unsigned char neighbor_sum = 0;
			for (char k = -1; k < 2; k++) { 
				for (char l = -1; l < 2; l++) {
					if (k==0 && l ==0) continue;

					//to which cell are we referring to?
					unsigned int x_where = i+k;
					unsigned int y_where = (j*dimension)+(l*dimension);

					//these two ifelseifs handle wrapping
					if ((j == 0) && (l == -1)) y_where += dimension;
					else if ((j == (dimension-1)) && (l == 1)) y_where -= dimension;

					if (i == 0 && k == -1) x_where += dimension;
					else if (i == (dimension-1) && k == 1) x_where -= dimension;

					neighbor_sum += grid[x_where][y_where] & 0x01 ? 1 : 0;	
				}
			}

			//are we dead or alive?
			if (get_cell_state(i,j) && (neighbor_sum == 2 || neighbor_sum == 3))
				temp_grid[i][j] = true;
			else if (!get_cell_state(i,j) && neighbor_sum == 3)
				temp_grid[i][j] = true;
			else
				temp_grid[i][j] = false;
		}
	}

	//just swap the pointers to grid and temp_grid, no copying
	std::vector<std::vector<bool>> tmp = grid;
	grid = temp_grid;
	temp_grid = tmp;
}

void GoL::clear()
{
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			grid[i][j] = 0;
}

void GoL::randomize()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1,10);

	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			grid[i][j] = (dist(rng) < 3) ? 1 : 0;
}

bool GoL::get_cell_state(unsigned int x, unsigned int y)
{
	return grid[x][y];
}

void GoL::flip_cell_state(unsigned int x, unsigned int y)
{
	unsigned char state = grid[x][y];
	grid[x][y] = get_cell_state(x,y)? state &= ~0x01 : state |= 0x01;
}
