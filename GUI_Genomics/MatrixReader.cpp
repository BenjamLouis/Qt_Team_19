#include "MatrixReader.h"
#include <iostream>
#include <cmath>

MatrixReader::MatrixReader(std::string file_name) :
	file(file_name)
	{
		read_matrix();
		}

//------------------------------------------------------------------------------

void MatrixReader::read_matrix() {
	std::string line;

	if (!file.is_open()) {
		std::cerr << "Log 14 : INFO : Le fichier matrice ne peut pas etre ouvert " << std::endl; // Log tracking
		throw(std::logic_error(std::string("Le fichier matrice ne peut pas être ouvert")));											

	} else {

		while(!file.eof()) {
                        try{
				file.exceptions(file.failbit | file.badbit);
				std::getline(file, line);
				std::string::size_type spliter(0);
				std::array<double, 4> insert;
				size_t counter(0);

				while (((spliter != std::string::npos) || (!file.eof())) && (counter < insert.size())) {
					size_t start_pos(spliter);
					spliter = line.find("\t", start_pos+1);
					std::string value = line.substr(start_pos, spliter);
					size_t check(value.find("\t"));
					if(check != std::string::npos) value.erase(check,1);
					double valueDouble = std::atof(value.c_str());
					double log_value = log2(valueDouble);
					insert[counter] = log_value;
					++counter;
				}

				matrix.push_back(insert);
                    } catch (std::ifstream::failure &e) {
                            if(!file.eof()) {
                                    std::cerr << "Log 18 : FATAL : Impossible de lire le fichier bien qu'ouvert. " << std::endl;
                                    throw std::logic_error(std::string("MatrixReader::read_matrix() : Impossible de lire le fichier bien qu'ouvert."));
                            }
                    }
		}

		file.close();
	}
}

//------------------------------------------------------------------------------

Matrix MatrixReader::getMatrix() const {

	return matrix;

}

//------------------------------------------------------------------------------

double MatrixReader::calculus(std::string sequence) {

	if (sequence.size() != matrix.size()) {

		std::cerr << "Log 16 : INFO : La sequence  dont on veut calculer le score n a pas la bonne taille " << std::endl; // Log tracking												
		return 0.; // error value

	}else {

		double sum(0);

		for (size_t i(0); i < sequence.size(); ++i) {

			const char nucleotide(sequence[i]);

			switch(nucleotide) {  

				case('A'): case ('a'):
				sum += (2 + compute(i, 0));
				break;

				case('C') : case ('c'):
				sum += (2 + compute(i, 1));
				break;

				case('G'): case('g'):
				sum += (2 + compute(i, 2));
				break;

				case('T'): case ('t'):
				sum += (2 + compute(i, 3));
				break;

				default:
				sum += 0;																																								
				break;
			}
		}
		return sum;
	}
}

//------------------------------------------------------------------------------

double MatrixReader::compute(size_t i, size_t nucleotide) {

	return matrix[i][nucleotide];

}

//------------------------------------------------------------------------------
