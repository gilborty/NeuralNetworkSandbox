#include "Net.h"

Net::Net( const std::vector<unsigned int>& topology )
	: m_error( 0.0 )
	, m_recentAverageError( 0.0 )
	, m_recentAverageSmoothingFactor( 0.5 )
{
	unsigned int numberOfLayers = topology.size();

	for( unsigned int layerNumber = 0; layerNumber < numberOfLayers; ++layerNumber )
	{
		m_layers.push_back( Neuron::Layer() );
		std::cout << "Created a layer" << std::endl;

		unsigned int numberOfOuptuts = layerNumber == topology.size() - 1 ? 0 : topology[ layerNumber + 1 ];
		//We have made a new layer, now fill it with neurons,
		//and add a bias neuron to the layer:
		for( unsigned int neuronNumber = 0; neuronNumber <= topology[ layerNumber ]; ++neuronNumber )
		{
			m_layers.back().push_back( Neuron( numberOfOuptuts, neuronNumber ) );
			std::cout << "Made a neuron." << std::endl;
		}

		//Force the bias neuron's output value to one. It's the last neuron created above
		m_layers.back().back().setOutputValue( 1.0 );
	}
}

void Net::getResults( std::vector<double>& resultValues ) const
{
	resultValues.clear();

	for( unsigned int n = 0; n < m_layers.back().size() - 1; ++n )
	{
		resultValues.push_back( m_layers.back()[n].getOutputValue() );
	}
}

void Net::backProp( const std::vector<double>& targetValues )
{
	//Calculate overall net error (e.g. RMS)
	//Trying to minimze this during backProp()

	//TODO implement RMS error function
	Neuron::Layer& outputLayer = m_layers.back();
	m_error = 0.0;

	for( unsigned int n = 0; n < outputLayer.size() - 1; ++n )
	{
		double delta = targetValues[n] - outputLayer[n].getOutputValue();
		m_error += delta * delta;
	}

	m_error /= outputLayer.size() - 1;
	m_error = sqrt( m_error );
	std::cout << "Error: " << m_error << std::endl;

	//Implement a recent average error measurement
	//TODO actually implement as a function
	m_recentAverageError = ( m_recentAverageError * m_recentAverageSmoothingFactor + m_error )
							/ (m_recentAverageSmoothingFactor + 1.0 );


	//Calculate output layer gradients
	for( unsigned int n = 0; n < outputLayer.size() - 1; ++n )
	{
		outputLayer[n].calculateOutputGradients( targetValues[n] );

	}

	//Calculate hidden layer gradients
	for( unsigned int layerNumber = m_layers.size() - 2; layerNumber > 0; --layerNumber )
	{
		Neuron::Layer& hiddenLayer = m_layers[layerNumber];
		Neuron::Layer& nextLayer = m_layers[layerNumber + 1];

		for( unsigned int n = 0; n < m_layers[layerNumber].size() - 1; ++n )
		{
			hiddenLayer[n].calculateHiddenGradients( nextLayer );
		}
	}

	//For all layers from outputs to first hidden layer
	//update the connection weights
	for( unsigned int layerNumber = m_layers.size() - 1; layerNumber > 0; --layerNumber )
	{
		Neuron::Layer& currentLayer = m_layers[layerNumber];
		Neuron::Layer& previousLayer = m_layers[layerNumber - 1];

		for( unsigned int n = 0; n < currentLayer.size() - 1; ++n )
		{
			currentLayer[n].updateInputWeights(previousLayer);
		}
	}

}

void Net::feedForward( const std::vector<double>& inputValues )
{
	//Make sure that the input values are equal to the number of neurons in first layer minus the additional bias neuron
	assert( inputValues.size() == m_layers[0].size() - 1 );


	//Assign (latch) the input values into the input neurons
	for( unsigned int i = 0; i < inputValues.size(); ++i )
	{
		m_layers[0][i].setOutputValue( inputValues[i] );
	}


	//Forward propagate
	for( unsigned int layerNumber = 1; layerNumber < m_layers.size(); ++layerNumber )
	{
		Neuron::Layer& previousLayer = m_layers[ layerNumber - 1 ];

		for( unsigned int n = 0; n < m_layers[ layerNumber ].size() - 1; ++n )
		{
			m_layers[layerNumber][n].feedForward( previousLayer );
		}
	}

}
