#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

class Grid
{
	private:
		int grid[9][9];
		vector<int> adjustValidNumbers(vector<int>, vector<int>, vector<int>); // generates an adjusted vector to hold the valid numbers for current grid box
		int pickValidNumber(vector<int>); // picks a new number from the list of adjusted numbers
		void restrictValidNumbers(vector<int> &, int); // removes the number from the current row, column, or square
	public:
		Grid();
		~Grid();
		void initializeGrid(); // sets all grid locations to 0
		bool generateGrid(); // attemps to find a valid solution
		void printGrid(); // displays the current grid
		void storeSolution(vector<Grid> &); // stores this Grid object in a vector of Grid objects
		void saveSolutions(const vector<Grid> &); // saves all Grid objects in the argument vector to a file of Grid objects
		void loadSolutions(vector<Grid> &); // loads all Grid objects from a file of Grid objects into the argument vector
};

vector<int> Grid::adjustValidNumbers(vector<int> row, vector<int> column, vector<int> square)
{
	// returns all numbers that are common to the row, column, and square.
	
	vector<int> validNumbers;
	
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

int Grid::pickValidNumber(vector<int> validNumbers)
{
	srand(time(0)); // seeds random number generator for new grid each time
	int index = rand() % validNumbers.size(); // chooses random index of validNumbers vector
	
	return validNumbers.at(index); // returns value at chosen index
}

void Grid::restrictValidNumbers(vector<int> &v, int badValue)
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


bool Grid::generateGrid()
{
	initializeGrid();
	vector< vector<int> > rows {	{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, // holds current valid numbers for each row
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
												{1, 2, 3, 4, 5, 6, 7, 8, 9}	};
	
	vector< vector<int> > columns {	{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
													{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
													{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
													{1, 2, 3, 4, 5, 6, 7, 8, 9}, // holds current valid numbers for each column
													{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
													{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
													{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
													{1, 2, 3, 4, 5, 6, 7, 8, 9}, 
													{1, 2, 3, 4, 5, 6, 7, 8, 9}	};
												
	for (int i = 0; i < 3; ++i) // rows of 3x3 squares
	{	
		for (int j = 0; j < 3; ++j) // columns of 3x3 squares
		{
			vector<int> square {1, 2, 3, 4, 5, 6, 7, 8, 9}; // holds current valid numbers for current 3x3 square
			
			for (int k = 0; k < 9; ++k) // each box in a 3x3 square
			{
				int rowIndex = 3*i + k/3; // calculates current row index based on for loop indices
				int columnIndex = 3*j + k%3; // calculates currenc column index based on for loop indices
				
				vector<int> adjustedNumbers = adjustValidNumbers(rows.at(rowIndex), columns.at(columnIndex), square); // generates an adjusted vector to hold the valid numbers for current grid box
				
				if (adjustedNumbers.size() == 0) // no new numbers possible
				{
					return false;
				}
				
				int newNumber = pickValidNumber(adjustedNumbers); // picks new number from list of adjusted numbers
				
				grid[rowIndex][columnIndex] = newNumber; // assigns the new number to correct grid box
				
				restrictValidNumbers(rows.at(rowIndex), newNumber); // updates the valid numbers for current row
				restrictValidNumbers(columns.at(columnIndex), newNumber); // updates the valid numbers for current column
				restrictValidNumbers(square, newNumber); // updates the valid numbers for current square
			}
		}
	}
	
	return true;
}

void Grid::printGrid()
{
	cout << "===================================\n";
	
	for (int i = 0; i < 9; ++i)
	{
		cout << "||";
		
		for (int j = 0; j < 9; ++j)
		{
			cout << " " << grid[i][j] << " ";
			if ((j + 1) % 3 == 0)
			{
				cout << "||";
			}
		}
		
		cout << endl;
		
		if ((i + 1) % 3 == 0)
		{
			cout << "===================================\n";
		}
	}
	
	cout << endl;
}

void Grid::storeSolution(vector<Grid> &solutions)
{
	for (int i = 0; i < solutions.size(); ++i)
	{
		if (this->grid == solutions.at(i).grid)
		{
			return;
		}
	}
	solutions.push_back(*this);
}

void Grid::saveSolutions(const vector<Grid> &solutions)
{
	fstream file("solutions.bin", ios::binary | ios::out);
	if (file.is_open() == false)
	{
		cout << "Error opening file to write." << endl;
		return;
	}
	for (int i = 0; i < solutions.size(); ++i)
	{
		*this = solutions.at(i);
		file.write(reinterpret_cast<char*>(&(*this)), sizeof(*this));
	}
	file.close();
}

void Grid::loadSolutions(vector<Grid> &solutions)
{
	solutions.resize(0);
	fstream file("solutions.bin", ios::binary | ios::in);
	if (file.is_open() == false)
	{
		cout << "Error opening file to read." << endl;
		return;
	}
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
			solutions.push_back(*this);
		}
	}
}

#endif