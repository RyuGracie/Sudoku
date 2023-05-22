#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

#pragma once
class Sudoku
{
public:
	struct Grid {
		int grid[9][9];
	};
	struct Move
	{
		int x, y, num;
	};
	Sudoku();
	void show();
	void showsol();
	void Solve(Move);
	bool solvable();
	void reset();
private:
	Grid sudoku;
	Grid sol;
	Move memor[3];
	void showgrid();
	void SolveRec();
	bool Rec(int x = 0, int y = 0);
	bool check(int x, int y, int num);

};
