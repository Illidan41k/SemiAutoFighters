#pragma once
#include <vector>
#include <iostream>
#include "Utilities.h"
class Field
{
public:
	Field(const int size);
	void Redraw();
	void Set(const engine::Coordinate &coordinate, const int &value);

	std::vector<float> Flatten();
private:
	std::vector<std::vector<float>> m_field{};
};

