#ifndef _MATRIX_READER_
#define _MATRIX_READER_
#include <vector>
#include <array>
#include <string>
#include <fstream>

typedef std::vector<std::array<double, 4>> Matrix;

class MatrixReader {
	
public:

	MatrixReader(std::string file_name);
	/*! Read the matrix file
	 * @throw logic_error the file cannot be opened
	*/
	void read_matrix();
	Matrix getMatrix() const;
	double calculus(std::string sequence);

private:
	
	/*! Function that looks for the value of a single nucleotide at a specific position
	 * @param[in] i la position dans la sequence
	 * @param [in] nucleotide l'indice du nucleotide (0 = A, 1 = C, 2 = G, 3 = T);
	 * @param[out] le score de ce nucleotide; */
	double compute(size_t i, size_t nucleotide);
	std::ifstream file;
	Matrix matrix;

};


#endif


