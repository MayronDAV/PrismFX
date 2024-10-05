#pragma once

// std
#include <cstdint>

// From glfw3.h


namespace PFX
{
	using MouseCode = uint8_t;

	namespace Mouse
	{
		enum : MouseCode
		{
			B1 = 0,
			B2 = 1,
			B3 = 2,
			B4 = 3,
			B5 = 4,
			B6 = 5,
			B7 = 6,
			B8 = 7,
			BLast = B8,
			BLeft = B1,
			BRight = B2,
			BMiddle = B3
		};
	}
}