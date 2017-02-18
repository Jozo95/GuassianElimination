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
		matrixPrint << "|";
		for (int q = 0; q < totalSizeColumn; q++) {
			matrixPrint << " " << matrix[i][q] << ", ";
		}
		matrixPrint << " | " << matrix[i][totalSizeColumn] << " |" << std::endl;
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
		theSolution = matrixCpy[i][totalSizeRow];
		std::cout << "The solution we need; " << theSolution << std::endl;
		for (int k = 0; k < totalSizeRow; k++) {
			theSolWithCalc += matrixCpy[i][k] * matrix2[k];
		}
		std::cout << "The solution we got: " << theSolWithCalc << std::endl;
		theSolWithCalc = 0;
	}

}

void Guassian::solveToZeros(int startingRow) {
	if (startingRow == -1){
		startingRow = totalSizeRow - 1;
	}


	for (int i = startingRow; i<totalSizeRow - 1; i++)            //g.elim
		for (int k = i + 1; k<totalSizeRow; k++) {
			double t = matrix[k][i] / matrix[i][i];
			double q = matrix[k][i], p = matrix[i][i];
			for (int j = 0; j <= totalSizeRow; j++) {
				//std::cout << "Operation (i= " << i << ") : matrix[k,j] ( " << matrix[k][j] << ") = " << matrix[k][j] << " - (" << q << " / " << p << ") that we get from pos (" << k << "," << i
					//<< ") and (" << i << "," << i << ") * " << matrix[i][j] << " that we get at pos (" << i << ", " << j << ")" << std::endl;
				matrix[k][j] = matrix[k][j] - t*matrix[i][j];
				if (matrix[k][j] < 0 || matrix[k][j] > 1)
					matrix[k][j] = 0;
			}
		}

	for (int i = 0; i < totalSizeRow; i++) {
		matrix2[i] = matrix[i][totalSizeRow];
	}

	for (int i = totalSizeRow - 1; i >= 0; i--) {                        //x is an array whose values correspond to the values of x,y,z..
		matrix2[i] = matrix[i][totalSizeRow];                //lhs
		for (int j = 0; j<totalSizeRow; j++)
			if (j != i)            //sub lhs values except the coefficient of the variable whose value    is being calculated
				matrix2[i] = matrix2[i] - matrix[i][j] * matrix2[j];
		matrix2[i] = matrix2[i] / matrix[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
	}

}

void Guassian::solveToZerosFromBottom(int startingRow) {
	for (int i = totalSizeRow-1; i>=0; i--)            //g.elim
		for (int k = i - 1; k >= 0; k--) {
			double t = matrix[k][i] / matrix[i][i];
			double q = matrix[k][i], p = matrix[i][i];
			for (int j = 0; j <= totalSizeRow; j++) {
				//std::cout << "Operation (i= " << i << ") : matrix[k,j] ( " << matrix[k][j] << ") = " << matrix[k][j] << " - (" << q << " / " << p << ") that we get from pos (" << k << "," << i
				//<< ") and (" << i << "," << i << ") * " << matrix[i][j] << " that we get at pos (" << i << ", " << j << ")" << std::endl;
				matrix[k][j] = matrix[k][j] - t*matrix[i][j];
				if (matrix[k][j] < 0 || matrix[k][j] > 1 )
					matrix[k][j] = 0;
			}
		}
	for (int i = 0; i < totalSizeRow; i++) {
		matrix2[i] = matrix[i][totalSizeRow];
	}
	for (int i = totalSizeRow - 1; i >= 0; i--) {                        //x is an array whose values correspond to the values of x,y,z..
		matrix2[i] = matrix[i][totalSizeRow];                //lhs
		for (int j = totalSizeRow-1; j >= 0 ; j--)
			if (j != i)            //sub lhs values except the coefficient of the variable whose value    is being calculated
				matrix2[i] = matrix2[i] - matrix[i][j] * matrix2[j];
		matrix2[i] = matrix2[i] / matrix[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
	}
}



bool Guassian::calculateMatrix(){
	int tempk = 0;
	std::cout << "After pivot" << std::endl;
	for (int i = 0; i < totalSizeRow; i++) {
		//Pivotisation
		tempk = i;
		// Finding the maximum head (pivot selection)
		for (int k = i + 1; k < totalSizeRow; k++)
			if (matrix[i][i] < matrix[k][i])
				tempk = k;
		//Switch row
		for (int j = 0; j <= totalSizeRow; j++)
		{
			double temp = matrix[i][j];
			matrix[i][j] = matrix[tempk][j];
			matrix[tempk][j] = temp;
		}
		//Modifying matrix w.r.t. pivot
		solveToZeros(i);
	}
	
	//Solve from bottom to upper.


	solveToZerosFromBottom(0);
 	printMatrix();
	
	std::cout << "PRINTING SOLUTIONS" << std::endl;

	for (int i = 0; i < totalSizeRow; i++)
		std::cout << matrix2[i] << ", ";
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
		int q = 0, i = 0, b = 0;
		for (i; i < totalSizeRow + 1; i++) {
			this->matrix[i] = new double[totalSizeColumn];
			this->matrixCpy[i] = new double[totalSizeColumn];
		}
		std::cout << "Matrix ** added with r*n->; " << totalSizeRow << "; " << totalSizeColumn << ".Starting to read values..." << std::endl;
		i = 0;

		while (!file.eof()) {
			while (q < totalSizeColumn + 1) {
				file >> this->matrix[i][b++];
				matrixCpy[i][b - 1] = matrix[i][b - 1];
				//std::cout << "Value read: " << matrix[i][b-1] << std::endl; 
				q++;
			}
			b = 0;
			q = 0;
			i++;
		}
		//std::cout << "VALLLLLLLL:" << matrix[0][totalSizeRow - 3];

		return true;
	}

	return false;
}
