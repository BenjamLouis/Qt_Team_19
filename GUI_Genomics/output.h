#ifndef OUTPUT_H
#define OUTPUT_H
#include <tclap/StdOutput.h>

class MyOutput : public TCLAP::StdOutput {
	
public: 		

	virtual void failure(TCLAP::CmdLineInterface& c, TCLAP::ArgException& e);


};

#endif
