#include <string>
#include <sstream>

class Guassian {
public:
	Guassian();
	Guassian(std::string filename);
	std::stringstream printMatrix();
private:
	bool readFile(std::string filename);
	double **matrix;
};