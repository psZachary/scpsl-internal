#pragma once
#include <math.h>

namespace AimbotHelper {

	int CalculateDistance(float dX0, float dY0, float dX1, float dY1)
	{
		return sqrt((dX1 - dX0) * (dX1 - dX0) + (dY1 - dY0) * (dY1 - dY0));
	}
}