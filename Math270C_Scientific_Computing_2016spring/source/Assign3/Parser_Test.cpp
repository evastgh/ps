#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

int main()
{
	const long GJomegaCount = 10;
	const long SORomegaCount = 80;
	string GJdata [GJomegaCount];
	string SORdata [SORomegaCount];

	ifstream file;
	string omega;
	string rho;
	long i;

	const long N = 4;
	string readFileNameGJ[N] = {"GaussJacobi2d_Results_40iters.csv", "GaussJacobi2d_Results_400iters.csv", "GaussJacobi2d_Results_2000iters.csv", "GaussJacobi2d_Results_50x100grid.csv"};
	string readFileNameSOR[N] = {"SOR2d_Results_40iters.csv", "SOR2d_Results_400iters.csv", "SOR2d_Results_2000iters.csv", "SOR2d_Results_50x100grid.csv"};
	for(long k=0; k<N; k++){
		file.open(readFileNameGJ[k].c_str());
		i=0;
		while(file.good()){
			if(i >= GJomegaCount) break;
			getline(file, omega, ',');
			if(k==0){
				GJdata[i] = omega;
				GJdata[i] += ',';
			}
			getline(file, rho, '\n');
			GJdata[i] += rho;
			i++;
		}
		file.close();
		for(i=0; i<GJomegaCount; i++){
			GJdata[i] += ',';
		}

		file.open(readFileNameSOR[k].c_str());
		i=0;
		while(file.good()){
			if(i >= SORomegaCount) break;
			getline(file, omega, ',');
			if(k==0){
				SORdata[i] = omega;
				SORdata[i] += ',';
			}
			getline(file, rho, '\n');
			SORdata[i] += rho;
			i++;
		}
		file.close();
		for(i=0; i<SORomegaCount ; i++){
			SORdata[i] += ',';
		}
		
	}
/*
	cout << "here comes the result for GJ. \n";
	for(long i=0; i<GJomegaCount; i++){
		cout << GJdata[i] << endl;
	}
	cout << "here comes the result for SOR. \n";
	for(long i=0; i<SORomegaCount; i++){
		cout << SORdata[i] << endl;
	}*/

	ofstream outputFileStream;
	outputFileStream.open("GaussJacobi2d_Results_All.csv");
	for(i=0; i<GJomegaCount; i++){
		outputFileStream << GJdata[i] << endl;
	}
	outputFileStream.close();

	outputFileStream.open("SOR2d_Results_All.csv");
	for(i=0; i<SORomegaCount; i++){
		outputFileStream << SORdata[i] << endl;
	}
	outputFileStream.close();

	return 0;
}
