#ifndef FASTAREADER_H
#define FASTAREADER_H

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "TxtWriter.h"
#include "MatrixReader.h"

class Fastareader {

public:
	/*! Constructor
	 @param[in] file: filename */
	Fastareader(std::string filename);
	/*!Make a vector containing our sequences of interest
		@param[in] multimap<string, pair<size_t, size_t> sequences to find and the nucleotides to find
		@param[out] vector<string> sequences of interest 
		@throw std::logic_error The file cannot be opened
		@throw std::logic_error No sequences have been found
	*/
	std::vector<std::string> seqInterest(const std::multimap<std::string, std::pair<size_t,size_t>>& toFind);
	/*!Create a map helping to write a fasta file using only sequences of interest */
	std::multimap<std::string, std::string> mapToWriter() const;
	/*!Generate the complementary nucleotide
	 *	@param[in] N nucleotide we want to reverse 
	 *	@param[out] C complemetnary of the nucleotide */
	char complementary(char N);
	/*!Generate a txt file analysing a fasta file depending on a PMW Matrix
	 * 	@param[in] T limit we want to overstep to keep a sequence
	 * 	@param[in] matName name of the matrix file 
	 * 	@throw std::logic_error The file cannot be opened
	 */
	void ReadAndCreate(std::string matName, double T);
	
private:
	std::ifstream file;
	std::multimap<std::string, std::string> headAndSeq; //! all the sequences (existant) of interest we will use to create the matrix and their header.
};

#endif
