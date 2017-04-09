
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

#include "../DoubleVectorNd/UCLAQ_DoubleVector2d.h"
#include "../Assign2/LaplaceOp2d.h"
#include "CGtemplate.h"

bool CGTest(double stopTol, long maxIter, long xPanels, long yPanels)
{
    long nx = xPanels-1, ny = yPanels-1;
    double hx = 1.0/(double)xPanels, hy = 1.0/(double)yPanels;
    double alpha = -1.0;
    double M = (double)nx+1;
    double pi = 3.141592653589793238;
    double kappa = pow(sin((M-1)*pi/2/M), 2)/pow(sin(pi/2/M), 2);

    // Echo input (using stdio since it's easier to create aligned output)

    cout << endl << "########   CG Iteration   ########" << endl;
    cout << "Stopping tolerance   : " << stopTol << endl;
    cout << "Maximum iterations   : " << maxIter << endl;
    cout << "Grid size            : " << xPanels << " x " << yPanels << endl;
    cout << "Condition Number     : " << kappa << endl;

    // Initialize right hand side

    UCLAQ::DoubleVector2d f(nx, ny);
    UCLAQ::DoubleVector2d u(nx, ny);

    // Initialize operators

    LaplaceOp2d Lop2d(alpha,xPanels,hx,yPanels,hy);
    CGtemplate <UCLAQ::DoubleVector2d, LaplaceOp2d> cgOp;
    //                  |                 |
    //                  |                 |
    //          vector class        operator class
    //

    // Associate linear operator that cgOp is to use

    cgOp.setOperator(Lop2d);

    // Specify iteration parameters and verbose flag

    cgOp.setExitTolerance(stopTol);
    cgOp.setIterationMax(maxIter);
    cgOp.clearVerboseFlag();

    // [C0] Determine/specify right hand side 

    f.setToValue(1.0);
    Lop2d.apply(f);

    // Specify starting iterate

    u.setToValue(0.0);

    // Solve the system

    cgOp.solve(f,u);

    // Extract parameters from the solution process

    long iterCount = cgOp.getIterationCount();
    double finalResidual = cgOp.getRelativeResidualNorm();

    cout << "Iterations           : " << iterCount << endl;
    cout << "CG residual          : " << finalResidual << endl;
    cout << "Relative Error Bound : " << kappa*finalResidual << endl;

    // Evaluate the actual error

    UCLAQ::DoubleVector2d exactSol(nx,ny);
    exactSol.setToValue(1.0);
    u -= exactSol;

    double errNorm = u.norm2()/exactSol.norm2();
    cout << "Error                : " << errNorm << endl;

    if (errNorm < kappa*finalResidual)
        cout << "Relative Error Bound is valid. " << endl;
    else 
        cout << "Relative Error Bound is not valid. " << endl;

    return (errNorm < kappa*finalResidual);

}

int main(){
    double stopTol = 1e-6;
    long maxIter=1000;
    //bool err50 = CGTest(stopTol,  maxIter, 50, 50);
    //bool err100 = CGTest(stopTol, maxIter, 100, 100);
    //bool err200 = CGTest(stopTol, maxIter, 200, 200);
    bool err500 = CGTest(stopTol, maxIter, 500, 500);

}