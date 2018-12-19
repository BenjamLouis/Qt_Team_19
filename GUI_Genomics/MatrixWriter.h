#ifndef _MATRIX_WRITER_
#define _MATRIX_WRITER_
#include "Writer.h"
#include <array>
#include <vector>

typedef std::vector<std::array<double, 4> > Matrix;

class MatrixWriter : public Writer {
	
public:

	MatrixWriter(Matrix attribute) :
	matrix(attribute)
	{};
	
private: 

		
	/*! From the numeric version of the matrix, this function will generate a file named result.mat in which
	 * the matrix will be tanslated, written as 4 coulumns, (A, T, C, G), separated by a tabulation */
	void process();
	Matrix matrix;
		

};

#endif


