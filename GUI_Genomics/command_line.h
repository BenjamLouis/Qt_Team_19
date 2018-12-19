#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H
#include <array>
#include <map>
#include <string>

enum usage {
	
	FINDING_POSITIONS,
	CREATING_MATRIX,
	UNDEFINED_USAGE,
	
};

class Command {
	
public: 
	/*! Analyses and parses the arguments given and determines the usage intended,
	 * 	or if it is not a known usage.
	 *  @param[out] usage enum type told by the parameters */
	usage initialize(int argc, char** argv);
	
	/*! Takes care of informing the user of his mistake when the parameters do not define a known usage*/
	void inform_user();
	std::string getSequence();
	std::string getMatrix();
	double getThreshold();
	int getLength();
	std::string getBed();
	
	/*! Returns "nochromosome" if no chromosome was entered */
	std::string getChromosome() ;

private:

	std::array<bool, 4> setArgs;
	std::map<size_t, std::string> parameters;
	
};


#endif

