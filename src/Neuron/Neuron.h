#pragma once

#include <cstdlib>
#include <vector>
//TODO have connection implement random weight
struct Connection
{
	double weight;
	double deltaWeight;
};

class Neuron
{
public:

	Neuron( unsigned int numberOfOuptuts );

	void setOutputValue( double value ) { m_outputValue = value; }
	double getOutputValue() const { return m_outputValue; }

	void feedForward( const Layer& previousLayer );

private:
	double m_outputValue;
	std::vector<Connection> m_outputWeights;

	static double randomWeight() { return rand() / double( RAND_MAX ); }

};
