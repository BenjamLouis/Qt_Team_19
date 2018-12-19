#ifndef _FASTA_WRITER_
#define _FASTA_WRITER_
#include "Writer.h"
#include <string>
#include <map>

class FastaWriter : public Writer {

public:

	FastaWriter(std::multimap<std::string, std::string> attribute) : 
	sequences(attribute)
	{};
	
private:

	/*! Uses the return of a funcion defined in fastareader: mapToWriter<a chromosome,
	the associated sequence> */
	void process();
	std::multimap<std::string, std::string> sequences;
	

};

#endif
