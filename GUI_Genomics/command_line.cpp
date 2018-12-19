#include "command_line.h"
#include <tclap/CmdLine.h>
#include "output.h"

usage Command::initialize(int argc, char** argv) {

	TCLAP::CmdLine cmd("Command description message", ' ', "0.1");

	MyOutput my;
	cmd.setOutput( &my );

// TCLAP interface

	TCLAP::ValueArg<std::string> sequenceArg("s", "sequence", "Name of the .fasta containing the sequence", true, "default.fasta", "string");
	cmd.add(sequenceArg);

	TCLAP::ValueArg<std::string> matrixArg("m", "matrix", "Name of the .pmw containing the matrix", false, "default.pmw", "string");
	cmd.add(matrixArg);

	TCLAP::ValueArg<std::string> thresholdArg("t", "threshold", "Minimum value for a sequence to be taken into account", false, "0.0", "double");
	cmd.add(thresholdArg);

	TCLAP::ValueArg<std::string> lengthArg("l", "length", "Length of the searched motif", false, "3", "int");
	cmd.add(lengthArg);

	TCLAP::ValueArg<std::string> bedArg("b", "bedfile", "Name of the bed file that needs to be read", false, "default.bed", "string");
	cmd.add(bedArg);

	TCLAP::ValueArg<std::string> nameArg("n", "name" , "Name of a specific chromosome to look for", false, "nochomosome", "string");
	cmd.add(nameArg);

	cmd.parse(argc, argv);

	setArgs[0] = matrixArg.isSet();
	setArgs[1] = thresholdArg.isSet();
	setArgs[2] = lengthArg.isSet();
	setArgs[3] = bedArg.isSet();
	setArgs[4] = nameArg.isSet();

	parameters.insert(std::make_pair(0, matrixArg.getValue()));
	parameters.insert(std::make_pair(1, thresholdArg.getValue()));
	parameters.insert(std::make_pair(2, lengthArg.getValue()));
	parameters.insert(std::make_pair(3, bedArg.getValue()));
	parameters.insert(std::make_pair(4, nameArg.getValue()));
	parameters.insert(std::make_pair(5, sequenceArg.getValue()));

//Depending on the arguments given, one or the other of the functionalities is performed

	if (setArgs[0] && setArgs[1] && !setArgs[2] && !setArgs[3]) {
		return usage::FINDING_POSITIONS;
	}else if (!setArgs[0] && !setArgs[1] && setArgs[2] && setArgs[3]) {
		return usage::CREATING_MATRIX;
	}else {
		return usage::UNDEFINED_USAGE;
	}

}

//------------------------------------------------------------------------------

void Command::inform_user() {

	std::cerr << "Error, you have entered the parameters :" << std::endl;
	std::cout << parameters[4] << "  ";
	for (size_t i(0); i <= 3; ++i) {
		if (setArgs[i]) { std::cout << parameters[i] << "  "; };
	};
	std::cout << std::endl
	<< "Which do not define a possible utilisation of the program" << std::endl << std::endl
	<< "To find postions accepted by the protein please enter : " << std::endl
	<< "-s yourfile.fasta -m yourfile.mat -t minimum value" << std::endl << std::endl
	<< "To recreate the protein acceptance matrix please enter : " << std::endl
	<< "-s yourfile.fasta -l length of the sequence -b yourfile.bed (optional): -n name of a specific sequence in which to look" << std::endl << std::endl
	<< "For further USAGE and HELP type : " << std::endl
	<< "./CommandLine --help" << std::endl;

}

//------------------------------------------------------------------------------

std::string Command::getSequence() {

	return parameters[5];

}

//------------------------------------------------------------------------------

std::string Command::getMatrix() {

	return parameters[0];

}

//------------------------------------------------------------------------------

double Command::getThreshold() {

	return std::stod(parameters[1]);

}

//------------------------------------------------------------------------------

int Command::getLength() {

	return std::stoi(parameters[2]);

}

//------------------------------------------------------------------------------

std::string Command::getBed() {

	return parameters[3];

}

//------------------------------------------------------------------------------

std::string Command::getChromosome() {

	return parameters[4];

}

//------------------------------------------------------------------------------
