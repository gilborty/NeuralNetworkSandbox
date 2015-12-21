#include "Neuron.h"

Neuron::Neuron( unsigned int numberOfOuptuts, unsigned int neuronIndex )
	: m_eta( 0.15 )
	, m_alpha( 0.5 )
{
	for( unsigned int connections = 0; connections < numberOfOuptuts; ++connections )
	{
		m_outputWeights.push_back( Connection() );

		//Set weight to random
		m_outputWeights.back().weight = randomWeight();
	}

	m_neuronIndex = neuronIndex;
}

void Neuron::updateInputWeights( Layer& previousLayer )
{
	//The weights to be updated are in the Connection container in the neurons in the previous layer

	for( unsigned int n = 0; n < previousLayer.size(); ++n )
	{
		Neuron& neuron = previousLayer[n];

		double oldDeltaWeight = neuron.m_outputWeights[m_neuronIndex].deltaWeight;

		double newDeltaWeight =
				//Individual input, magnified by the gradient and train rate
				m_eta
				* neuron.getOutputValue()
				* m_gradient
				//Also add momentum, a fraction of the previous delta weight
				+ m_alpha
				* oldDeltaWeight;

		neuron.m_outputWeights[m_neuronIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_neuronIndex].weight += newDeltaWeight;
	}
}

double Neuron::sumDOW( const Layer& nextLayer ) const
{
	double sum = 0.0;

	//Sum our contributions of the errors at the nodes we feed

	for( unsigned int n = 0; n < nextLayer.size() - 1; ++n )
	{
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

void Neuron::calculateOutputGradients( double targetValue )
{
	double delta = targetValue - m_outputValue;
	m_gradient = delta * transferFunctionDerivative( m_outputValue );
}

void Neuron::calculateHiddenGradients( const Layer& nextLayer )
{
	double dow = sumDOW( nextLayer );
	m_gradient = dow * transferFunctionDerivative( m_outputValue );

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
