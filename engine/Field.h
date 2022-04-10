#pragma once
#include <vector>
#include <iostream>
#include "Utilities.h"

namespace engine
{
	class Field
	{
	public:
		Field(const int size, int initRand);
		void Redraw();
		void Set(const engine::Coordinate& coordinate, const int& value);
		engine::Coordinate TL();
		engine::Coordinate BR();
		std::vector<float> Flatten();
		float At(const engine::Coordinate& coordinate);

	private:
		void mazemake(std::vector<std::vector<float>>& field, int height, int width, int k, int rheight, int rwidth);

		bool deadend(int x, int y, std::vector<std::vector<float>> field, int height, int width);

		std::vector<std::vector<float>> m_field{};

	};

}