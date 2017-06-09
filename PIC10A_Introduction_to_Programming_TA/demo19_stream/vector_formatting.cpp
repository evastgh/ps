#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;
int main() {
	// set up a random vector 
	srand(time(nullptr));
	size_t sizeVector = 10;
	vector<uint> randomVector(sizeVector); // use default constructor of uint and fill the vector
	cout << "Now starts generating the data. " << endl;
	for (size_t i = 0; i < sizeVector; ++i){
		randomVector[i] = rand() % 30;
		cout << randomVector[i] << endl;
	}

	ofstream fout;
	fout.open("random_data.txt");
	if (!fout.is_open()) {
		cout << "couldn't open file!" << endl;
	}

	cout << "Now starts storing the data. " << endl;
	for (size_t i = 0; i < sizeVector; ++i) {
		fout << randomVector[i] << endl;
	}
	fout.close();

	ifstream fin;
	fin.open("random_data.txt");

	cout << "Now starts restoring the data. " << endl;
	cout << fin; // fin will be casted to bool (it's current state!)
	vector<uint> readFromData(sizeVector);
	{
		size_t i = 0;
		while (fin >> readFromData[i]) {
			cout << readFromData[i] << endl;
			++i;
		}
	}
	cout << fin;
	// for (size_t i = 0; i < sizeVector; ++i){
	// 	fin >> readFromData[i];
	// 	cout << readFromData[i] << endl;
	// }
	fin.close();

	return 0;
}
