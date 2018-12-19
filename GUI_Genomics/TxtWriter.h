#ifndef _TXT_WRITER_
#define _TXT_WRITER_
#include "Writer.h"
#include <string>
#include <vector>


struct interest {
	std::string chromosome;
	size_t start_position;
	bool direction;
	std::string sequence;
	double score;
};

class TxtWriter : public Writer {
	
public:
	
	TxtWriter(std::vector<interest> values):
	toWrite(values)
	{};
	
private:

	void process();
	std::vector<interest> toWrite;
	
	
};

#endif

