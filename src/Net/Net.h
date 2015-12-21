#pragma once

#include <iostream>
#include <vector>
#include <cassert>

#include "Neuron.h"

using Layer = std::vector<Neuron>;

class Net
{
public:
	//TODO implement topology data type if he doesn't
	Net( const std::vector<unsigned int>& topology );

	//Public member functions
	void feedForward( const std::vector<double>& inputValues );

	void backProp( const std::vector<double>& targetValues );

	void getResults( std::vector<double>& resultValues ) const;

private:
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
	std::vector<Layer> m_layers; //m_layers[layerNumber][neuronNumber]

};

