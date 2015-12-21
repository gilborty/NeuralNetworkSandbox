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


private:
	double m_outputValue;
	std::vector<Connection> m_outputWeights;

	static double randomWeight( void ) { return rand() / double( RAND_MAX ); }

};
