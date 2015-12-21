#include "Net.h"
#include "Neuron.h"

#include <vector>

int main( int argc, char** argv )
{
	//Construct the network
	std::vector<unsigned int> topology;

	topology.push_back( 3 ); //3 inputs
	topology.push_back( 2 ); //2 hidden
	topology.push_back( 1 ); //1 output

	Net network( topology );

    //Training
    std::vector<double> inputValues;
    network.feedForward( inputValues );

    //Backprop learning
    std::vector<double> targetValues;
    network.backProp( targetValues );

    //
    std::vector<double> resultValues;
    network.getResults( resultValues );

    return 0;

}

