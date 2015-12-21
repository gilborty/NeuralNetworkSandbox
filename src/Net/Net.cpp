#include "Net.h"

Net::Net( const std::vector<unsigned int>& topology )
{
	unsigned int numberOfLayers = topology.size();

	for( unsigned int layerNumber = 0; layerNumber < numberOfLayers; ++layerNumber )
	{
		m_layers.push_back( Layer() );

		unsigned int numberOfOuptuts = layerNumber == topology.size() - 1 ? 0: topology[ layerNumber + 1 ];
		//We have made a new layer, now fill it with neurons,
		//and add a bias neuron to the layer:
		for( unsigned int neuronNumber = 0; neuronNumber <= topology[ layerNumber ]; ++neuronNumber )
		{
			m_layers.back().push_back( Neuron( numberOfOuptuts, neuronNumber ) );
			std::cout << "Made a neuron." << std::endl;
		}

	}
}

void Net::backProp( const std::vector<double>& targetValues )
{
	//Calculate overall net error (e.g. RMS)
	//Trying to minimze this during backProp()

	//TODO implement RMS error function
	Layer& outputLayer = m_layers.back();
	m_error = 0.0;

	for( unsigned int n = 0; n < outputLayer.size() - 1; ++n )
	{
		double delta = targetValues[n] - outputLayer[n].getOutputValue();
		m_error += delta * delta;
	}

	m_error /= outputLayer.size() - 1;
	m_error = sqrt( m_error );




	//Calculate output layer gradients

	//Calculate hidden layer gradients

	//For all layers from outputs to first hidden layer
	//update the connection weights

}

void Net::feedForward( const std::vector<double>& inputValues )
{
	//Make sure that the input values are equal to the number of neurons in first layer minus the additional bias neuron
	assert( inputValues.size() == m_layers[0].size() - 1 );

	//Assign (latch) the input values into the input neurons
	for( unsigned i = 0; i < inputValues.size(); ++i )
	{
		m_layers[0][i].setOutputValue( inputValues[i] );

	}

	//Forward propagate
	for( unsigned int layerNumber = 0; layerNumber < inputValues.size(); ++layerNumber )
	{
		Layer& previousLayer = m_layers[ layerNumber - 1 ];

		for( unsigned int n = 0; n < m_layers[ layerNumber ].size() - 1; ++n )
		{
			m_layers[layerNumber][n].feedForward( previousLayer );
		}
	}

}
