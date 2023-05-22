#include "Sudoku.h"


Sudoku::Sudoku()
{
	srand(time(NULL));
	do
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				sudoku.grid[i][j] = 0;
			}
		}
		for (int i = 0; i < 90; i++)
		{
			std::copy(&sudoku.grid[0][0], &sudoku.grid[0][0] + 81, &sol.grid[0][0]);
			int place = rand() % 81;
			int x = place % 9;
			int y = place / 9;
			int num = rand() % 9 + 1;
			if (check(x, y, num))
				sudoku.grid[y][x] = num;
		}
		SolveRec();

	} while (!solvable());
	std::copy(&sudoku.grid[0][0], &sudoku.grid[0][0] + 81, &sol.grid[0][0]);
}

void Sudoku::SolveRec()
{
	if (sol.grid[0][0] != 0) {
		Rec(1, 0);
	}
	else {
		for (int i = 1; i < 10; i++)
		{
			sol.grid[0][0] = 0;
			if (check(0, 0, i)) {
				sol.grid[0][0] = i;
				if (!Rec(1, 0))
					continue;
				else {
					break;
				}
			}
		}
	}
}

void Sudoku::show()
{
	for (int i = 0; i < 13; i++)
	{
		if (i % 4 == 0) {
			std::cout << "+-------+-------+-------+\n";
			continue;
		}
		for (int j = 0; j < 13; j++)
		{
			if (j % 4 == 0) {
				std::cout << "|";
			}
			else {
				if (sudoku.grid[i - i / 4 - 1][j - j / 4 - 1] == 0) {
					std::cout << ".";
				}
				else
				{
					std::cout << sudoku.grid[i - i / 4 - 1][j - j / 4 - 1];
				}
			}
			std::cout << " ";
		}
		std::cout << std::endl;

	}
}

void Sudoku::showgrid()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << sudoku.grid[i][j];
			std::cout << " ";
		}
		std::cout << "\n";

	}
	std::cout << std::endl;
}

void Sudoku::showsol()
{
	for (int i = 0; i < 13; i++)
	{
		if (i % 4 == 0) {
			std::cout << "+-------+-------+-------+\n";
			continue;
		}
		for (int j = 0; j < 13; j++)
		{
			if (j % 4 == 0) {
				std::cout << "|";
			}
			else {
				if (sol.grid[i - i / 4 - 1][j - j / 4 - 1] == 0) {
					std::cout << ".";
				}
				else
				{
					std::cout << sol.grid[i - i / 4 - 1][j - j / 4 - 1];
				}
			}
			std::cout << " ";
		}
		std::cout << "\n";

	}
}

void Sudoku::Solve(Move ruch)
{
	if (check(ruch.x - 1, ruch.y - 1, ruch.num))
	{
		sol.grid[ruch.y-1][ruch.x-1] = ruch.num;
	}
	else
		std::cout << "Wrong! Cannot be placed"<<std::endl;
}

bool Sudoku::solvable()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sol.grid[i][j] == 0)
				return false;
		}
	}
	return true;
}

void Sudoku::reset()
{
	std::copy(&sudoku.grid[0][0], &sudoku.grid[0][0] + 81, &sol.grid[0][0]);
}

bool Sudoku::Rec(int x, int y)
{
	//this->showsol();
	if (x == 8 && y == 8) {
		if (sol.grid[y][x] != 0)
			return true;
		for (int i = 1; i < 10; i++)
		{
			sol.grid[y][x] = 0;
			if (check(x, y, i)) {
				sol.grid[y][x] = i;
				return true;
			}
		}
		return false;
	}
	if (sol.grid[y][x] != 0) {

		if (x == 8 && y != 8) {
			if (Rec(0, y + 1))
				return true;
		}
		else {
			if (Rec(x+1, y))
				return true;
		}
		return false;
		
	}
	for (int i = 1; i < 10; i++)
	{
		sol.grid[y][x] = 0;
		if (check(x, y, i)) {
			sol.grid[y][x] = i;
			if (x == 8 && y != 8) {
				if (!Rec(0, y + 1))
					continue;
				else {
					return true;
				}
			}
			else {
				if (!Rec(x+1, y))
					continue;
				else {
					return true;
				}
			}
		}
	}
	return false;
}

bool Sudoku::check(int x, int y, int num)
{
	if (sol.grid[y][x] != 0)
		return false;
	int l = x / 3 + 1;
	int m = y / 3 + 1;
	switch (l*m)
	{
	case 1:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i == x && j == y)
					continue;
				if (sol.grid[j][i] == num)
					return false;
			}

		}
		break;
	case 2:
		if (l > m) {
			for (int i = 3; i < 6; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (i == x && j == y)
						continue;
					if (sol.grid[j][i] == num)
						return false;
				}
			}
		}
		else {
			for (int i = 0; i < 3; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					if (i == x && j == y)
						continue;
					if (sol.grid[j][i] == num)
						return false;
				}
			}
		}
		break;
	case 3:
		if (l > m) {
			for (int i = 6; i < 9; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (i == x && j == y)
						continue;
					if (sol.grid[j][i] == num)
						return false;
				}
			}
		}
		else {
			for (int i = 0; i < 3; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					if (i == x && j == y)
						continue;
					if (sol.grid[j][i] == num)
						return false;
				}
			}
		}
		break;
	case 4:
		for (int i = 3; i < 6; i++)
		{
			for (int j = 3; j < 6; j++)
			{
				if (i == x && j == y)
					continue;
				if (sol.grid[j][i] == num)
					return false;
			}

		}
		break;
	case 6:
		if (l > m) {
			for (int i = 6; i < 9; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					if (i == x && j == y)
						continue;
					if (sol.grid[j][i] == num)
						return false;
				}
			}
		}
		else {
			for (int i = 3; i < 6; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					if (i == x && j == y)
						continue;
					if (sol.grid[j][i] == num)
						return false;
				}
			}
		}
		break;
	case 9:
		for (int i = 6; i < 9; i++)
		{
			for (int j = 6; j < 9; j++)
			{
				if (i == x && j == y)
					continue;
				if (sol.grid[j][i] == num)
					return false;
			}

		}
		break;
	default:
		break;
	}
	for (int i = 0; i < 9; i++)
	{
		if (sol.grid[y][i] == num)
			return false;
		if (sol.grid[i][x] == num)
			return false;
	}
	return true;
}
