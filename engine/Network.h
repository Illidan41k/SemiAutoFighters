#pragma once
#include <vector>
#include <algorithm>
#include <numeric>

#include "Field.h"
namespace engine
{
	class Network
	{
	public:

		Network(const int inputSize)
		{
			m_input.reserve(inputSize);

		}
		
		std::vector<float> Compute(std::shared_ptr<Field> field)
		{
			m_layers[0]->Compute(field->Flatten());

			m_layers[1]->Compute(m_layers[0]->m_outputs);

			return m_layers[1]->m_outputs;
		}

		void Dense(const int inputSize, int initRand)
		{
			m_layers.emplace_back(std::make_shared<Layer>(inputSize, initRand));
		}

		std::shared_ptr<Network> GetChild(std::shared_ptr<Network> other)
		{
			std::shared_ptr<Network> child = std::make_shared<Network>(1);
		}


	private:
		struct Neuron
		{
			Neuron(const int& inputSize)
			{
				m_weights.reserve(inputSize);


				for (int i = 0; i < inputSize; i++)
				{
					float newWeight = m_min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_max - m_min)));

					m_weights.push_back(newWeight);

				}
			}

			float Compute(const std::vector<float>& inputs)
			{
				return Activation(inputs);
			}

			float Activation(const std::vector<float>& inputs)
			{
				std::vector<float> result{};
				result.reserve(inputs.size());

				std::transform(inputs.begin(), inputs.end(),
					m_weights.begin(), std::back_inserter(result),
					std::multiplies<float>());

				float sum = std::accumulate(result.begin(), result.end(),
					decltype(result)::value_type(0));

				auto temp = (1 + std::exp(sum));
				auto activation = 1 / temp;

				return activation;
			}

			std::vector<float> m_weights{};
			int m_len{ 0 };

			float m_min = -1.;
			float m_max = 1.;
		};


		struct Layer //
		{
			Layer(const int& neurons, int initRand)
			{
				std::srand(initRand);

				for (int i = 0; i < neurons; i++)
				{
					m_neurons.emplace_back(std::make_shared<Neuron>(13*13));
				}
			}

			void Compute(const std::vector<float>& inputs)
			{
				m_outputs.clear();
				m_outputs.reserve(m_neurons.size());

				for (auto& n : m_neurons)
				{
					m_outputs.emplace_back(n->Compute(inputs));
				}
			}

			std::vector<float> m_outputs{};
			std::vector<std::shared_ptr<Neuron>> m_neurons{};
		};





		std::vector<std::shared_ptr<Layer>> m_layers{};
		std::vector<int> m_input{};
	};

}