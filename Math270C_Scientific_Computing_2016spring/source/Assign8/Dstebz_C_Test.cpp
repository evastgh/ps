/*
 * Dstebz_C_Test.cpp
 *
 * A program that demonstrates the use of the Dstebz_C member function dstebz.
 *
 * In this program all of the eigenvalues of the 3-point finite difference
 * approximation to the operator
 *
 *              -Delta u
 *
 *  with homogeneous boundary conditions  u(xMin) = u(xMax) = 0
 *
 *  are computed, and the absolute error associated with each eigenvalue
 *  is evaluated and output.
 *
 *  External dependencies: Dstebz_C.h
 *
 *
 *  Assuming the Dstebz_C_Test.cpp and Dstebz_C.h are in the same directory
 *  the following commands can be used to compile this sample code.
 *
 * Debug mode
 *
 * g++ -D_DEBUG -g Dstebz_C_Test.cpp -std=c++11 -o Dstebz_C_Test.exe
//
// Release mode with O2 optimization:
//
// g++ -O2 Dstebz_C_Test.cpp -std=c++11 -o Dstebz_C_Test.exe
 *
 *  Created on: May 17, 2016
 *      Author: anderson
 */
    

#include <vector>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "Dstebz_C.h"

int main()
{
    long  n      = 20;            // System size

    // Set up vector of coefficients of symmetric tri-diagonal matrix corresponding
    // to 1D Laplace operator with homogeneous boundary conditions

    long xPanels = n+1;
    double xMin = 0.0;
    double xMax = 1.0;
    double LX   = (xMax-xMin);
    double hx   = (xMax-xMin)/(double)(xPanels);
    double pi     =  3.141592653589793238;

    vector<double> d(n, 2.0/(hx*hx));  // Diagonal elements
    vector<double> e(n,-1.0/(hx*hx));  // Upper diagonal elements

    char  range = 'A';    // Compute all eigenvalues
    char  order = 'E';    // Order eigenvalues from smallest to largest

    double vl    = 0.0;   // Lower interval bound. Not used if range = "A" or "I"
    double vu    = 0.0;   // Upper interval bound. Not used if range = "A" or "I"

    long   il    = 0;     // Low  index value. Not used if range = "A" or "V"
    long   iu    = 0;     // High index velue. Not used if range = "A" or "V"


    double absTol = 1.0e-08; // Absolute tolerance

    double*dptr   = &d[0];   // Pointer to diagonal values
    double*eptr   = &e[0];   // Pointer to upper diagonal values

    // Output data

    long m        = 0;           // Number of eigenvalues found
    long nsplit   = 0;           // Number of tri-diagonal blocks
    vector<double> w(n,0.0);     // Computed eigenvalues

    // Work arrays

    vector<long>   iblock(n,0);
    vector<long>   isplit(n,0);
    vector<double> work(4*n,0.0);
    vector<long>   iwork(3*n,0);

    // Information output

    long info = 0;

    // Declare instance of Dstebz_C

    Dstebz_C triEigRoutine;

    // The prototype for the Dstebz_C member function dstebz is

    /*

    int dstebz(char range, char order, long *n, double *vl, double *vu, long *il, long *iu,
    double *abstol, double *d__, double *e, long *m, long *nsplit, double *w, long *iblock,
    long *isplit, double *work, long *iwork, long *info)

    */

    // Invoke dstebz

    int dstebzReturn
    = triEigRoutine.dstebz(range,order,&n,&vl,&vu,&il,&iu,&absTol,dptr,eptr,&m,&nsplit,&w[0],&iblock[0],&isplit[0],&work[0], &iwork[0],&info);

    // Check routine error indicator

    if(info != 0)
    {
    cerr << "### Dstebz_C member function dstebz returned non-zero error code ###" << endl;
    cerr << "    Info value = " << info << endl;
    cerr << "    See dstebz.f documentation for interpretation " << endl;
    exit(1);
    }


    // Evaluate the error in the eigenvalues and print out the results

    double alpha  = -1.0;
    double lambda ;


    printf("\nXXX   Dstebz_C_Test XXX \n\n");
    printf("Specified tolerance : %10.5e \n",absTol);
    printf("System size : %ld \n\n",n);

    printf("Eigenvalue     Computed           Exact          Absolute Error \n");
    for(long i = 0; i < m; i++)
    {
        lambda = alpha*(2.0/(hx*hx))*(cos(((i+1)*pi*hx)/LX) - 1.0);
        printf("Eig : %2ld : %15.10e : %15.10e  : %10.5e  \n",i,w[i],lambda,fabs(lambda-w[i]));
    }

    return 0;
}



