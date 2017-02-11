#include "Guassian.h"

Guassian::Guassian(){
	this->matrix = new double*[10];
}

Guassian::Guassian(std::string filename){
	if (readFile(filename)) {
		printMatrix();
	}
	matrix2 = new double[totalSize];
}

std::string Guassian::printMatrix()
{
	std::stringstream matrixPrint;
	matrixPrint.setf(4);
	matrixPrint << "-" << std::endl;
	for (int i = 0; i < totalSize; i++) {
		matrixPrint <<  "|";
		for (int q = 0; q < totalSize; q++) {
			matrixPrint << " " << matrix[i][q] << ", ";
		}
		matrixPrint << " | " <<  matrix[i][totalSize] << " |" << std::endl;
	}
	std::cout.setf(std::ios::fixed);
	std::cout.setf(std::ios::showpoint);
	std::cout.precision(4);

	std::cout << matrixPrint.str() << std::endl;
	return matrixPrint.str();
}

void Guassian::testTheValues(){
	
	std::cout << "Row looks like; " << std::endl;
	double theSolution = 0,theSolWithCalc=0;
	printMatrix();
	for (int i = 0; i < totalSize; i++) {
		theSolution = matrixCpy[i][totalSize];
		std::cout << "The solution we need; " << theSolution << std::endl;
		for (int k = 0; k < totalSize; k++) {
			theSolWithCalc += matrixCpy[i][k] * matrix2[k];
		}
		std::cout << "The solution we got: " << theSolWithCalc << std::endl;
		theSolWithCalc = 0;
	}

}

void Guassian::solveToZeros(int startingRow) {
	for (int i = startingRow; i<totalSize - 1; i++)            //g.elim
		for (int k = i + 1; k<totalSize; k++) {
			double t = matrix[k][i] / matrix[i][i];
			double q = matrix[k][i], p = matrix[i][i];
			for (int j = 0; j <= totalSize; j++) {
				//std::cout << "Operation (i= " << i << ") : matrix[k,j] ( " << matrix[k][j] << ") = " << matrix[k][j] << " - (" << q << " / " << p << ") that we get from pos (" << k << "," << i
					//<< ") and (" << i << "," << i << ") * " << matrix[i][j] << " that we get at pos (" << i << ", " << j << ")" << std::endl;
				matrix[k][j] = matrix[k][j] - t*matrix[i][j];

			}
		}

	for (int i = 0; i < totalSize; i++) {
		matrix2[i] = matrix[i][totalSize];
	}

	for (int i = totalSize - 1; i >= 0; i--) {                        //x is an array whose values correspond to the values of x,y,z..
		matrix2[i] = matrix[i][totalSize];                //lhs
		for (int j = 0; j<totalSize; j++)
			if (j != i)            //sub lhs values except the coefficient of the variable whose value    is being calculated
				matrix2[i] = matrix2[i] - matrix[i][j] * matrix2[j];
		matrix2[i] = matrix2[i] / matrix[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
	}

}



bool Guassian::calculateMatrix(){
	int tempk = 0;
	std::cout << "After pivot" << std::endl;
	for (int i = 0; i < totalSize; i++) {
		//Pivotisation
		tempk = i;
		// Finding the maximum head (pivot selection)
		for (int k = i + 1; k < totalSize; k++)
			if (matrix[i][i] < matrix[k][i])
				tempk = k;
		//Switch row
		for (int j = 0; j <= totalSize; j++)
		{
			double temp = matrix[i][j];
			matrix[i][j] = matrix[tempk][j];
			matrix[tempk][j] = temp;
		}
		//Modifying matrix w.r.t. pivot
		solveToZeros(i);
	}
	
	//Solve from bottom to upper.



 	printMatrix();
	
	std::cout << "PRINTING SOLUTIONS" << std::endl;

	for (int i = 0; i < totalSize; i++)
		std::cout << matrix2[i] << ", ";
	return false;
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
		this->matrixCpy = new double*[totalSize];
		int q = 0,i  = 0,b = 0;
		for (i; i < totalSize + 1; i++) {
			this->matrix[i] = new double[totalSize];
			this->matrixCpy[i] = new double[totalSize];
		}
		std::cout << "Matrix ** added with n*n->; " << totalSize << ". Starting to read values..." << std::endl;
		i = 0;

		while (!file.eof()) {
			while (q < totalSize+1) {
				file >> this->matrix[i][b++];
				matrixCpy[i][b-1] = matrix[i][b - 1];
				//std::cout << "Value read: " << matrix[i][b] << std::endl; 
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
