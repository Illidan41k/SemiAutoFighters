#pragma once
#include <utility>
#include "Field.h"
#include "Utilities.h"
#include "Network.h"

namespace engine
{
	class Fighter
	{
	public:

		struct NetStats
		{
			NetStats(std::shared_ptr<Network> net)
			{
				network = net;
				field = std::make_shared<Field>(10);
			}

			std::shared_ptr<Network> network;
			float mark;
			Coordinate coordinate{std::make_pair(3,3)};
			std::shared_ptr<Field> field;
		};

		Fighter(std::shared_ptr<Field> field, Coordinate coordinate):
			m_field(field), 
			m_coordinate(coordinate),
			m_network(std::make_shared<Network>(100))

		{
			int initRand = static_cast <unsigned> (time(0));
			m_network->Dense(100, initRand);
			m_network->Dense(4, initRand);
			move(m_field, m_coordinate, Direction::Top);

			for (int i = 0; i < 200; i++)
			{
				auto network = std::make_shared<Network>(100);
				network->Dense(100, initRand+i+5);
				network->Dense(4, initRand + i + 1000);
				auto netStats = std::make_shared<NetStats>(network);
				move(netStats->field, netStats->coordinate, Direction::Top);
				m_actors.push_back(netStats);
			}

			
		}
		
		void Run();
		Direction ComputeDirection(std::shared_ptr<Network> net, std::shared_ptr<Field> field);

	private:
		void SelfTrain();

		void move(std::shared_ptr<Field> field, Coordinate &coordinate, const Direction & direction, bool verbose = false);
		float DistanceToTarget(const Coordinate & coordinate);
		Coordinate m_coordinate;
		int m_maxCoordinate = 10;
		std::shared_ptr<Field> m_field;
		std::shared_ptr<Network> m_network;

		std::vector<std::shared_ptr<NetStats>> m_actors{};
		//std::vector
	};
}
