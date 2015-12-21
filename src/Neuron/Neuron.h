#pragma once

#include <cstdlib>
#include <vector>
#include <cmath>


//TODO have connection implement random weight
struct Connection
{
	double weight;
	double deltaWeight;
};

class Neuron
{
public:

	Neuron( unsigned int numberOfOuptuts, unsigned int neuronIndex );

	void setOutputValue( double value ) { m_outputValue = value; }
	double getOutputValue() const { return m_outputValue; }

	void calculateOutputGradients( double targetValue );
	void calculateHiddenGradients( const Layer& nextLayer );

	void feedForward( const Layer& previousLayer );

private:
	double m_outputValue;
	unsigned int m_neuronIndex;

	double m_gradient;
	std::vector<Connection> m_outputWeights;

	double sumDOW( const Layer& nextLayer ) const;

	static double transferFunction( double x );
	static double transferFunctionDerivative( double x );
	static double randomWeight() { return rand() / double( RAND_MAX ); }

};
