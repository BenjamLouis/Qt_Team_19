#include "MatrixWriter.h"
#include <string>
#include <fstream>
#include <iostream>

void MatrixWriter::process() {
	
	std::ofstream mat_file("../result/result.mat", std::ios::out | std::ios::trunc);
	
	for (size_t i(0); i < matrix.size(); ++i) {
		
		for (size_t j(0); j < matrix[i].size(); ++j) {
			
			mat_file << matrix[i][j];
			mat_file << "\t";
			
		};
		
		mat_file << "\n";
		

	};
	
}


