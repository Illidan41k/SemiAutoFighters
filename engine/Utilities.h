#pragma once
#include <utility>
#include <iostream>

namespace engine
{

	using  Coordinate = std::pair<int, int>;

	struct Values
	{
		static const int Wall = -3;
		static const int Pass = 0;
		static const int Player = 5;
		static const int Target = 10;
	};

	enum class Direction
	{
		Left = 1,
		Right = 2,
		Top = 3,
		Bottom = 4
	};


}