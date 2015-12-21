#include "Net.h"
#include "Neuron.h"
#include "TrainingData.h"

#include <vector>

std::string dataFile = "data/trainingData.txt";

void showVectorValues( std::string label, std::vector<double>& vectorIn )
{
	std::cout << label << " ";

	for( unsigned int i = 0; i < vectorIn.size(); ++i )
	{
		std::cout << vectorIn[i] << " ";
	}

	std::cout << std::endl;
}

int main( int argc, char** argv )
{
	TrainingData trainingData( dataFile );

	//Construct the network
	std::vector<unsigned int> topology;
	trainingData.getTopology( topology );

	Net network( topology );

    //Training
	std::vector<double> inputValues, targetValues, resultValues;
	int trainingPass = 0;

	while( !trainingData.isEndOfFile() )
	{
		++trainingPass;
		std::cout << "Pass number: " << trainingPass << std::endl;

		//Get new input data and feed it forward
		if( trainingData.getNextInputs( inputValues ) != topology[0] )
		{
			break;
		}
		showVectorValues( ": Inputs:", inputValues );
		network.feedForward( inputValues );

		//Collect the net's actual results
		network.getResults( resultValues );
		showVectorValues( "Outputs:", resultValues );

		//Train the net what the outputs should have been
		trainingData.getTargetOutputs( targetValues );
		showVectorValues( "Targets:", targetValues );
		assert( targetValues.size() == topology.back() );

		network.backProp( targetValues );

		//Report back on how well it is doing
		std::cout << "Net recent average error: "
					<< network.getRecentAverageError() << std::endl;


	}

	std::cout << "Done. " << std::endl;

    return 0;

}

