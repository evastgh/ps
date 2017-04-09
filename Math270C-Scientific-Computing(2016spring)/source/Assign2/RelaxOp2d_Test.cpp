#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

#include "../DoubleVectorNd/UCLAQ_DoubleVector2d.h"

#include "LaplaceOp2d.h"         // Laplace operator class (From Assignment 1)
#include "GaussJacobiOp2d.h"     // Weighted Gauss-Jacobi
#include "SORop2d.h"             // SORop2d 

//                RelaxOp2D_Test.cpp
//
// Sample code that tests two relaxation methods, weighted Gauss-Jacobi
// and SOR using operator implementations.
//
// Assuming the 270C classes are contained in the sub-directory
// ../270C_Classes, the following commands can be used to compile
// this sample code.
//
// Debug mode with bounds checking:
//
// g++ -D_DEBUG RelaxOp2d_Test.cpp -std=c++11 -I../270C_Classes -o RelaxOp2d_Test.exe
//
// Release mode with O2 optimization:
//
// g++ -O2 RelaxOp2d_Test.cpp -std=c++11 -I../270C_Classes -o RelaxOp2d_Test.exe
//
// Version April 5, 2016

int main()
{
	double residualStopTolerance = 1.0e-03;
	long xPanels;
	long yPanels;

    double omegaGaussJacobi;
    double         omegaSOR;

	double    kx;
	double    ky;

	cout << "Enter number of X-panels: ";
	cin >> xPanels;

	cout << "Enter number of Y-panels: ";
	cin >> yPanels;

	cout << "Enter X-wave number       : ";
	cin >> kx;

	cout << "Enter Y-wave number       : ";
	cin >> ky;

    cout << "Enter Gauss-Jacobi relaxation parameter : ";
    cin >> omegaGaussJacobi;

    cout << "Enter SOR relaxation parameter : ";
    cin >> omegaSOR;


//   Problem set up. Unit domain.

	double xMin = 0.0;
	double xMax = 1.0;

	double yMin = 0.0;
	double yMax = 1.0;

	double LX   = (xMax-xMin);
	double hx   = (xMax-xMin)/(double)(xPanels);

	double LY   = (yMax-yMin);
	double hy   = (yMax-yMin)/(double)(yPanels);

	double pi     =  3.141592653589793238;

	double alpha  = -1.0;  // Coefficient of discrete Laplace operator


	// Create test vector consisting of the exact eigenvalue of the discrete operator.
	//
	// Note:  The x-coordinate evaluation starts at the first interior point

	long nx = xPanels - 1;
	long ny = yPanels - 1;


	UCLAQ::DoubleVector2d u(nx,ny);
	UCLAQ::DoubleVector2d Lu(nx,ny);
	UCLAQ::DoubleVector2d f(nx,ny);
	UCLAQ::DoubleVector2d residual(nx,ny);

	double x; double y;


	for(long i = 0; i < nx; i++){
	    for(long j = 0; j < ny; j++){
            x = xMin + (i+1)*hx;
            y = yMin + (j+1)*hy;
	        f(i,j) = cos(kx*pi*(x-xMin)/LX)*cos(ky*pi*(y-yMin)/LY);
        }
    }

	// Instantiate operator

	LaplaceOp2d Lop2d(alpha, xPanels, hx, yPanels, hy);

	// Instantiate Gauss-Jacobi Operator

    GaussJacobiOp2d gjOp(alpha, xPanels, hx, yPanels, hy, omegaGaussJacobi);

    // Specify the right hand side and
    gjOp.setRightHandSide(f);


    // Relaxation loop with limiter on the number of iterations in
    // case a mistake has been made...

    long iterMaxCount   = 20000;
    long iterCount      = 0.0;
    double residualNorm = 1.0;

    u.setToValue(0.0);
    gjOp.apply(u);

    while((iterCount < iterMaxCount)&&(residualNorm > residualStopTolerance ))
    {
    	gjOp.apply(u); // Apply one step of the Gauss-Jacobi operator

    	// Compute the residual

    	Lu = u;
    	Lop2d.apply(Lu);
    	residual = Lu - f;
    	residualNorm = sqrt(hx*hy)*residual.norm2();

    	iterCount++;
    	if(iterCount%50 == 0)
        {
//    	cout << "Iteration : " << iterCount << " Residual Norm : " << residualNorm << endl;
        }
    }

    cout << endl;
    cout << "XXXX  Gauss-Jacobi 2D Operator Test Output XXXX "          << endl;

    cout << "X-Panel Count : " << xPanels << endl;
    cout << "Y-Panel Count : " << yPanels << endl;
    cout << "X-Wavenumber  : " << kx << endl;
    cout << "Y-Wavenumber  : " << ky << endl;
    cout << "Omega         : " << omegaGaussJacobi << endl;

    cout << "Gauss-Jacobi Iterations  = " << iterCount << endl;
    cout << "Residual norm (L2)       = " << sqrt(hx*hy)*residual.norm2()  << endl;
    cout << "Residual norm (Inf)      = " << residual.normInf() << endl;
    cout << endl << endl;

    // Instantiate SOR Operator

    SORop2d sorOp(alpha, xPanels, hx, yPanels, hy, omegaSOR);

    // Specify the right hand side and

    sorOp.setRightHandSide(f);

    // Relaxation loop with limiter on the number of iterations in
    // case a mistake has been made...

    iterMaxCount   = 20000;
    iterCount      = 0.0;
    residualNorm = 1.0;

    u.setToValue(0.0);

    while((iterCount < iterMaxCount)&&(residualNorm > residualStopTolerance ))
    {
    	sorOp.apply(u); // Apply one step of the Gauss-Jacobi operator

    	// Compute the residual

    	Lu = u;
    	Lop2d.apply(Lu);
    	residual = Lu - f;
    	residualNorm = sqrt(hx*hy)*residual.norm2();

    	iterCount++;
    	if(iterCount%50 == 0)
        {
//    	cout << "Iteration : " << iterCount << " Residual Norm : " << residualNorm << endl;
        }
    }

    cout << endl;
    cout << "XXXX  SOR  2D Operator Test Output XXXX "          << endl;

    cout << "X-Panel Count : " << xPanels << endl;
    cout << "Y-Panel Count : " << yPanels << endl;
    cout << "X-Wavenumber  : " << kx << endl;
    cout << "Y-Wavenumber  : " << ky << endl;
    cout << "Omega         : " << omegaSOR << endl;

    cout << "SOR Iterations           = " << iterCount << endl;
    cout << "Residual norm (L2)       = " << sqrt(hx*hy)*residual.norm2()  << endl;
    cout << "Residual norm (Inf)      = " << residual.normInf() << endl;

}
