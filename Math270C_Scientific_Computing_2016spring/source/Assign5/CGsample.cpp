//
// CGsample
//
// This program uses Conjugate-Gradients to solve
//
//  D u = f
//
// where D is a diagonal operator with positive coefficients
//
// Test case currently implemented:
//
// The size of the system being solved is n X n
//
// D = diagonal operator with entries d_i = i+1  i = 0 .. n-1
// f = vector of all ones
//
// Assuming the 270C classes are contained in the sub-directory
// ../270C_Classes, the following commands can be used to compile
// this sample code.
//
// Debug mode with bounds checking:
//
// g++ -D_DEBUG -g CGsample.cpp -std=c++11 -I../270C_Classes -o CGsample.exe
//
// Release mode with O2 optimization:
//
// g++ -O2 CGsample.cpp -std=c++11 -I../270C_Classes -o CGsample.exe
//
//  Created for Math 270C : Chris Anderson 4/26/2016
//
#include <cstdio>
#include <iostream>
using namespace std;

#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"
#include "DiagOp.h"
#include "CGtemplate.h"

int main()
{
    
    long         n;
    double stopTol;
    long   maxIter = 1000;

    cout << "Enter dimension of system n: ";
    cin >> n;
    cout <<  "Enter stopping tolerance: ";
    cin >> stopTol;

// Echo input (using stdio since it's easier to create aligned output)

    printf("########   CG Iteration   ########\n");
    printf("System dimension     :  %-5ld   \n",n);
    printf("Stopping tolerance   :  %-10.5f \n",stopTol);
    printf("Maximum iterations   :  %-5ld  \n",maxIter);

// Initialize right hand side

    UCLAQ::DoubleVector1d  f(n);
    UCLAQ::DoubleVector1d  u(n);

    // Initialize operators

    DiagOp                diagOp;

    CGtemplate <UCLAQ::DoubleVector1d, DiagOp> cgOp;
    //                  |                 |
    //                  |                 |
    //          vector class        operator class
    //

    // Associate linear operator that cgOp is to use

    cgOp.setOperator(diagOp);

    // Specify iteration parameters and verbose flag

    cgOp.setExitTolerance(stopTol);
    cgOp.setIterationMax(maxIter);
    cgOp.setVerboseFlag();

    // Specify right hand side

    for(long i = 0; i < n; i++)
    {
        f(i) = 1.0;
    }

    // Specify starting iterate

    u.setToValue(0.0);

    // Solve the system

    cgOp.solve(f,u);

    // Extract parameters from the solution process

    long iterCount       = cgOp.getIterationCount();
    double finalResidual = cgOp.getRelativeResidualNorm();

    printf("Iterations         :  %-6ld  \n",iterCount);
    printf("CG residual        :  %10.5e \n",finalResidual);


    // Evaluate the actual error

    UCLAQ::DoubleVector1d uErr(n);

    for(long i = 0; i < n; i++)
    {
      uErr(i) = u(i) -1.0/(double)(i+1);
    }

    double errNorm;
    errNorm = uErr.norm2()/u.norm2();
    printf("Computed Error     :  %10.5e \n",errNorm);

}
