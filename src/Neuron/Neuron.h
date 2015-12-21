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
	using Layer = std::vector<Neuron>;

	Neuron( unsigned int numberOfOuptuts, unsigned int neuronIndex );

	void setOutputValue( double value ) { m_outputValue = value; }
	double getOutputValue() const { return m_outputValue; }

	void calculateOutputGradients( double targetValue );
	void calculateHiddenGradients( const Layer& nextLayer );

	void updateInputWeights( Layer& previousLayer );

	void feedForward( const Layer& previousLayer );

private:
	const double m_eta;		//[0.0, 1.0] overall net training rate
	const double m_alpha;    //[0.0, n] multiplier of the last weight change (i.e. momentum)
	double m_outputValue;
	unsigned int m_neuronIndex;

	double m_gradient;
	std::vector<Connection> m_outputWeights;

	double sumDOW( const Layer& nextLayer ) const;

	static double transferFunction( double x );
	static double transferFunctionDerivative( double x );
	static double randomWeight() { return rand() / double( RAND_MAX ); }

};
