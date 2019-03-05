#include <iostream>
#include "Matrix.h"
using namespace std;
int main()
{
	//cout << "Input matrix dimension: ";
	//int n, m;
	//cin >> n >> m;
	//double default_val = 0.0;
	//Matrix A(n, m, default_val), B(n, m, default_val);
	
	//Matrix A(3, 3, 0.5);
	//cout << "Printing A...\n";
	//A.print();

	//Matrix B(2, 2, 0.5);
	//cout << "Printing B...\n";
	//B.print();

	//Matrix C = A + B;
	//cout << "Printing C = A + B...\n";
	//C.print();

	cout << "Input matrix dimension: ";
	int n, m;
	cin >> n >> m;
	double default_val = 0.0;
	Matrix A(n, m, default_val);

	for (unsigned int i = 0; i < n; ++i) {
		cout << "Row " << i << ": ";
		for (unsigned int j = 0; j < m; ++j) {
			double entry;
			cin >> entry;
			A.set(i, j, entry);
			cout << "i = " << i << ", j = " << j << endl;
			A.print();
		}
	}

	return 0;
}
