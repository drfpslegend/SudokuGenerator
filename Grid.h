#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>

class Grid
{
	private:
		int grid[9][9];
		std::vector<int> adjustValidNumbers(std::vector<int>, std::vector<int>, std::vector<int>);
		int findValidNumber(std::vector<int>);
		void restrictValidNumbers(std::vector<int> &, int);
	public:
		Grid();
		~Grid();
		void initializeGrid();
		bool generateGrid();
		void printGrid();
		void saveSolution();
		void loadSolutions();
};

Grid::Grid()
{
	initializeGrid();
}

Grid::~Grid()
{
	
}

void Grid::initializeGrid()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			grid[i][j] = 0; // sets all grid locations to 0
		}
	}
}

void Grid::restrictValidNumbers(std::vector<int> &v, int badValue)
{
	int index; // will hold index of number to delete
	
	for (int i = 0; i < v.size(); ++i) // checks to see where the number is in the vector
	{
		if (v.at(i) == badValue)
		{
			index = i; // if numbers are equal, assigns correct index and breaks the for loop
			break;
		}
	}
	
	for (int i = index; i < v.size() - 1; ++i)
	{
		v.at(i) = v.at(i + 1); // assigns all next values to previous ones
	}
	
	v.pop_back(); // deletes last value from vector
}

std::vector<int> Grid::adjustValidNumbers(std::vector<int> row, std::vector<int> column, std::vector<int> square)
{
	// returns all numbers that are common to the row, column, and square.
	
	std::vector<int> validNumbers;
	
	for (int i = 1; i <= 9; ++i) // iterates through all possible values
	{
		bool commonToAll = false;
		
		for (int j = 0; j < row.size(); ++j) // iterates through row
		{
			if (row.at(j) == i)
			{
				for (int k = 0; k < column.size(); ++k) // iterates through column
				{
					if (column.at(k) == i)
					{
						for (int m = 0; m < square.size(); ++m) // iterates through square
						{
							if (square.at(m) == i)
							{
								commonToAll = true;
								break;
							}
						}
						break;
					}
				}
				break;
			}
		}
		
		if (commonToAll) //  if the number is valid for the row, column, and square, put it in validNumbers
		{
			validNumbers.push_back(i);
		}
	}
	
	return validNumbers;
}

int Grid::findValidNumber(std::vector<int> validNumbers)
{
	std::srand(std::time(0)); // seeds random number generator for new grid each time
	int index = rand() % validNumbers.size(); // chooses random index of validNumbers vector
	
	return validNumbers.at(index); // returns value at chosen index
}

bool Grid::generateGrid()
{
	std::vector< std::vector<int> > rows {	{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
											{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
											{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
											{1, 2, 3, 4, 5, 6, 7, 8, 9}, // holds current valid numbers for each row
											{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
											{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
											{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
											{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
											{1, 2, 3, 4, 5, 6, 7, 8, 9}	};
	
	std::vector< std::vector<int> > columns {	{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, // holds current valid numbers for each column
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}	};

	initializeGrid();
	for (int i = 0; i < 3; ++i) // rows of 3x3 squares
	{	
		for (int j = 0; j < 3; ++j) // columns of 3x3 squares
		{
			std::vector<int> square {1, 2, 3, 4, 5, 6, 7, 8, 9}; // holds current valid numbers for current 3x3 square
			
			for (int k = 0; k < 9; ++k) // each box in a 3x3 square
			{
				int rowIndex = 3*i + k/3; // calculates current row index based on for loop indices
				int columnIndex = 3*j + k%3; // calculates currenc column index based on for loop indices
				
				std::vector<int> adjustedNumbers = adjustValidNumbers(rows.at(rowIndex), columns.at(columnIndex), square); // generates an adjusted vector to hold the valid numbers for current grid box
				
				if (adjustedNumbers.size() == 0)
				{
					return false;
				}
				
				int newNumber = findValidNumber(adjustedNumbers); // picks new number from list of adjusted numbers
				
				grid[rowIndex][columnIndex] = newNumber; // assigns the new number to correct grid box
				
				restrictValidNumbers(rows.at(rowIndex), newNumber); // updates the valid numbers for current row
				restrictValidNumbers(columns.at(columnIndex), newNumber); // updates the valid numbers for current column
				restrictValidNumbers(square, newNumber); // updates the valid numbers for current square
				
				//system("cls");
				//printGrid();
			}
		}
	}
	
	return true;
}

void Grid::printGrid()
{
	std::cout << "===================================\n";
	
	for (int i = 0; i < 9; ++i)
	{
		std::cout << "||";
		
		for (int j = 0; j < 9; ++j)
		{
			std::cout << " " << grid[i][j] << " ";
			if ((j + 1) % 3 == 0)
			{
				std::cout << "||";
			}
		}
		
		std::cout << std::endl;
		
		if ((i + 1) % 3 == 0)
		{
			std::cout << "===================================\n";
		}
	}
	
	std::cout << std::endl;
}

void Grid::saveSolution()
{
	std::fstream file("solutions.bin", std::ios::binary | std::ios::out | std::ios:: app);
	file.write(reinterpret_cast<char*>(&(*this)), sizeof(*this));
	file.close();
}

void Grid::loadSolutions()
{
	std::fstream file("solutions.bin", std::ios::binary | std::ios::in);
	int n = 1;
	
	while (true)
	{
		file.read(reinterpret_cast<char*>(&(*this)), sizeof(*this));
		if (file.eof())
		{
			file.close();
			break;
		}
		else
		{
			std::cout << n << ")" << std::endl;
			++n;
			printGrid();
		}
	}
}

#endif
