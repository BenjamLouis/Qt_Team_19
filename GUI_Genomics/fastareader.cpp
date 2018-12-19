#include "fastareader.h"
#include <algorithm>
#include <chrono>


Fastareader::Fastareader(std::string filename) :
	file(filename)
	{}

//------------------------------------------------------------------------------

std::vector<std::string> Fastareader::seqInterest(const std::multimap<std::string, std::pair<size_t,size_t>>& toFind) {

std::string line, seq; //line = line of the file, we'll use it with a getline; seq = sequence of interest
seq.clear();
char c; //Character used to read the file
std::vector<std::string> allSeq; //Vector containing our sequences of interest, we will return it
headAndSeq.clear();
std::multimap<std::string, bool> checkExist; //Map used to check if a sequence exist or not
std::string nameSeq; //name of the header of the sequence we are reading, useful when we arrive at the end of file and that the two maps and allSeq does not push back the sequence name

	if(file.is_open()) {
		while (!file.eof()) {
			std::getline(file, line); //Reading the file char by char
			if(line[0] =='>') {
				size_t counter(0); //Will count the number of character taken in the sequence
				size_t position(0); //Position in the sequence
				int char_beg(file.tellg()); //Give the position of the character or line in the file
					for(auto it : toFind) {
						if(line == std::string(">") + it.first) {
							bool comple(it.second.second < it.second.first); //Check if we want the complementary of the seq (we have to reverse it)
							if(it.second.first < it.second.second) { //If we want the complementary of the sequence, we have decided to reverse the pair of size_t (it.second.first>it.second.second)
								if( position >= it.second.first) {
									counter = 0; file.seekg(char_beg); //if we want to extract a sequence which has its start before the end of the previous sequence asked, we return to the beginning of the seq
								} else if (position == it.second.first) { //as the character keep being implemented,
									 seq.push_back(c); 					  //if we want to extract a sequence which begins by the end of the previous sequence, we add the last character of the last sequence to the new one
								}
							} else {
								if(position >= it.second.first) {	//If we want the complementary of the sequence, we have decided to reverse the pair of size_t (it.second.first>it.second.second)
									counter = 0; file.seekg(char_beg);
								} else if (position == it.second.second) {
									seq.push_back(complementary(c));
								}
							}
							do {
								file>>c; //we read char by char the sequence
								if(c != '>') {
									if((it.second.first<it.second.second)&&(counter >= it.second.first)) {
										seq.push_back(c);
										position = it.second.second;
									} else if ((counter >= it.second.second)&& (it.second.first>it.second.second)) {
										seq.push_back(complementary(c));
										position = it.second.first;
									}
									++counter;
								}
							} while ((c != '>') && (!file.eof()) && (counter < std::max(it.second.second, it.second.first)));
							if(!seq.empty()) {
								if(comple) {
									std::reverse(seq.begin(), seq.end());
								}
								allSeq.push_back(seq);
								checkExist.insert(std::pair<std::string, bool>(it.first, true));
								headAndSeq.insert(std::pair<std::string, std::string>(std::string(">") + it.first, seq));
							} else {
								std::cerr << "Log 7 : INFO : Le nucléotide en position " << std::min(it.second.first, it.second.second) << " n existe pas "  << std::endl; // Log tracking				
							}
							seq.clear();
						}
					}

			}
			if(allSeq.size() == toFind.size()) {  //if we have the right size of vector, it means that all sequences have been found, so we return directly allSeq and we get back to the beginning of the file for further research in that same file
					file.seekg(file.beg);
					return allSeq;
			}
		}
		if(allSeq.empty()) {
				std::cerr << "Log 8 : ERROR : La liste de sequence cherchee n est pas trouve dans le fasta" << std::endl; // Log tracking					                    
				throw(std::logic_error(std::string("Fastareader::seqInterest  NO SEQUENCES FOUND")));
			}
		if(!seq.empty()) { //case where we reached end of file before seq being pushed back in all vector and maps
			allSeq.push_back(seq);
			checkExist.insert(std::pair<std::string, bool>(nameSeq, true));
			headAndSeq.insert(std::pair<std::string, std::string>(std::string(">") + nameSeq, seq));
		}

		if(allSeq.size() < toFind.size()) {
			for(auto i : toFind) {
				if(checkExist.find(i.first) == checkExist.end()) {
					std::cerr << "Log 9 : INFO : La borne " << i.first << " n a pas ete trouvee dans le fasta ou les nucleotides recherchés n'existaient pas ou n'ont pas été trouvés" << std::endl; // Log tracking					                     
				}
			}
		}
		file.seekg(file.beg);
	} else {
		std::cerr << "Log 10 : ERROR : Le fichier fasta n existe pas ou est ferme " << std::endl; // Log tracking					                
		throw(std::logic_error(std::string("Fastareader::seqInterest The file does not exist or is closed")));
	}
	return allSeq;
}

//------------------------------------------------------------------------------

std::multimap<std::string, std::string> Fastareader::mapToWriter() const {
	return headAndSeq;
}

char Fastareader::complementary(char N) {
	switch (N) {
		case ('A') : case ('a') : return 'T'; break;
		case ('T') : case ('t') : return 'A'; break;
		case ('G') : case ('g') : return 'C'; break;
		case ('C') : case ('c') : return 'G'; break;
		default : return 'N';
	}
}

//------------------------------------------------------------------------------

void Fastareader::ReadAndCreate(std::string matName, double T) {

	MatrixReader matreader(matName);
	std::vector<interest> allInterest;
	std::string line, seq, seqc; //line = line of the file, we'll use it with a getline; seq = sequence of interest; seqc = complementary.
	char nucle;
	unsigned int position(0);

	if(file.is_open()) {
			while (!file.eof()) {
				std::getline(file, line); //Reading the file char by char
				if(line[0] =='>') {
					line.erase(0,1);
					seq.clear();
					seqc.clear();
					position = 0;
					do {
						file >> nucle;
						if(nucle != '>') {
							seq.push_back(nucle);
							seqc.push_back(complementary(nucle));
							++position;
							if(seq.size() == matreader.getMatrix().size()) {
								double calcSeq(matreader.calculus(seq));
								std::string reversedSeqc(seqc);
								std::reverse(reversedSeqc.begin(), reversedSeqc.end());
								double calcSeqc(matreader.calculus(reversedSeqc));
								if(calcSeq >= T) {
									interest inter;
									inter.chromosome = line;
									inter.start_position = position - matreader.getMatrix().size() + 1;
									inter. direction = true;
									inter.sequence = seq;
									inter.score = calcSeq;
									allInterest.push_back(inter);
								}
								if(calcSeqc >= T) {
									interest interC;
									interC.chromosome = line;
									interC.start_position = position - matreader.getMatrix().size() + 1;
									interC. direction = false;
									interC.sequence = seq;
									interC.score = calcSeqc;
									allInterest.push_back(interC);
								}
								seq.erase(0,1);
								seqc.erase(0,1);
							}
						}
					} while((!file.eof())&&(nucle!= '>'));
					if(!file.eof()) {
						unsigned int lastpos(file.tellg());
						file.seekg(lastpos - 1);
					}
				}
			}
	} else {
		std::cerr << "Log 11 : ERROR : Le fichier fasta n existe pas ou est ferme " << std::endl; // Log tracking					           
		throw(std::logic_error(std::string("Fastareader::ReadAndCreate The file does not exist or is closed")));
	}
	TxtWriter writer(allInterest);
	writer.create_file();
}

//------------------------------------------------------------------------------
