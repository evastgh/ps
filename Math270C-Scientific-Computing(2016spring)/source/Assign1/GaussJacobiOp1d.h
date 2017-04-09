/*
 * GaussJacobiOp1d.h
 *
 *  Created on: April 5, 2016
 *      Author: anderson
 */

#ifndef _GaussJacobiOp1d_
#define _GaussJacobiOp1d_

#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"

/**
 *                       Class GaussJacobiOp1d
 *
 *  A class whose apply member function implements a single step of
 *  weighted Gauss-Jacobi iteration to the 3-point discrete Laplace operator with
 *  homogeneous boundary conditions.
 *
 *  This class was created by modifying LaplaceOp1d, specifically
 *
 *  (*) A UCLAQ::DoubleVector1d data member, f,  was added to store the right hand side.
 *      Appropriate statements in the initialize routines were added to
 *      initialize this data member.
 *
 *  (*) A setRightHandSide(...) member function was added
 *
 *  (*) The apply() member function was modified to implement one step
 *      of weighted Gauss-Jacobi instead of the discrete Laplace operator.
 */

class GaussJacobiOp1d
{
public:

    GaussJacobiOp1d()
    {
    initialize();
    }

    virtual ~GaussJacobiOp1d()
    {}

    GaussJacobiOp1d(double alpha, long xPanels, double hx, double omega = 1.0)
    {
    initialize(alpha,xPanels,hx,omega);
    }

    void initialize(double alpha, long xPanels, double hx, double omega = 1.0)
    {
    this->alpha   = alpha;
    this->hx      = hx;
    this->xPanels = xPanels;
    this->nx  = xPanels-1;
    this->omega = omega;

    Vtmp.initialize(nx);
    }

    void initialize()
    {
    this->alpha   = 0.0;
    this->hx      = 0.0;
    this->xPanels = 0;
    this->nx  = 0;
    this->omega = 1.0;
    Vtmp.initialize();
    }

    void setRightHandSide(UCLAQ::DoubleVector1d& f)
    {
        this->f = f;
    }

    void setRelaxationParameter(double omega)
    {
        this->omega = omega;
    }


    /**
    This routine applies one step of weighted Gauss-Jacobi to the 3-point
    discrete Laplace operator interior grid points associated with a uniform discretization
    with nx INTERIOR points that are spaced hx apart.

    Input  : UCLAQ::DoubleVector1d a vector of size m whose values are those of
             associated with the interior values of the discretization

    Output : The input vector is overwritten with the result

    If _DEBUG is defined at compile time, bounds checking is performed
    on operations associated on the UCLAQ::DoubleVector1d class, which is why there is no explicit
    bounds checking in this routine.
    */

    void apply(UCLAQ::DoubleVector1d& V)
    {
    double vStar;

    Vtmp = V;
    long i;

    i = 0;
    vStar = 0.5*(Vtmp(i+1)  - ((hx*hx)/alpha)*f(i));
    V(i)  = omega*vStar + (1.0 - omega)*Vtmp(i);

    // Interior grid points not adjacent to the edge

    for(i = 1; i < nx-1; i++)
    {

     vStar = 0.5*(Vtmp(i+1) + Vtmp(i-1) - ((hx*hx)/alpha)*f(i));
     V(i)  = omega*vStar + (1.0 - omega)*Vtmp(i);
    }

    i = nx-1;
    vStar = 0.5*(Vtmp(i-1) - ((hx*hx)/alpha)*f(i));
    V(i)  = omega*vStar + (1.0 - omega)*Vtmp(i);

    }

    double         alpha; // Coefficient of the Laplace Operator
    double            hx; // Grid spacing in the x-direction
    long         xPanels; // Number of panels in the x-direction
    long              nx; // Number of unknowns in the x-direction

    UCLAQ::DoubleVector1d f;    // Right hand side
    UCLAQ::DoubleVector1d Vtmp; // Temporary

    double omega; // Relaxation factor
};



#endif /* _GaussJacobiOp1d_ */
