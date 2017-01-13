#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class Guassian {
public:
	Guassian();
	Guassian(std::string filename);
	double **matrix;
	std::string printMatrix();
	void testTheValues();

	bool calculateMatrix();
private:
	double *matrix2;
	double **matrixCpy;
	int totalSize;
	bool readFile(std::string filename);
	
};