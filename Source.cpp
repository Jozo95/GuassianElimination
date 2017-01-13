
#include "Guassian.h"



int main(int argc, char** argv) {
	Guassian guassian = Guassian("test.txt");

	guassian.calculateMatrix();

	guassian.testTheValues();
	while (1) {

	}
	return 0;
}