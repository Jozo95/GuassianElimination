#include "Guassian.h"

Guassian::Guassian(){
	this->matrix = new double*[10];
}

Guassian::Guassian(std::string filename){

}

std::stringstream Guassian::printMatrix()
{
	return std::stringstream();
}

bool Guassian::readFile(std::string filename)
{
	return false;
}
