#include <iostream>
#include <windows.h>

#include "Grid.h"

using namespace std;

int main()
{
	vector<Grid> solutions;
	Grid sudoku;
	sudoku.loadSolutions(solutions);
	const int BEEP_LENGTH = 1250;
	
	int choice = -1;
	while(true)
	{
		while (choice < 0 || choice > 4)
		{
			cout << "Number of solutions found thus far: " << solutions.size() << endl << endl;
			cout << "[0] Quit program" << endl;
			cout << "[1] Display solutions found" << endl;
			cout << "[2] Generate solution" << endl;
			cout << "[3] Generate many solutions (infinite)" << endl;
			cout << "[4] Save solutions" << endl;
			cin >> choice;
			system("cls");
			
			if (choice == 0)
			{
				return 0;
			}
			else if (choice == 1)
			{
				sudoku.loadSolutions(solutions);
				for (int i = 0; i < solutions.size(); ++i)
				{
					cout << i + 1 << ")" << endl;
					solutions.at(i).printGrid();
				}
			}
			else if (choice == 2)
			{
				while (sudoku.generateGrid() == false)
				{
					continue;
				}
				sudoku.printGrid();
				sudoku.storeSolution(solutions);
				sudoku.saveSolutions(solutions);
				sudoku.loadSolutions(solutions);
				Beep(523, BEEP_LENGTH);
			}
			else if (choice == 3)
			{
				while (true)
				{
					while (sudoku.generateGrid() == false)
					{
						continue;
					}
					sudoku.printGrid();
					sudoku.storeSolution(solutions);
					sudoku.saveSolutions(solutions);
					sudoku.loadSolutions(solutions);
					Beep(523, BEEP_LENGTH);
				}
			}
			else if (choice == 4)
			{
				sudoku.saveSolutions(solutions);
			}
		}
		choice = -1;
	}
	
	return 0;
}