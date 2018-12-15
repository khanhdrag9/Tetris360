#pragma once
#include "Defines.h"

//direction : Bottom left -> bottom right -> top right -> top left

namespace crd
{
	const int O[][4] = { {MAX_COL / 2, MAX_COL / 2 + 1, MAX_COL / 2, MAX_COL / 2 + 1} , {MAX_ROW, MAX_ROW, MAX_ROW + 1, MAX_ROW + 1} };
	
}

namespace loc
{
	const int O[][4] = { {-1, 0, 0, -1} , {-1, -1, 0, 0} };
	const int I[][4] = { {0, 0, 0, 0} , {-2, -1, 0, 1} };
	const int L[][4] = { {-1, 0, -1, -1} , {-1, -1, 0, 1} };
	const int T[][4] = { {0, 1, 0, -1} , {-1, 0, 0, 0} };
}