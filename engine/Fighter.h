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
			NetStats(std::shared_ptr<Network> net, int size, int initRand)
			{
				network = net;
				field = std::make_shared<Field>(size, initRand);
			}

			std::shared_ptr<Network> network;
			float mark;
			Coordinate target{};
			Coordinate player{};
			std::shared_ptr<Field> field{};
		};

		Fighter(std::shared_ptr<Field> field, Coordinate coordinate, int size):
			m_field(field), 
			m_coordinate(coordinate),
			m_network(std::make_shared<Network>(100))

		{
			int initRand = static_cast <unsigned> (time(0));
			m_network->Dense(100, initRand);
			m_network->Dense(4, initRand);
			move(m_field, m_coordinate, Direction::Top);

			for (int i = 0; i < 40; i++)
			{
				auto network = std::make_shared<Network>(size* size);
				network->Dense(size* size, initRand+i+1);
				network->Dense(4, initRand + i + 1000);
				auto netStats = std::make_shared<NetStats>(network, size, initRand+i+325);
				PutFighterAndTarget(netStats);
				move(netStats->field, netStats->player, Direction::Top);
				
				m_actors.push_back(netStats);
			}

			
		}
		
		void Run();
		Direction ComputeDirection(std::shared_ptr<Network> net, std::shared_ptr<Field> field);

	private:
		static inline Coordinate Move(std::shared_ptr<Field> field, const Direction& direction, const Coordinate oldCoordinate)
		{
			auto newCoordinate = std::make_pair(oldCoordinate.first, oldCoordinate.second);
			switch (direction)
			{

			case Direction::Left:
				if (field->At(std::make_pair(newCoordinate.first-1, newCoordinate.second)) == Values::Pass)
				{
					newCoordinate.first--;
					break;
				}
			case Direction::Right:
				if (field->At(std::make_pair(newCoordinate.first + 1, newCoordinate.second)) == Values::Pass)
				{
					newCoordinate.first++;
					break;
				}
			case Direction::Top:
				if (field->At(std::make_pair(newCoordinate.first, newCoordinate.second-1)) == Values::Pass)
				{
					newCoordinate.second--;
					break;
				}
			case Direction::Bottom:
				if (field->At(std::make_pair(newCoordinate.first, newCoordinate.second + 1)) == Values::Pass)
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

		void SelfTrain();
		void PutFighterAndTarget(std::shared_ptr<NetStats> stats);
		void move(std::shared_ptr<Field> field, Coordinate &coordinate, const Direction & direction, bool verbose = false);
		float DistanceToTarget(const Coordinate & playerCoordinate, const Coordinate& targetCoordinate);
		Coordinate m_coordinate;
		int m_maxCoordinate = 10;
		std::shared_ptr<Field> m_field;
		std::shared_ptr<Network> m_network;

		std::vector<std::shared_ptr<NetStats>> m_actors{};
		//std::vector
	};
}
