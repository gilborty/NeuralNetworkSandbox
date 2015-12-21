#include "Net.h"

Net::Net( const std::vector<unsigned int>& topology )
{
	unsigned int numberOfLayers = topology.size();

	for( unsigned int layerNumber = 0; layerNumber < numberOfLayers; ++layerNumber )
	{
		m_layers.push_back( Layer() );

		//We have made a new layer, now fill it with neurons,
		//and add a bias neuron to the layer:
		for( unsigned int neuronNumber = 0; neuronNumber <= topology[ layerNumber ]; ++neuronNumber )
		{
			m_layers.back().push_back( Neuron() );
			std::cout << "Made a neuron." << std::endl;
		}

	}


}
