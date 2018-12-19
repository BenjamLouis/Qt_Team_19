#include "output.h"
#include <iostream>
#include <tclap/ArgException.h>
#include <typeinfo>


void MyOutput::failure(TCLAP::CmdLineInterface& _cmd, TCLAP::ArgException& e)
	{
	std::string progName = _cmd.getProgramName();
																					//_______________________A VERIFIER AVEC BENJAM_________________________//
	std::cerr << "PARSE ERROR: " << e.argId() << std::endl
		      << "             " << e.error() << std::endl << std::endl;

		 TCLAP::CmdLineParseException err;
		 if (typeid(e) == typeid(err)) {
			std::cerr
						 << "             Reminder: Please Input a sequence file (.fasta)" << std::endl
						 << "             and either: " << "matrix file and threshold to find positions to create bed file" << std::endl
						 << "             or: " << "length of the sequence and bed file to create a matrix file (optional: the name of a sepecific chromosome in which to look at)" << std::endl << std::endl;
		  }

	if ( _cmd.hasHelpAndVersion() )
		{
			std::cerr << "Brief USAGE: " << std::endl;

			_shortUsage( _cmd, std::cerr );

			std::cerr << std::endl << "For complete USAGE and HELP type: "
					  << std::endl << "   " << progName << " "
					  << TCLAP::Arg::nameStartString() << "help"
					  << std::endl << std::endl;
		}
	else
		usage(_cmd);

	throw TCLAP::ExitException(1);
}

//------------------------------------------------------------------------------
