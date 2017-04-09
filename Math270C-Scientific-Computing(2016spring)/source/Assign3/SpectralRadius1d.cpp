
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"
#include "../RandOpNd/RandVectorOp.h"

#include "GaussJacobiOp1d.h"     // Weighted Gauss-Jacobi
#include "SORop1d.h"             // SORop1d

//                SpectralRadius.cpp
//
// Sample code that estimates the spectral radius of weighted Gauss-Jacobi 
// and SOR for the 1d Laplace operator.
//
// We estimate the spectral radius using the power method.
//
// The estimate of the largest eigenvalue at step k is taken to be
//
// rho_estimage^k = sqrt(<A q^k, A q^k >) with the input q of unit length.
//
//
//
// Assuming the 270C classes are contained in the sub-directory
// ../270C_Classes, the following commands can be used to compile
// this sample code.
//
// Debug mode with bounds checking:
//
// g++ -D_DEBUG  SpectralRadius1d.cpp -std=c++11 -I../Assign2 -I../270C_Classes -o  SpectralRadius1d.exe
//
// Release mode with O2 optimization:
//
// g++ -O2  SpectralRadius1d.cpp -std=c++11  -I../Assign2 -I../270C_Classes -o  SpectralRadius1d.exe
//
// Version April 11, 2016

int main()
{
	bool verboseOutput  = true;    // If true print test results to screen

    long iterMaxCount   = 2000;      // Maximal number of power method iterations.

    double stopTol      = 1.0e-07; // Stop condition based upon difference of eigenvalues after each
                                   // power method iteration

    long   GJomegaCount = 10;      // Number of different values of omega to use for Gauss-Jacobi
    double GJomegaBegin = 0.1;     // Range of relaxation factors for weighted Gauss-Jacobi
    double GJomegaEnd   = 1.0;

    long   SORomegaCount = 80;     // Number of different values of omega to use for SOR
    double SORomegaBegin = 0.1;    // Range of relaxation factors for SOR
    double SORomegaEnd   = 1.98;

	long xPanels;

    xPanels = 50;

	/*
	cout << "Enter number of X-panels: ";
	cin >> xPanels;

    */

//   Problem set up. Unit domain.

	double xMin = 0.0;
	double xMax = 1.0;

	double LX   = (xMax-xMin);
	double hx   = (xMax-xMin)/(double)(xPanels);


	double alpha  = -1.0;  // Coefficient of discrete Laplace operator

	long nx = xPanels - 1;

    //  Variables used to implement power method iterations

	UCLAQ::DoubleVector1d u(nx);
	UCLAQ::DoubleVector1d q(nx);
    UCLAQ::DoubleVector1d Aq(nx);
	UCLAQ::DoubleVector1d f(nx);

    // Create initial random vector (using the same one for all estimates)
    // with unit l2 norm

    UCLAQ::RandVectorOp < UCLAQ::DoubleVector1d >  randVectorOp;
    //                              |
    //                        vector class

    UCLAQ::DoubleVector1d                     randVector(nx);

    randVectorOp.randomize(randVector);

    randVector  *= 1.0/randVector.norm2();

    double omega;
    double dOmega;

    double rho;
    double rhoDiff;
    double rhoKM1;

    long iterCount;

    if(verboseOutput)
    {
    	cout << endl;
    	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX " << endl;
        cout << "XXXXXXXX   Weighted Gauss-Jacobi  XXXXXXXX " << endl;
        cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX " << endl;
        cout << endl;
    }
    // Instantiate Gauss-Jacobi Operator

    GaussJacobiOp1d gjOp(alpha, xPanels, hx,1.0);

    // Specify f == 0 so apply operator implements the iteration matrix

    f.setToValue(0.0);
    gjOp.setRightHandSide(f);

    // Initialize loop over omega for Gauss-Jacobi

    dOmega  = (GJomegaEnd - GJomegaBegin)/(GJomegaCount-1);

    // Open up data file to output (omega,lamba) as comma separated values

    string dataFileName = "GaussJacobi_Results.csv";
    ofstream outputFileStream;
    outputFileStream.open(dataFileName.c_str());

    for(long omegaStep = 0; omegaStep < GJomegaCount; omegaStep++) // Set relaxation factor
    {
    // Set relaxation factor

    omega = GJomegaBegin + omegaStep*dOmega;
    gjOp.omega = omega;

    // Initialize power method variables. Use same starting vector for each omega

    q  = randVector;
    Aq = q; gjOp.apply(Aq);  // Apply iteration matrix

    rhoKM1 = 0.0;
    for(iterCount = 0; iterCount < iterMaxCount; iterCount++)    // Power method loop
    {
    u     = Aq;
    q     = u/u.norm2();

    Aq = q; gjOp.apply(Aq);           // Apply iteration matrix
    rho = Aq.norm2();                 // spectral radius approximation is (<A q^k , A q^k >)^(1/2)


    rhoDiff = abs(rho - rhoKM1)/(abs(rho) + 1.0); // Use relative magnitude to measure difference
    rhoKM1  = rho;

    if(rhoDiff < stopTol) break;
    }

    // save results to a file

    outputFileStream << omega << "," << rho << endl;

    if(verboseOutput)
    {
    cout <<  "Omega = " << omega << " rho = " << rho << " iterations = " << iterCount << " rho difference = " << rhoDiff <<  endl;
    }

    }

    // Close output file stream

    outputFileStream.close();

    if(verboseOutput)
    {
    	cout << endl;
    	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX " << endl;
    	cout << "XXXXXXXX          SOR             XXXXXXXX " << endl;
    	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX " << endl;
        cout << endl;
    }

    // Instantiate SOR Operator

    SORop1d sorOp(alpha, xPanels, hx, 1.0);

    // Specify f == 0 so apply operator implements the iteration matrix

    f.setToValue(0.0);
    sorOp.setRightHandSide(f);

    // Initialize loop over omega for SOR

    dOmega  = (SORomegaEnd - SORomegaBegin)/(SORomegaCount-1);

    // Re-open output file stream with another file name

    dataFileName = "SOR_Results1d.csv";
    outputFileStream.open(dataFileName.c_str());

    for(long omegaStep = 0; omegaStep < SORomegaCount; omegaStep++) // Loop over relaxation factor
    {

    // Set relaxation factor

    omega = SORomegaBegin + omegaStep*dOmega;
    sorOp.omega = omega;

    // Initialize power method variables. Use same starting vector for each omega

    q         = randVector;
    Aq        = q; sorOp.apply(Aq);    // Apply iteration matrix
    rhoKM1    = 0.0;

    for(iterCount = 0; iterCount < iterMaxCount; iterCount++)        // Power method loop
    {
    u     = Aq;
    q     = u/u.norm2();

    Aq  = q; sorOp.apply(Aq);    // Apply iteration matrix
    rho = Aq.norm2();            // spectral radius approximation is (<A q^k , A q^k >)^(1/2)


    rhoDiff = abs(rho - rhoKM1)/(abs(rho) + 1.0); // Use relative magnitude to measure difference
    rhoKM1  = rho;

    if(rhoDiff < stopTol) break;
    }

    // Save results to a file

    outputFileStream << omega << "," << rho << endl;

    if(verboseOutput)
    {
    cout <<  "Omega = " << omega << " rho = " << rho << " iterations = " << iterCount << " rho difference = " << rhoDiff <<  endl;
    }
    }

    // Close output file stream

    outputFileStream.close();

    cout << endl;

    cout << "Data file created : " << "GaussJacobi1d_Results.csv" << endl;
    cout << "Data file created : " << "SOR_Results1d.csv" << endl;

    cout << endl;
    cout << "XXXX Execution Completed XXXX " << endl;

}

