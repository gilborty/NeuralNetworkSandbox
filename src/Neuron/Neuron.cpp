#include "Neuron.h"

Neuron::Neuron( unsigned int numberOfOuptuts, unsigned int neuronIndex )
{
	for( unsigned int connections = 0; connections < numberOfOuptuts; ++connections )
	{
		m_outputWeights.push_back( Connection() );

		//Set weight to random
		m_outputWeights.back().weight = randomWeight();
	}

	m_neuronIndex = neuronIndex;
}

double Neuron::transferFunction( double x )
{
	//Hyperbolic tan: tanh
	//Output range [-1.0, 1.0]

	return tanh( x );
}

double Neuron::transferFunctionDerivative( double x )
{
	//Use approximation, actual is 1 - tanh^2( x )
	return 1.0 - x * x;
}

void Neuron::feedForward( const Layer& previousLayer )
{
	//Sum up the inputs
	double sum = 0.0;

	//Sum the previous layer's outputs (which are inputs)
	//Need to include the bias neuron from the previous layer as well

	for( unsigned int n = 0; n < previousLayer.size(); ++n )
	{
		sum += previousLayer[n].getOutputValue() *
				previousLayer[n].m_outputWeights[ m_neuronIndex ].weight;
	}

	m_outputValue = transferFunction( sum );



}
