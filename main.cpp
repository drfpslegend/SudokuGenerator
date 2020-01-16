#include <iostream>
#include <windows.h>

#include "Grid.h"

int main()
{
	Grid sudoku;
	const int BEEP_LENGTH = 1250;
	
	int choice = 1;
	while(true)
	{
		std::cout << "Quit program [0]" << std::endl;
		std::cout << "Display solutions found [1]" << std::endl;
		std::cout << "Generate solution [2]" << std::endl;
		std::cout << "Generate many solutions (infinite) [3]" << std::endl;
		
		std::cin >> choice;
		system("cls");
		
		if (choice == 0)
		{
			break;
		}
		else if (choice == 1)
		{
			sudoku.loadSolutions();
			Beep(523, BEEP_LENGTH);
		}
		else if (choice == 2)
		{
			while (sudoku.generateGrid() == false)
			{
				
			}
			sudoku.saveSolution();
			sudoku.printGrid();
			Beep(523, BEEP_LENGTH);
		}
		else if (choice == 3)
		{
			while (true)
			{
				while (sudoku.generateGrid() == false)
				{
					
				}
				sudoku.saveSolution();
				sudoku.printGrid();
				Beep(523, BEEP_LENGTH);
			}
		}
		else
		{
			std::cout << "Invalid option.  Enter 0, 1, or 2: ";
			std::cin >> choice;
		}
	}
	
	return 0;
}
