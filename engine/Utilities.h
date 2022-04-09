#pragma once
#include <utility>
#include <iostream>
namespace engine
{
	using  Coordinate = std::pair<int, int>;

	enum class Direction
	{
		Left = 1,
		Right = 2,
		Top = 3,
		Bottom = 4
	};

	static inline Coordinate Move(const Direction& direction, const Coordinate oldCoordinate, const int maxCoordinate = 10)
	{
		auto newCoordinate = std::make_pair(oldCoordinate.first, oldCoordinate.second);
		switch (direction)
		{
			
		case Direction::Left:
			if (newCoordinate.first > 0)
			{
				newCoordinate.first--;
				break;
			}
		case Direction::Right:
			if (newCoordinate.first < maxCoordinate-1)
			{
				newCoordinate.first++;
				break;
			}
		case Direction::Top:
			if (newCoordinate.second > 0)
			{
				newCoordinate.second--;
				break;
			}
		case Direction::Bottom:
			if (newCoordinate.second < maxCoordinate - 1)
			{
				newCoordinate.second++;
				break;
			}
		default:
			std::cout << "wrong direction" << std::endl;
			break;
		}
		return newCoordinate;
	}

}