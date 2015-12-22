#include "TrainingDataHandler.h"

TrainingDataHandler::TrainingDataHandler( const std::string trainingDataFile )
{
	m_trainingDataFile.open( trainingDataFile.c_str() );
}

void TrainingDataHandler::getTopology( std::vector<unsigned int>& topology )
{
	std::string line;
	std::string label;

	std::getline( m_trainingDataFile, line );

	std::stringstream ss( line );

	ss >> label;

	if( this->isEndOfFile() || label.compare( "topology:") != 0 )
	{
		abort();
	}

	while( !ss.eof() )
	{
		unsigned int n;
		ss >> n;
		topology.push_back( n );
	}

	return;
}

unsigned int TrainingDataHandler::getNextInputs( std::vector<double>& inputValues )
{
	inputValues.clear();

	std::string line;
	std::getline( m_trainingDataFile, line );
	std::stringstream ss( line );

	std::string label;
	ss >> label;
	if( label.compare("in:") == 0 )
	{
		double oneValue;
		while( ss >> oneValue )
		{
			inputValues.push_back( oneValue );
		}
	}

	return inputValues.size();
}

unsigned int TrainingDataHandler::getTargetOutputs( std::vector<double>& targetOutputValues )
{
	targetOutputValues.clear();

	std::string line;
	std::getline( m_trainingDataFile, line );
	std::stringstream ss( line );

	std::string label;
	ss >> label;
	if( label.compare("out:") == 0 )
	{
		double oneValue;
		while( ss >> oneValue )
		{
			targetOutputValues.push_back( oneValue );
		}
	}

	return targetOutputValues.size();
}
