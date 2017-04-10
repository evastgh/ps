
//                MultiGrid1d.cpp
//
// Sample code that uses multigrid relaxation to solve
// the one dimensional Laplace equation.
//
// Assuming the 270C classes are contained in the sub-directory
// ../270C_Classes,  and LaplaceOp1d.h and GaussJacobi1d.h are contained in the
// directory ../Assign2, then the following commands can be used to compile
// this sample code.
//
// Debug mode with bounds checking:
//
// g++ -g -D_DEBUG MultiGrid1d.cpp -std=c++11 -I../270C_Classes -I../Assign2 -o MultiGrid1d.exe
//
// Release mode with O2 optimization:
//
// g++ -O2  MultiGrid1d.cpp -std=c++11 -I../270C_Classes  -I../Assign2  -o MultiGrid1d.exe
//
// Version: April 5, 2016

#include <cmath>
#include <functional>
using namespace std;

#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"

#include "../Assign1/LaplaceOp1d.h"
#include "MultiGridVcycle1d.h"

int main()
{
	int  maxMultiGridLevel;
    int  minMultiGridLevel;

    cout << "Enter maximal multi-grid level : ";
	cin >> maxMultiGridLevel;

	cout << "Enter minimal multi-grid level >= 0 : ";
	cin >> minMultiGridLevel;

    long   xPanels = pow(2,maxMultiGridLevel+1);

    double omegaGaussJacobi = 0.75;
    long   relaxationCount  = 2;
    double               kx = 1.0;

    double residualStopTolerance = 1.0e-03;

//   Problem set up. Unit domain.

    double xMin = 0.0;
    double xMax = 1.0;
    double LX   = (xMax-xMin);
    double hx   = (xMax-xMin)/(double)(xPanels);

    double pi     =  3.141592653589793238;
    double alpha  = -1.0;      // Coefficient of discrete Laplace operator

    // Create a right hand side vector

    long nx = xPanels - 1; // Number of x-coordinate values

    UCLAQ::DoubleVector1d         u(nx);   // Current iterate
    UCLAQ::DoubleVector1d        Lu(nx);   // For evaluation L(u)
    UCLAQ::DoubleVector1d         f(nx);
    UCLAQ::DoubleVector1d  residual(nx);

    double x;

    // Create a right hand side vector

    for(long i = 0; i < nx; i++)
    {
        x = xMin + (i+1)*hx;
        f(i) = cos(kx*pi*(x-xMin)/LX);
    }

    LaplaceOp1d       Lop1d(alpha, xPanels, hx);
    MultiGridVcycle1d mgVcycle(maxMultiGridLevel,relaxationCount,omegaGaussJacobi, alpha, xMin, xMax,minMultiGridLevel);
    mgVcycle.clearVerboseFlag(); // Use mgVcycle.setVerboseFlag() to turn on verbose output

    // Set right hand side an other parameters

    mgVcycle.setRightHandSide(f);

    // MultiGrid V-cycle loop with limiter on the number of iterations in
    // case a mistake has been made...

    long iterMaxCount   = 100;
    long iterCount      = 0.0;
    double residualNorm = 1.0;

    u.setToValue(0.0);

    cout << endl << "XXXX  MultiGrid1d  XXXX " << endl << endl;

    while((iterCount < iterMaxCount)&&(residualNorm > residualStopTolerance ))
    {
        mgVcycle.applyVcycle(u);

        // Compute the residual

        Lu = u;
        Lop1d.apply(Lu);
        residual = Lu - f;
        residualNorm = sqrt(hx)*residual.norm2();

        iterCount++;
        cout << "Vcycle : " << iterCount << " Residual Norm : " << residualNorm << endl;
    }

    cout << endl;
    cout << "XXXX  MultiGrid1d Test Output XXXX "       << endl;

    cout << "X-Panel Count    : " << xPanels << endl;
    cout << "X-Wavenumber     : " << kx << endl;
    cout << "Omega            : " << omegaGaussJacobi << endl;
    cout << "RelaxationCount  : " << relaxationCount << endl;

    cout << "MultiGrid V-cycles       = " << iterCount << endl;
    cout << "Residual norm (L2)       = " << sqrt(hx)*residual.norm2()  << endl;
    cout << "Residual norm (Inf)      = " << residual.normInf() << endl;
    cout << endl;


} 

