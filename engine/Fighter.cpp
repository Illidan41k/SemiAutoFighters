#include "Fighter.h"

void engine::Fighter::Run()
{
	SelfTrain();

	while (DistanceToTarget(m_coordinate) > 1)
	{
		move(m_field, m_coordinate, ComputeDirection(m_network, m_field));

	}
	
}

engine::Direction engine::Fighter::ComputeDirection(std::shared_ptr<Network> net, std::shared_ptr<Field> field)
{
	auto desisions = net->Compute(field);
	auto pos = std::distance(desisions.begin(), std::max_element(desisions.begin(), desisions.end()));
	
	return static_cast <Direction>(pos + 1);
}

void engine::Fighter::SelfTrain()
{
	const int stepCapacity = 15;
	const int iterations = 100;

	for (int i = 0; i < iterations; i++)
	{
		system("cls");
		for (auto& net : m_actors)
		{
			
			for (int steps = 0; steps < stepCapacity; steps++)
			{
				
				//std::cout << "step: " << steps << std::endl;
				move(net->field, net->coordinate, ComputeDirection(net->network, net->field), false);
				
			}

			net->mark = DistanceToTarget(net->coordinate);
		}

		std::sort(m_actors.begin(), m_actors.end(), [](const auto &a, const auto &b) {
			return a->mark < b->mark;
			});

		for (int k = 0; k < 5; k++)
		{
			std::cout << m_actors[k]->mark << std::endl;
			m_actors[k]->field->Redraw();
		}
		std::cout << "---------------------------------" << std::endl;

		system("pause");
	}

}

void engine::Fighter::move(std::shared_ptr<Field> field, Coordinate& coordinate, const Direction& direction, bool verbose)
{
	field->Set(coordinate, 0);
	coordinate = Move(direction, coordinate);
	field->Set(coordinate, 10);

	if (verbose)
	{
		field->Redraw();
		std::cout << "x:" << coordinate.first << " y:" << coordinate.second << std::endl;
		std::cout << "distance:" << DistanceToTarget(coordinate) << std::endl;
	}

	
}

float engine::Fighter::DistanceToTarget(const Coordinate& coordinate)
{
	auto delta_x = coordinate.first - 7;
	auto delta_y = coordinate.second - 9;

	return sqrt(delta_x* delta_x+ delta_y* delta_y);
}
