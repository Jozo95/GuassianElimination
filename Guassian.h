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
private:
	int totalSize;
	bool readFile(std::string filename);
	
};