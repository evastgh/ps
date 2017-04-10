//
//######################################################################
//                       PCGMRES_sample.cpp
//
// A code demonstrates the use of the pre-conditioned GMRES(k) template
// to solve a linear system of equations arising from the
// discretization of the differential equation
// 
// -u_xx = f   for x in [0,1]
//
// The stopping condition used for this routine is that the relative
// size of the residual in the discrete L2 norm is less than the
// stopping tolerance.
//
// The pre-conditioner is a diagonal pre-conditioner.
//
// Math 270C                                                  5/9/2016
//######################################################################
//

#include <cmath>
#include <iostream>
using namespace std;

#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"
#include "PCGMREStemplate.h"

/**
 *                       Class LaplaceOp1d
 *  A class whose apply member function implements the 3-point finite difference
 *  discete  Laplace operator with homogeneous boundary conditions.
*/

class LaplaceOp1d
{
public:

    LaplaceOp1d()
    {
    initialize();
    }

    virtual ~LaplaceOp1d()
    {}

    LaplaceOp1d(double alpha, long xPanels, double hx)
    {
    initialize(alpha,xPanels,hx);
    }

    void initialize(double alpha, long xPanels, double hx)
    {
    this->alpha   = alpha;
    this->hx      = hx;
    this->xPanels = xPanels;
    this->nx  = xPanels-1;

    Vtmp.initialize(nx);
    }

    void initialize()
    {
    this->alpha   = 0.0;
    this->hx      = 0.0;
    this->xPanels = 0;
    this->nx  = 0;
    Vtmp.initialize();
    }

    /**
    This routine applies the 3-point discrete Laplace operator to
    the interior grid points associated with a uniform discretization
    with m INTERIOR points that are spaced hx apart.

    Input  : UCLAQ::DoubleVector1d a vector of size m whose values are those of
             associated with the interior values of the discretization

    Output : The input vector is overwritten with the result

    If _DEBUG is defined at compile time, bounds checking is performed
    on operations associated on the UCLAQ::DoubleVector1d class, which is why there is no explicit
    bounds checking in this routine.
    */

    void apply(UCLAQ::DoubleVector1d& V)
    {
    Vtmp = V;

    // Grid points adjacent to edge

    long i;

    i = 0;
    V(i)   = alpha*((-2.0*Vtmp(i) + Vtmp(i+1))/(hx*hx));

    i = nx-1;
    V(i) =  alpha*((-2.0*Vtmp(i) + Vtmp(i-1))/(hx*hx));

    // Interior grid points not adjacent to the edge

    for(i = 1; i < nx-1; i++)
    {
    V(i) =  alpha*((Vtmp(i+1) - 2.0*Vtmp(i) + Vtmp(i-1))/(hx*hx));
    }
    }

    double         alpha; // Coefficient of the Laplace Operator
    double            hx; // Grid spacing in the x-direction
    long         xPanels; // Number of panels in the x-direction
    long          nx; // Number of unknowns in the x-direction

    UCLAQ::DoubleVector1d Vtmp; // Temporary
};

// Pre-conditioner consisting of scalar multiplication.

class DiagPreConditioner
{
public:
	DiagPreConditioner()                 {dVal = 1.0;}
	DiagPreConditioner(double diagVal)  {dVal = diagVal;}
	void setDiagValue (double diagVal)  {dVal = diagVal;}

	void apply(UCLAQ::DoubleVector1d& V)
	{
		V *= dVal;
	}

	double dVal;
};

int main()
{
    long    xPanel;
    double stopTol;
    long   maxIter    = 10000;
    long subspaceSize = 0;
    double alpha      = -1.0;

    cout << "Enter number of panels:\n";
    xPanel = 64;
//    cin >> xPanel;
    cout <<  "Enter stopping tolerance:\n";
    stopTol = 1e-06;
//    cin >> stopTol;
    cout <<  "Enter subspace size:\n";
    subspaceSize = 4;
//    cin >> subspaceSize;

    //   Problem set up

    double xMin = 0.0;
    double xMax = 1.0;
    double hx   = (xMax-xMin)/(double)(xPanel);

    // Echo input (using stdio since it's easier to create aligned output)

    printf("########   GMRES Iteration   ########\n");
    printf("x in [%-6.3f, %-6.3f] \n",xMin, xMax);
    printf("Number of panels     :  %-5ld   \n",xPanel);
    printf("Stopping tolerance   :  %-10.5f \n",stopTol);
    printf("Maximum iterations   :  %-5ld  \n",maxIter);
    printf("Subspace size        :  %-5ld  \n",subspaceSize);

    // Initialize 1D laplace operator

    LaplaceOp1d  laplaceOp;
    laplaceOp.initialize(alpha, xPanel, hx);

    // Initialize pre-conditioner. In this case just
    // diagonal scaling.

    DiagPreConditioner    diagPreConditioner;
    diagPreConditioner.setDiagValue(hx*hx/2.0);

    // Initialize right hand side and iterates

    long n = xPanel - 1;

    UCLAQ::DoubleVector1d          f(n);
    UCLAQ::DoubleVector1d          u(n);
    UCLAQ::DoubleVector1d     uExact(n);

    // Create right hand side

    uExact.setToValue(1.0);
    f = uExact;
    laplaceOp.apply(f);

    // Set up GMRES template

    PCGMREStemplate < UCLAQ::DoubleVector1d, LaplaceOp1d, DiagPreConditioner > gmresOp;

    //                  |                        |                |
    //                  |                        |                |
    //           vector class              operator class   pre-conditioner operator class

    // Associate specific operators with the method

    gmresOp.setOperator(laplaceOp);
    gmresOp.setPreconditioner(diagPreConditioner);

    // Specify gmres parameters

    gmresOp.setSubspaceSize(subspaceSize);
    gmresOp.setVerboseFlag();

    // Specify iteration parameters


    gmresOp.setExitTolerance(stopTol);
    gmresOp.setIterationMax(20000);

//  Solve the system

    gmresOp.solve(f,u);

 // Extract parameters from the solution process

    long iterCount       = gmresOp.getIterationCount();
    double finalResidual = gmresOp.getRelativeResidualNorm();
    printf("Iteration %-6ld :  GMRES residual : %10.5e \n",iterCount,finalResidual);

    //
    // Evaluate the actual error
    //
    UCLAQ::DoubleVector1d  err(n);
    err = u - uExact;

    double errNorm;
    errNorm = err.norm2()/uExact.norm2();
    printf("Relative Error in Solution   :  %10.5e \n",errNorm);


    return 0;
}
