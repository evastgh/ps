#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

#include "../DoubleVectorNd/UCLAQ_DoubleVector2d.h"
#include "../Assign2/LaplaceOp2d.h"
#include "MultiGridVcycle2d.h"


int MultiGrid2dTest(double omegaGaussJacobi, long relaxationCount){
	int maxMultiGridLevel = 7;
	int minMultiGridLevel = 0;

	long xPanels = pow(2, maxMultiGridLevel+1), yPanels = xPanels;
	long nx = xPanels-1, ny = yPanels-1;

	double kx = 1.0;
	double ky = 1.0;

	double residualStopTolerance = 1.0e-06;

	double xMin = 0.0, xMax = 1.0, LX = (xMax-xMin), hx = LX/(double)xPanels;
	double yMin = 0.0, yMax = 1.0, LY = (yMax-yMin), hy = LY/(double)yPanels;

	double pi = 3.141592653589793238;
	double alpha = -1.0;

	UCLAQ::DoubleVector2d u(nx, ny);
	UCLAQ::DoubleVector2d Lu(nx, ny);
	UCLAQ::DoubleVector2d f(nx, ny);
	UCLAQ::DoubleVector2d residual(nx, ny);

	double x, y;
	for(long i=0; i<nx; ++i){
		for(long j=0; j<ny; ++j){
			x = xMin + (i+1)*hx;
			y = yMin + (j+1)*hy;
			f(i, j) = cos(kx*pi*(x-xMin)/LX)*cos(kx*pi*(y-yMin)/LY);
		}
	}

	LaplaceOp2d Lop1d(alpha, xPanels, hx, yPanels, hy);
	MultiGridVcycle2d mgVcycle(maxMultiGridLevel, relaxationCount, omegaGaussJacobi,alpha,xMin,xMax,yMin,yMax,minMultiGridLevel);
	mgVcycle.clearVerboseFlag();
	mgVcycle.setRightHandSide(f);

	long iterMaxCount = 100;
	long iterCount = 0;
	double residualNorm = 1.0;

	u.setToValue(0.0);

//	cout << endl << "XXXX MultiGrid2d XXXX" << endl << endl;

	while((iterCount < iterMaxCount)&&(residualNorm > residualStopTolerance)){
		mgVcycle.applyVcycle(u);

		Lu = u;
		Lop1d.apply(Lu);
		residual = Lu - f;
		residualNorm = sqrt(hx)*residual.norm2();

		iterCount++;
		// cout << "Vcycle : " << iterCount << "Residual Norm : " << residualNorm << endl;
	}


/*
	cout << endl;
	cout << "XXXX MultiGrid2d Test Output XXXX" << endl;

	cout << "X-Panel Count    : " << xPanels << endl;
	cout << "Y-Panel Count 	  : " << yPanels << endl;
	cout << "X-Wavenumber     : " << kx << endl;
	cout << "Y-Wavenumber     : " << ky << endl;
	cout << "Omega            : " << omegaGaussJacobi << endl;
	cout << "RelaxationCount  : " << relaxationCount << endl;

	cout << "MultiGrid V-cycles       = " << iterCount << endl;
	cout << "Residual norm (L2)       = " << sqrt(hx)*residual.norm2()  << endl;
	cout << "Residual norm (Inf)      = " << residual.normInf() << endl;
	cout << endl;
*/
	cout << "Omega = " << omegaGaussJacobi << ", RelaxationCount = " << relaxationCount << "; V-cycles count: " << iterCount << "." << endl;
	return iterCount;
}

int main(){
	const long omegaTestSize = 9;
	const long relaxationCountTestSize = 5;
	double omega;
	long relaxationCount;

	ofstream outputFileStream;
	outputFileStream.open("MultiGrid2d_Results_maxlevel7.csv");

	for(long j=0; j<relaxationCountTestSize; ++j){
		relaxationCount = 2 + j;
		outputFileStream << '&' << relaxationCount;
	}
	for(long i=0; i<omegaTestSize; ++i){
		omega = 0.1+0.1*(double)i;
		outputFileStream << "\\\\" << endl << omega;
		for(long j=0; j<relaxationCountTestSize; ++j){
			relaxationCount = 2 + j;
			outputFileStream << '&' << relaxationCount*(MultiGrid2dTest(omega, relaxationCount));
		}	
	}
	/*
	outputFileStream << "Omega,RelaxationSetting,RelaxationCount" << endl;
	for(long i=0; i<omegaTestSize; ++i){
		omega = 0.1+0.1*(double)i;
		for(long j=0; j<relaxationCountTestSize; ++j){
			relaxationCount = 2 + j;
			outputFileStream << omega << ',' << relaxationCount << ',' << MultiGrid2dTest(omega, relaxationCount) << endl;
		}
	}
	*/
	outputFileStream.close();

}