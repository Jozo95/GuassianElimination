#include "Guassian.h"

Guassian::Guassian(){
	this->matrix = new double*[10];
}

Guassian::Guassian(std::string filename){
	if (readFile(filename)) {
		printMatrix();
	}
	matrix2 = new double[totalSizeRow];
}

std::string Guassian::printMatrix()
{
	std::stringstream matrixPrint;
	matrixPrint.setf(4);


	matrixPrint << "-" << std::endl;
	for (int i = 0; i < totalSizeRow; i++) {
		matrixPrint <<  "|";
		for (int q = 0; q < totalSizeColumn; q++) {
			matrixPrint << " " << matrix[i][q] << ", ";
		}
		matrixPrint << " | " <<  matrix[i][totalSizeColumn] << " |" << std::endl;
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
	for (int i = 0; i < totalSizeRow; i++) {
		theSolution = matrixCpy[i][totalSizeColumn];
		std::cout << "The solution we need; " << theSolution << std::endl;
		for (int k = 0; k < totalSizeColumn; k++) {
			theSolWithCalc += matrixCpy[i][k] * matrix2[k];
		}
		std::cout << "The solution we got: " << theSolWithCalc << std::endl;
		theSolWithCalc = 0;
	}

}

bool Guassian::calculateMatrix(){
	int multiplier = -1;
	
	int startingPivotingIndex = totalSizeColumn - totalSizeRow;
	std::cout << "Starting Pivoting index: " << startingPivotingIndex << std::endl;
	std::cout << "After pivot" << std::endl;
	
	
	for (int i = 0; i < totalSizeRow; i++)                    //Pivotisation
		for (int k = i + 1;  k < totalSizeRow; k++)
			if (matrix[i][startingPivotingIndex] < matrix[k][startingPivotingIndex])
				for (int j = 0; j <= totalSizeColumn; j++)
				{
					double temp = matrix[i][j];
					matrix[i][j] = matrix[k][j];
					matrix[k][j] = temp;
				}

	printMatrix();


	/*
		int startingPivotingIndex = totalSizeColumn - totalSizeRow;
	std::cout << "Starting Pivoting index: " << startingPivotingIndex << std::endl;
	

	std::cout << "After pivot" << std::endl;
	
	int i, k, j, itrtor=1;
	for (i = 0; i < totalSizeRow-1; i++) {
		for (k = startingPivotingIndex; k < totalSizeColumn; k++) {
			if (matrix[i][i] < matrix[i + itrtor][k]) {
				for (int j = 0; j <= totalSizeColumn; j++) {
					double temp = matrix[i][j];
					matrix[i][j] = matrix[i + 1][j];
					matrix[i + 1][j] = temp;
					itrtor++;
				}
				itrtor = 0;
			}
			
		}
	}
	*/
    // TESTING WITH 1 - BITS, N - R PIVOTING
	


	/*std::cout << "After guass" << std::endl;
	for (int i = 0; i<totalSize - 1; i++)            //g.elim
		for (int k = i + 1; k<totalSize; k++){
			double t = matrix[k][i] / matrix[i][i];
			double q = matrix[k][i], p = matrix[i][i];
			for (int j = 0; j <= totalSize; j++) {
				std::cout << "Operation (i= " << i << ") : matrix[k,j] ( " << matrix[k][j] << ") = " << matrix[k][j] << " - (" << q << " / " <<  p << ") that we get from pos (" << k << "," << i
					<< ") and (" << i << "," << i << ") * " << matrix[i][j] << " that we get at pos (" << i << ", " << j << ")" << std::endl;
				matrix[k][j] = matrix[k][j] - t*matrix[i][j];    
				
			}
		}

	printMatrix();

	//std::cout << "After back-sub" << std::endl;
	//for (int i = totalSize - 1; i >= 0; i--) {
	//	matrix[i][totalSize] = matrix[i][totalSize] / matrix[i][i];
	//	matrix[i][i] = matrix[i][i] / matrix[i][i];
	//	
	//}
	
	
	for (int i = 0; i < totalSize; i++) {
		matrix2[i] = matrix[i][totalSize];
	}

	for (int i = totalSize - 1;  i >= 0; i--){                        //x is an array whose values correspond to the values of x,y,z..
		matrix2[i] = matrix[i][totalSize];                //lhs
		for (int j = 0; j<totalSize; j++)
			if (j != i)            //sub lhs values except the coefficient of the variable whose value    is being calculated
				matrix2[i] = matrix2[i] - matrix[i][j] * matrix2[j];
		matrix2[i] = matrix2[i] / matrix[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
	}

 	printMatrix();

	std::cout << "PRINTING SOLUTIONS" << std::endl;

	for (int i = 0; i < totalSize; i++)
		std::cout << matrix2[i] << ", ";*/
	return false;
}

bool Guassian::readFile(std::string filename)
{

	std::ifstream file;
	file.open(filename);
	if (file.is_open()) {
		std::cout << "File open, continueing" << std::endl;
		file >> totalSizeRow;
		file >> totalSizeColumn;
		std::cout << "N value; " << totalSizeRow << std::endl;

		std::cout << "N value; " << totalSizeColumn << std::endl;


		this->matrix = new double*[totalSizeRow];
		this->matrixCpy = new double*[totalSizeRow];
		int q = 0,i  = 0,b = 0;
		for (i; i < totalSizeRow + 1; i++) {
			this->matrix[i] = new double[totalSizeColumn];
			this->matrixCpy[i] = new double[totalSizeColumn];
		}
		std::cout << "Matrix ** added with r*n->; " << totalSizeRow << "; " << totalSizeColumn << ".Starting to read values..." << std::endl;
		i = 0;

		while (!file.eof()) {
			while (q < totalSizeColumn+1) {
				file >> this->matrix[i][b++];
				matrixCpy[i][b-1] = matrix[i][b - 1];
				//std::cout << "Value read: " << matrix[i][b-1] << std::endl; 
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
