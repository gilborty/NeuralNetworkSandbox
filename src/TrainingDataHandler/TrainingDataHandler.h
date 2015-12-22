#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class TrainingDataHandler
{
public:

	TrainingDataHandler( const std::string trainingDataFile );

	bool isEndOfFile() { return m_trainingDataFile.eof(); }
	void getTopology( std::vector<unsigned int>& topology );

	//Returns the number of input values read from the file
	unsigned int getNextInputs( std::vector<double>& inputValues );
	unsigned int getTargetOutputs( std::vector<double>& targetOutputValues );

private:
	std::ifstream m_trainingDataFile;

};
