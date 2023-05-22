// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Sudoku.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>

int gameFlow() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;

	Sudoku sudoku;
	std::cout << std::endl;
	sudoku.showsol();
	while (!sudoku.solvable()) {
		std::cout << std::endl;
		std::cout << "----------------------------------------------------------------------------" << std::endl;
		std::cout << "1 - input number, 2 - reset sudoku, 3 - new sudoku" << std::endl;
		int input;
		if (!(std::cin >> input))
			continue;
		switch (input)
		{
		case 1:
			std::cout << "Enter x y num" << std::endl;
			int x, y, num;
			std::cin >> x >> y >> num;
			system("CLS");
			sudoku.Solve({ x, y, num });
			break;
		case 2:
			sudoku.reset();
			system("CLS");
			break;
		case 3:
			sudoku = Sudoku();
			system("CLS");
			break;
		default:
			system("CLS");
			std::cout << "WRONG INPUT" << std::endl;
			break;
		}
		std::cout << std::endl;
		DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
		sudoku.showsol();
		//std::cout << virtualMemUsed << std::endl;
		//sudoku.show();
	}
	std::cout << "CONGRATULATIONS!" << std::endl;
	return 0;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	sf::Font font;
	if (!font.loadFromFile("C:\windows\font\arial.ttf"))
		return EXIT_FAILURE;
	sf::Text text("Hello SFML", font, 50);

	gameFlow();
	return 0;
}

