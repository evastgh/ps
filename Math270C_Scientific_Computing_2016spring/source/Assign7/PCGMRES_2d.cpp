#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

#include "../DoubleVectorNd/UCLAQ_DoubleVector2d.h"
#include "PCGMREStemplate.h"
#include "../Assign2/LaplaceOp2d.h"
#include "../Assign6/MultiGrid_PreCondOp2d.h"
#include "../Timing/ClockIt.h"

long PCGMREStest(long k, long subspaceSize, double stopTol = 1e-06, long maxIter = 20000, long relaxationCount = 2, double GJomega = 0.8)
{
    long maxMultiGridLevel = k+5, minMultiGridLevel = 0;
    long xPanels = pow(2, k+6), yPanels = pow(2, k+6);
    double alpha = -1.0;

    //   Problem set up

    double xMin = 0.0, xMax = 1.0;
    double yMin = 0.0, yMax = 1.0;
    double hx = (xMax-xMin)/(double)(xPanels);
    double hy = (yMax-yMin)/(double)(yPanels);

    // Echo input (using stdio since it's easier to create aligned output)
/*
    printf("########   GMRES Iteration   ########\n");
    printf("x in [%-6.3f, %-6.3f] \n", xMin, xMax);
    printf("y in [%-6.3f, %-6.3f] \n", yMin, yMax);
    printf("Number of x panels   : %-6ld   \n", xPanels);
    printf("Number of y panels   : %-6ld   \n", yPanels);
    printf("Stopping tolerance   : %-10.1e \n", stopTol);
    printf("Maximum iterations   : %-6ld  \n", maxIter);
    printf("Subspace size        : %-6ld  \n", subspaceSize);
*/
    // Initialize 1D laplace operator

    LaplaceOp2d  laplaceOp;
    laplaceOp.initialize(alpha,xPanels,hx,yPanels,hy);

    // Initialize pre-conditioner. In this case just
    // multi-grid pre-conditioner

    MultiGrid_PreCondOp2d mgVcycle;
    mgVcycle.initialize(maxMultiGridLevel, relaxationCount, GJomega, alpha, xMin, xMax, yMin, yMax, minMultiGridLevel);


    // Initialize right hand side and iterates

    long nx = xPanels-1, ny = yPanels-1;

    UCLAQ::DoubleVector2d f(nx, ny), u(nx, ny), uExact(nx, ny);

    // Create right hand side

    uExact.setToValue(1.0);
    f = uExact;
    laplaceOp.apply(f);

    // Set up GMRES template

    PCGMREStemplate < UCLAQ::DoubleVector2d, LaplaceOp2d, MultiGrid_PreCondOp2d > gmresOp;

    //                  |                        |                |
    //                  |                        |                |
    //           vector class              operator class   pre-conditioner operator class

    // Associate specific operators with the method

    gmresOp.setOperator(laplaceOp);
    gmresOp.setPreconditioner(mgVcycle);

    // Specify gmres parameters

    gmresOp.setSubspaceSize(subspaceSize);
//    gmresOp.setVerboseFlag();

    // Specify iteration parameters

    gmresOp.setExitTolerance(stopTol);
    gmresOp.setIterationMax(maxIter);

//  Solve the system

    gmresOp.solve(f,u);

 // Extract parameters from the solution process
/*
    long iterCount = gmresOp.getIterationCount();
    double finalResidual = gmresOp.getRelativeResidualNorm();
    printf("Iteration            : %-6ld \nGMRES residual       : %10.5e \n",iterCount,finalResidual);

    //
    // Evaluate the actual error
    //
    UCLAQ::DoubleVector2d  err(nx, ny);
    err = u - uExact;

    double errNorm;
    errNorm = err.norm2()/uExact.norm2();
    printf("Relative Error in Solution   : %10.5e \n",errNorm);
*/
    return gmresOp.getIterationCount();
}

int main(){
    long PCGMRESiterCount, N = 10;
    ClockIt GMRESclock;
    double GMREStime;

    ofstream outputFileStream;
    outputFileStream.open("PreCondGMRESTimingTest.csv");
    
    outputFileStream << " & 2 & 5 & 10 & 15 & 20 \\\\" << endl;
    for(long k=0; k<3; k++){
        GMRESclock.start();
        for(long i=0; i<N; i++) PCGMRESiterCount = PCGMREStest(k, 2);
        GMRESclock.stop();
        outputFileStream << k+5 << " & " << GMRESclock.getSecElapsedTime()/(double)N;
        for(long m=1; m<5; m++){
            GMRESclock.start();
            for(long i=0; i<N; i++) PCGMRESiterCount = PCGMREStest(k, m*5);
            GMRESclock.stop();
            outputFileStream << " & " << GMRESclock.getSecElapsedTime()/(double)N;
        }
        outputFileStream << "\\\\" << endl;
        cout << "Tests for grid size " << k+5 << " all done. " << endl;
    }
    
    outputFileStream.close();
    return 0;
}
