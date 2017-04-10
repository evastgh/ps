#ifndef _LaplaceOp2d_
#define _LaplaceOp2d_

#include <cmath>
using namespace std;

#include "../DoubleVectorNd/UCLAQ_DoubleVector2d.h"
#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"
#include "../SparseOp/SparseOp.h"
#include "../SparseOp/IndexMap2d.h"

class LaplaceOp2d
{
public:

    LaplaceOp2d()
    {
    initialize();
    }

    virtual ~LaplaceOp2d()
    {}

    LaplaceOp2d(double alpha, long xPanels, double hx, long yPanels, double hy)
    {
    initialize(alpha,xPanels,hx,yPanels,hy);
    }

    void initialize(double alpha, long xPanels, double hx, long yPanels, double hy)
    {
    this->alpha   = alpha;
    this->hx      = hx;
    this->hy      = hy;
    this->xPanels = xPanels;
    this->yPanels = yPanels;
    this->nx  = xPanels-1;
    this->ny  = yPanels-1;

    Vtmp.initialize(nx,ny);
    }

    void initialize()
    {
    this->alpha   = 0.0;
    this->hx      = 0.0;
    this->hy      = 0.0;
    this->xPanels = 0;
    this->yPanels = 0;
    this->nx  = 0;
    this->ny  = 0;
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
    on operations associated on the UCLAQ::DoubleVector1d class, which 
    is why there is no explicit bounds checking in this routine.
    */

    void apply(UCLAQ::DoubleVector2d& V)
    {
    Vtmp = V;

    long i;
    long j;

    // Interior grid points not adjacent to the edge

    for(i = 1; i < nx-1; i++){
        for(j=1; j < ny-1; j++){
            V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));
        }
    }

    // Grid points adjacent to edge


    for(j=1; j < ny-1; j++){
        i = 0;
        V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));
        i = nx-1;
        V(i,j) =  alpha*(((-2.0)*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));
    }

    for(i=1; i < nx-1; i++){
        j = 0;
        V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j))/(hy*hy));
        j = ny-1;
        V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + ((-2.0)*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));    
    }

    i=0;
    j=0;
    V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j))/(hy*hy));

    i=nx-1;
    j=0;
    V(i,j) =  alpha*(((-2.0)*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j))/(hy*hy));

    i=0;
    j=ny-1;
    V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j))/(hx*hx) + ((-2.0)*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));

    i=nx-1;
    j=ny-1;
    V(i,j) =  alpha*(((-2.0)*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + ((-2.0)*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));



    }

    double         alpha; // Coefficient of the Laplace Operator
    double            hx; // Grid spacing in the x-direction
    double            hy;
    long         xPanels; // Number of panels in the x-direction
    long         yPanels;
    long          nx; // Number of unknowns in the x-direction
    long          ny;

    UCLAQ::DoubleVector2d Vtmp; // Temporary
};

#endif /* LAPLACEOP2D_H_ */