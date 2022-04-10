#include "Field.h"

namespace engine
{
	Field::Field(const int size, int initRand)
	{
		std::srand(initRand);

		for (int i = 0; i < size; i++)
		{
			m_field.emplace_back(std::vector<float>(size, 0));
		}

		mazemake(m_field, size, size, 2, 3, 3);
		/// //////////////

	}

	void Field::Redraw()
	{

		for (int i = 0; i < m_field.size(); i++)
		{
			auto& line = m_field[i];

			for (int j = 0; j < line.size(); j++)
			{
				std::cout << abs(line[j]) << " ";
			}

			std::cout << std::endl;

		}
	}

	void Field::Set(const engine::Coordinate& coordinate, const int& value)
	{
		m_field[coordinate.second][coordinate.first] = value;
	}

	engine::Coordinate Field::TL()
	{
		for (int i = 0; i < m_field.size(); i++)
		{
			for (int j = 0; j < m_field.size(); j++)
			{
				if (m_field[i][j] == engine::Values::Pass)
				{
					return std::make_pair(i, j);
				}
			}
		}

		return std::make_pair(-1, -1);
	}

	engine::Coordinate Field::BR()
	{
		for (int i = m_field.size() - 1; i > 0; i--)
		{
			for (int j = m_field.size() - 1; j > 0; j--)
			{
				if (m_field[i][j] == engine::Values::Pass)
				{
					return std::make_pair(i, j);
				}
			}
		}

		return std::make_pair(-1, -1);
	}

	void Field::mazemake(std::vector<std::vector<float>>& field, int height, int width, int k, int rheight, int rwidth)
	{

		int x, y, c, a;
		bool b, swap = true;
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				field[i][j] = engine::Values::Wall;

		rheight--; rwidth--; // Исключительно для удобства
		/*
		for (int l = 0; l < k; l++) {  // Генерация комнат
			b = 1;
			while (b) {
				do { // Точка-центр комнаты
					if (rwidth % 4 == 0) // Комнаты, с разной делимостью на 4 ведут себя
						x = 2 * (rand() % (width / 2)) + 1; // по разному, унифицируем
					else
						x = 2 * (rand() % (width / 2)) + 2;
					if (rheight % 4 == 0)
						y = 2 * (rand() % (height / 2)) + 1;
					else
						y = 2 * (rand() % (height / 2)) + 2;
				} while (x < (rwidth + 2) || x >(width - rwidth - 2) ||
					y < (rheight + 2) || y >(height - rheight - 2));

				b = 0; // Комнаты не должны прикасаться
				for (int i = (y - rheight - 2); i < (y + rheight + 2); i++)
					for (int j = (x - rwidth - 2); j < (x + rwidth + 2); j++)
						if (field[i][j] == m_room)
							b = 1;

				if (b)
					continue;

				for (int i = (y - rheight / 2); i < (y + rheight / 2 + 1); i++) // Раскопки комнаты
					for (int j = (x - rwidth / 2); j < (x + rwidth / 2 + 1); j++)
						field[i][j] = m_room;

				c = rand() % 4; // Дверь в комнату, определяем в какую стену
				// Нижняя, верхняя, правая и левая соответственно
							// Нагромождение в виде rand()... нужно для того, чтобы дверь стояла в разных
							// местах стены
				if (c == 0) m_field[y + rheight / 2 + 1][x - rwidth / 2 + 2 * (rand() % (rwidth / 2 + 1))] = m_room;
				if (c == 1) m_field[y - rheight / 2 - 1][x - rwidth / 2 + 2 * (rand() % (rwidth / 2 + 1))] = m_room;
				if (c == 2) m_field[y - rheight / 2 + 2 * (rand() % (rheight / 2 + 1))][x + rwidth / 2 + 1] = m_room;
				if (c == 3) m_field[y - rheight / 2 + 2 * (rand() % (rheight / 2 + 1))][x - rwidth / 2 - 1] = m_room;
				// swap отвечает за возможность поворачивать комнату на 90°
				if (swap) {
					rheight += rwidth;
					rwidth = rheight - rwidth;
					rheight -= rwidth;
				} // Вот так настоящие мужики меняют переменные значениями
			}
		}
		*/

		for (int i = 0; i < height; i++) // Массив заполняется землей-ноликами
			for (int j = 0; j < width; j++)
				field[i][j] = engine::Values::Wall;

		x = 3; y = 3; a = 0; // Точка приземления крота и счетчик
		while (a < 10000) { // Да, простите, костыль, иначе есть как, но лень
			field[y][x] = engine::Values::Pass; a++;
			while (1) { // Бесконечный цикл, который прерывается только тупиком
				c = rand() % 4; // Напоминаю, что крот прорывает
				switch (c) {  // по две клетки в одном направлении за прыжок
				case 0: if (y != 1)
					if (field[y - 2][x] == engine::Values::Wall) { // Вверх
						field[y - 1][x] = engine::Values::Pass;
						field[y - 2][x] = engine::Values::Pass;
						y -= 2;
					}
				case 1: if (y != height - 2)
					if (field[y + 2][x] == engine::Values::Wall) { // Вниз
						field[y + 1][x] = engine::Values::Pass;
						field[y + 2][x] = engine::Values::Pass;
						y += 2;
					}
				case 2: if (x != 1)
					if (field[y][x - 2] == engine::Values::Wall) { // Налево
						field[y][x - 1] = engine::Values::Pass;
						field[y][x - 2] = engine::Values::Pass;
						x -= 2;
					}
				case 3: if (x != width - 2)
					if (field[y][x + 2] == engine::Values::Wall) { // Направо
						field[y][x + 1] = engine::Values::Pass;
						field[y][x + 2] = engine::Values::Pass;
						x += 2;
					}
				}
				if (deadend(x, y, field, height, width))
					break;
			}

			if (deadend(x, y, field, height, width)) // Вытаскиваем крота из тупика
				do {
					x = 2 * (rand() % ((width - 1) / 2)) + 1;
					y = 2 * (rand() % ((height - 1) / 2)) + 1;
				} while (field[y][x] != engine::Values::Pass);
		}
	}

	bool Field::deadend(int x, int y, std::vector<std::vector<float>> field, int height, int width)
	{
		{
			int a = 0;

			if (x != 1) {
				if (field[y][x - 2] == Values::Pass)
					a += 1;
			}
			else a += 1;

			if (y != 1) {
				if (field[y - 2][x] == Values::Pass)
					a += 1;
			}
			else a += 1;

			if (x != width - 2) {
				if (field[y][x + 2] == Values::Pass)
					a += 1;
			}
			else a += 1;

			if (y != height - 2) {
				if (field[y + 2][x] == Values::Pass)
					a += 1;
			}
			else a += 1;

			if (a == 4)
				return 1;
			else
				return 0;
		}
	}

	std::vector<float> Field::Flatten()
	{
		std::vector<float> flattened;

		for (const auto& v : m_field) {
			std::copy(v.begin(), v.end(), std::back_inserter(flattened));
		}

		return flattened;
	}

	float Field::At(const engine::Coordinate& coordinate)
	{
		return m_field[coordinate.first][coordinate.second];
	}
}