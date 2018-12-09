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
}