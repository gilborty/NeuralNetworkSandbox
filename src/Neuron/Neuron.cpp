#include "Neuron.h"

Neuron::Neuron( unsigned int numberOfOuptuts )
{
	for( unsigned int connections = 0; connections < numberOfOuptuts; ++connections )
	{
		m_outputWeights.push_back( Connection() );

		//Set weight to random
		m_outputWeights.back().weight = randomWeight();
	}
}
