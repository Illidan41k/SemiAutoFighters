#include "Fighter.h"

namespace engine {
	void engine::Fighter::Run()
	{
		SelfTrain();

		while (DistanceToTarget(m_coordinate, m_coordinate) > 1)
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
		const int stepCapacity = 50;
		const int iterations = 100;

		for (int i = 0; i < iterations; i++)
		{
			system("cls");
			for (auto& net : m_actors)
			{

				for (int steps = 0; steps < stepCapacity; steps++)
				{

					//std::cout << "step: " << steps << std::endl;
					move(net->field, net->player, ComputeDirection(net->network, net->field), false);

				}

				net->mark = DistanceToTarget(net->player, net->target);
			}

			std::sort(m_actors.begin(), m_actors.end(), [](const auto& a, const auto& b) {
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

	void engine::Fighter::PutFighterAndTarget(std::shared_ptr<NetStats> stats)
	{
		auto& field = stats->field;
		stats->player = field->TL();
		stats->target = field->BR();

		field->Set(stats->player, 5);
		field->Set(stats->target, 10);
	}

	void engine::Fighter::move(std::shared_ptr<Field> field, Coordinate& coordinate, const Direction& direction, bool verbose)
	{
		field->Set(coordinate, 0);
		coordinate = Move(field, direction, coordinate);
		field->Set(coordinate, 10);

		if (verbose)
		{
			field->Redraw();
			std::cout << "x:" << coordinate.first << " y:" << coordinate.second << std::endl;
		}


	}

	float engine::Fighter::DistanceToTarget(const Coordinate& playerCoordinate, const Coordinate& targetCoordinate)
	{
		auto delta_x = playerCoordinate.first - targetCoordinate.first;
		auto delta_y = playerCoordinate.second - targetCoordinate.second;

		return sqrt(delta_x * delta_x + delta_y * delta_y);
	}
}