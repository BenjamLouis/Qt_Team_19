#include "TxtWriter.h"
#include <fstream>
#include <iomanip>

void TxtWriter::process() {

	std::ofstream txt_file("../result/result.txt", std::ios::out | std::ios::trunc);
	
	for (size_t i(0); i < toWrite.size(); ++i) {
		
		txt_file << toWrite[i].chromosome << "\t" << toWrite[i].start_position << "\t";
		if (toWrite[i].direction) { txt_file << "+"; } else { txt_file << "-"; };
		txt_file << "\t" << toWrite[i].sequence << "\t" << toWrite[i].score << "\n";
		
	}
	
}

