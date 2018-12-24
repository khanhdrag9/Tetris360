#pragma once
#include "Defines.h"

//direction : Bottom left -> bottom right -> top right -> top left

namespace crd
{
	const int O[][4] = { {MAX_COL / 2, MAX_COL / 2 + 1, MAX_COL / 2, MAX_COL / 2 + 1} , {MAX_ROW, MAX_ROW, MAX_ROW + 1, MAX_ROW + 1} };
	
}

namespace loc	//col -> row
{
	const int O[][4] = { {0, 1, 1, 0} , {0, 0, 1, 1} };
	const int I[][4] = { {0, 0, 0, 0} , {-1, 0, 1, 2} };
	const int L[][4] = { {0, 1, 0, 0} , {-1, -1, 0, 1} };
	const int T[][4] = { {0, 1, 0, -1} , {-1, 0, 0, 0} };
	const int J[][4] = { {-1, 0, 0, 0} ,{-1, -1, 0, 1} };
	const int S[][4] = { {-1, 0, 0, 1} ,{0, 0, 1, 1} };
	const int Z[][4] = { {0, 1, 0, -1} ,{0, 0, 1, 1} };
}

namespace rot	//row -> col
{
	const int O[][1] = { {0} , {0} };
	const int I[][8] = {
		{-1, 0, 1, 2,  0, 0, 0, 0},
		{0, 0, 0, 0,   -1, 0, 1, 2}
	};
	const int L[][16] = {
		{-1, -1, 0, 1,  0, -1, 0, 0,  1, 1, 0, -1,  0, 1, 0, 0},
		{0, 1, 0, 0,  -1, -1, 0, 1,   0, -1, 0, 0,   1, 1, 0, -1}
	};
	const int T[][16] = {
		{-1, 0, 0, 0,  0, -1, 0, 1,  1, 0, 0, 0,   0, 1, 0, -1},
		{0, 1, 0, -1,  -1, 0, 0, 0,  0, -1, 0, 1,  1, 0, 0, 0}
	};
	const int J[][16] = {
		{ -1, -1, 0, 1,   1, 0, 0, 0,    1, 1, 0, -1,  -1, 0, 0, 0},
		{ -1, 0, 0, 0,    -1, -1, 0, 1,  1, 0, 0, 0,    1, 1, 0, -1}
	};
	const int S[][8] = {
		{0, 0, 1, 1,   1, 0, 0, -1},
		{-1, 0, 0, 1,  0, 0, 1, 1}
	};
	const int Z[][8] = {
		{0, 0, 1, 1,   0, -1, 0, 1},
		{0, 1, 0, -1,  0, 0, 1, 1}
	};
}