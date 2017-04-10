#ifndef _LaplaceOp1d_
#define _LaplaceOp1d_

#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"

/**
 *                       Class LaplaceOp1d
 *  A class whose apply member function implements the 3-point finite difference
 *  discrete  Laplace operator with homogeneous boundary conditions.
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
    with nx INTERIOR points that are spaced hx apart.

    Input  : UCLAQ::DoubleVector1d a vector of size m whose values are those of
             associated with the interior values of the discretization

    Output : The input vector is overwritten with the result

    If _DEBUG is defined at compile time, bounds checking is performed
    on operations associated on the UCLAQ::DoubleVector1d class, which
    is why there is no explicit bounds checking in this routine.
    */

    void apply(UCLAQ::DoubleVector1d& V)
    {
    Vtmp = V;

    long i;

    i = 0;
    V(i)   = alpha*((-2.0*Vtmp(i) + Vtmp(i+1))/(hx*hx));

    // Interior grid points not adjacent to the edge

    for(i = 1; i < nx-1; i++)
    {
    V(i) =  alpha*((Vtmp(i+1) - 2.0*Vtmp(i) + Vtmp(i-1))/(hx*hx));
    }

    i = nx-1;
    V(i) =  alpha*((-2.0*Vtmp(i) + Vtmp(i-1))/(hx*hx));

    }

    double         alpha; // Coefficient of the Laplace Operator
    double            hx; // Grid spacing in the x-direction
    long         xPanels; // Number of panels in the x-direction
    long              nx; // Number of unknowns in the x-direction

    UCLAQ::DoubleVector1d Vtmp; // Temporary
};

#endif /* LAPLACEOP1D_H_ */
