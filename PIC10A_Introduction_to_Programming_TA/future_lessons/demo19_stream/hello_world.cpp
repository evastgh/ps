#include <iostream>
#include <fstream>

using namespace std;
int main() {
		ofstream fout;
		fout.open("Hello.txt", std::fstream::in | std::fstream::out | fstream::app);
		if (!fout.is_open()) {
				cout << "couldn't open file!" << endl;
		}
		fout << "Hello World!";
		fout.close();


		ifstream fin;
		fin.open("Hello.txt");
		string str;
		getline(fin, str);
		cout << str << endl;
		fin.close();
		
		return 0;
}
