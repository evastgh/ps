
//                RelaxOp1D_Test.cpp
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
// g++ -D_DEBUG RelaxOp1d_Test.cpp -std=c++11 -I../270C_Classes -o RelaxOp1d_Test.exe
//
// Release mode with O2 optimization:
//
// g++ -O2 RelaxOp1d_Test.cpp -std=c++11 -I../270C_Classes -o RelaxOp1d_Test.exe
//
// Version: April 5, 2016

#include <cmath>
using namespace std;

#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"

#include "../Assign1/LaplaceOp1d.h"
#include "../Assign1/GaussJacobiOp1d.h"
#include "../Assign1/SORop1d.h"


int main()
{
    long            xPanels;
    double               kx;
    double omegaGaussJacobi;
    double         omegaSOR;

    cout << "Enter number of X-panels  : ";
    cin >> xPanels;

    cout << "Enter wave number         : ";
    cin >> kx;

    cout << "Enter Gauss-Jacobi relaxation parameter : ";
    cin >> omegaGaussJacobi;

    cout << "Enter SOR relaxation parameter : ";
    cin >> omegaSOR;
    
    double residualStopTolerance = 1.0e-03;

//   Problem set up. Unit domain.

    double xMin = 0.0;
    double xMax = 1.0;
    double LX   = (xMax-xMin);
    double hx   = (xMax-xMin)/(double)(xPanels);

    double pi     =  3.141592653589793238;
    double alpha  = -1.0;                                           // Coefficient of discrete Laplace operator

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

    // Instantiate operator

    LaplaceOp1d Lop1d(alpha, xPanels, hx);

    // Instantiate Gauss-Jacobi Operator

    GaussJacobiOp1d gjOp(alpha, xPanels, hx, omegaGaussJacobi);

    // Specify the right hand side and

    gjOp.setRightHandSide(f);

    // Relaxation loop with limiter on the number of iterations in
    // case a mistake has been made...

    long iterMaxCount   = 20000;
    long iterCount      = 0.0;
    double residualNorm = 1.0;

    u.setToValue(0.0);

    cout << endl << "XXXX  GaussJacobiOp1d  XXXX " << endl << endl;

    while((iterCount < iterMaxCount)&&(residualNorm > residualStopTolerance ))
    {
        gjOp.apply(u); // Apply one step of the Gauss-Jacobi operator

        // Compute the residual

        Lu = u;
        Lop1d.apply(Lu);
        residual = Lu - f;
        residualNorm = sqrt(hx)*residual.norm2();

        iterCount++;
        if(iterCount%50 == 0)
        {
        cout << "Iteration : " << iterCount << " Residual Norm : " << residualNorm << endl;
        }
    }

    cout << endl;
    cout << "XXXX  GaussJacobiOp1d Test Output XXXX "          << endl;

    cout << "X-Panel Count : " << xPanels << endl;
    cout << "X-Wavenumber  : " << kx << endl;
    cout << "Omega         : " << omegaGaussJacobi << endl;

    cout << "Gauss-Jacobi Iterations  = " << iterCount << endl;
    cout << "Residual norm (L2)       = " << sqrt(hx)*residual.norm2()  << endl;
    cout << "Residual norm (Inf)      = " << residual.normInf() << endl;
    cout << endl;

   // Instantiate SOR Operator

    SORop1d sorOp(alpha, xPanels, hx, omegaSOR);

    // Specify the right hand side and

    sorOp.setRightHandSide(f);

    // Relaxation loop with limiter on the number of iterations in
    // case a mistake has been made...

    iterMaxCount   = 20000;
    iterCount      = 0.0;
    residualNorm = 1.0;


    u.setToValue(0.0);


    cout << endl << "XXXX  SOR  XXXX " << endl << endl;

    while((iterCount < iterMaxCount)&&(residualNorm > residualStopTolerance ))
    {
        sorOp.apply(u); // Apply one step of the Gauss-Seidel operator

        // Compute the residual

        Lu = u;
        Lop1d.apply(Lu);
        residual = Lu - f;
        residualNorm = sqrt(hx)*residual.norm2();

        iterCount++;
        if(iterCount%50 == 0)
        {
        cout << "Iteration : " << iterCount << " Residual Norm : " << residualNorm << endl;
        }
    }

    cout << endl;
    cout << "XXXX  SORop1d Test Output XXXX "          << endl;

    cout << "X-Panel Count : " << xPanels << endl;
    cout << "X-Wavenumber  : " << kx << endl;
    cout << "Omega         : " << omegaSOR << endl;

    cout << "SOR Iterations           = " << iterCount << endl;
    cout << "Residual norm (L2)       = " << sqrt(hx)*residual.norm2()  << endl;
    cout << "Residual norm (Inf)      = " << residual.normInf() << endl;
} 
