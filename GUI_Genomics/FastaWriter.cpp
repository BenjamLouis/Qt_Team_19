#include "FastaWriter.h"
#include <fstream>


void FastaWriter::process() {

	std::ofstream fasta_file("../result/result.fasta");

	for (auto i : sequences) {

		fasta_file << i.first << "\n" << i.second << "\n";

	};

}

//------------------------------------------------------------------------------
