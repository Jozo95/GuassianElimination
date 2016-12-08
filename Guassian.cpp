#include "Guassian.h"

Guassian::Guassian(){
	this->matrix = new double*[10];
}

Guassian::Guassian(std::string filename){
	if (readFile(filename)) {
		printMatrix();
	}
}

std::string Guassian::printMatrix()
{
	std::stringstream matrixPrint;
	matrixPrint << "-" << std::endl;
	for (int i = 0; i < totalSize; i++) {
		matrixPrint <<  "|";
		for (int q = 0; q < totalSize-1; q++) {
			matrixPrint << " " << matrix[i][q] << ", ";
		}
		matrixPrint << " | " <<  matrix[i][totalSize-1] << " |" << std::endl;
	}
	

	std::cout << matrixPrint.str() << std::endl;
	return matrixPrint.str();
}

bool Guassian::readFile(std::string filename)
{
	std::ifstream file;
	file.open(filename);
	if (file.is_open()) {
		std::cout << "File open, continueing" << std::endl;
		file >> totalSize;
		std::cout << "N value; " << totalSize << std::endl;
		this->matrix = new double*[totalSize];
		int q = 0,i  = 0,b = 0;
		for (i; i < totalSize; i++)
			this->matrix[i] = new double[totalSize];
		std::cout << "Matrix ** added with n*n->; " << totalSize << ". Starting to read values..." << std::endl;
		i = 0;

		while (!file.eof()) {
			while (q < totalSize) {
				file >> this->matrix[i][b++];
				std::cout << "Value read: " << matrix[i][b] << std::endl; 
				q++;
			}
			b = 0;
			q = 0;
			i++;
		}
		//std::cout << "VALLLLLLLL:" << matrix[0][totalSize - 3];

		return true;
	}

	return false;
}
