#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
class Guassian {
public:
	Guassian();
	Guassian(std::string filename);
	double **matrix;
	std::string printMatrix();
	void testTheValues();

	void solveToZeros(int startingRow);

	void solveToZerosFromBottom(int startingRow);

	void findAllCombinations();

	int factorial(int n);

	bool calculateMatrix();
private:

	double *matrix2;
	double **matrixCpy;
	int totalSizeRow,totalSizeColumn;
	bool readFile(std::string filename);
	
};