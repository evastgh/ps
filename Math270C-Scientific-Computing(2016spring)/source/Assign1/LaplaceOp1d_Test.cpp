
//                LaplaceOp1d_Test.cpp
//
// Sample code that demonstrates the implementaiton of 
// a 1D discrete Laplace operator in  both the "operator" form 
// and as a sparse matrix.
//
//
// Assuming the 270C classes are contained in the sub-directory
// ../270C_Classes, the following commands can be used to compile
// this sample code.
//
// Debug mode with bounds checking:
//
// g++ -D_DEBUG LaplaceOp1d_Test.cpp -std=c++11 -I../270C_Classes -o LaplaceOp1d_Test.exe
//
// Release mode with O2 optimization:
//
// g++ -O2 LaplaceOp1d_Test.cpp -std=c++11 -I../270C_Classes -o LaplaceOp1d_Test.exe
//

#include <cmath>
using namespace std;


#include "DoubleVectorNd/UCLAQ_DoubleVector1d.h"
#include "SparseOp/SparseOp.h"

// Typically the following two classes would be specified in separate header
// files (e.g. LaplaceOp1d.h and IndexMap1d.h), but they are specified here
// so that one can quickly view their contents.
//

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
    on operations associated on the UCLAQ::DoubleVector1d class, which 
    is why there is no explicit bounds checking in this routine.
    */

    void apply(UCLAQ::DoubleVector1d& V)
    {
    Vtmp = V;

    long i;

    // Interior grid points not adjacent to the edge

    for(i = 1; i < nx-1; i++)
    {
    V(i) =  alpha*((Vtmp(i+1) - 2.0*Vtmp(i) + Vtmp(i-1))/(hx*hx));
    }

    // Grid points adjacent to edge

    i = 0;
    V(i)   = alpha*((-2.0*Vtmp(i) + Vtmp(i+1))/(hx*hx));

    i = nx-1;
    V(i) =  alpha*((-2.0*Vtmp(i) + Vtmp(i-1))/(hx*hx));

    }

    double         alpha; // Coefficient of the Laplace Operator
    double            hx; // Grid spacing in the x-direction
    long         xPanels; // Number of panels in the x-direction
    long          nx; // Number of unknowns in the x-direction

    UCLAQ::DoubleVector1d Vtmp; // Temporary
};

/**
 *                       Class IndexMap1d
 * This class maps the vector index associated with the grid data
 * values to the linear index associated with a matrix representation
 * of the operator.
 *
 */
class IndexMap1d
{
public :

    IndexMap1d(long xDim)
    {
    this->xDim = xDim;
    }

    // Returns the linear index associated with the matrix representation
    // based upon the vector index associated with the grid dadta values

    long linearIndex(long i)
    {
        return i;
    }

    long xDim;
};

int main()
{
    long xPanels;
    double    kx;

    cout << "Enter number of X-panels: ";
    cin >> xPanels;

    cout << "Enter wave number       : ";
    cin >> kx;

//   Problem set up. Unit domain.

    double xMin = 0.0;
    double xMax = 1.0;
    double LX   = (xMax-xMin);
    double hx   = (xMax-xMin)/(double)(xPanels);

    double pi     =  3.141592653589793238;

    double alpha  = -1.0;                                           // Coefficient of discrete Laplace operator
    double lambda = alpha*(2.0/(hx*hx))*(cos((kx*pi*hx)/LX) - 1.0); // Exact eigenvalue of discrete operator

    // Create test vector consisting of the exact eigenvalue of the discrete operator.
    // Note:  The x-coordinate evaluation starts at the first interior point

    long nx = xPanels - 1; // Number of x-coordinate values

    UCLAQ::DoubleVector1d v(nx);
    UCLAQ::DoubleVector1d vExact(nx);
    UCLAQ::DoubleVector1d vErr(nx);

    double x;
    for(long i = 0; i < nx; i++)
    {
        x = xMin + (i+1)*hx;
        v(i) = sin(kx*pi*(x-xMin)/LX);
    }


    // Instantiate operator

    LaplaceOp1d Lop1d(alpha, xPanels, hx);

    // Verify by checking operator on exact eigenvector of the discrete  operator.

    vExact = lambda*v;
    Lop1d.apply(v);

    // Check results(*)
    //
    // * Output a grid scaled L_2 norm so the norm is well-behaved
    //   as xPanels is increased.
    //

    vErr = vExact - v;

    cout << endl;
    cout << "XXXX  Laplacian 1D Operator Test Output XXXX "          << endl;

    cout << "X-Panel Count : " << xPanels << endl;
    cout << "X-Wavenumber  : " << kx << endl;

    cout << "L_2    Error in operator = " << sqrt(hx)*vErr.norm2()  << endl;
    cout << "L_Inf  Error in operator = " << vErr.normInf() << endl;

    //######################################################################
    //
    // Repeat the test using the M270::SparseOp sparse matrix representation
    // of the operator.
    //
    //######################################################################

    long n  = nx;  // Number of unknowns


    long   rowDimension  = n;
    long   colDimension  = n;

    SparseOp < UCLAQ::DoubleVector1d > sOp(rowDimension, colDimension);
    //                     |
    //  Vector class with pre-defined set of member functions.
    //  See comments in SparseOp.h for required member functions.
    //

    // Instantiate a class that maps indices from the vector of values associated
    // with the discretization to the linear index associated with the
    // matrix representation and the inverse of this mapping.

    IndexMap1d iMap(nx);

    long i;

    // Interior grid points not adjacent to the edge

    for(i = 1; i < nx-1; i++)
    {
    //V(i) =  alpha*((Vtmp(i+1) - 2.0*Vtmp(i) + Vtmp(i-1))/(hx*hx));
    sOp(iMap.linearIndex(i),iMap.linearIndex(i-1)) =  alpha*((1.0)/(hx*hx));
    sOp(iMap.linearIndex(i),iMap.linearIndex(i))   =  alpha*((-2.0)/(hx*hx));
    sOp(iMap.linearIndex(i),iMap.linearIndex(i+1)) =  alpha*((1.0)/(hx*hx));
    }

    // Edge points


    i = 0;

    // V(i)   = alpha*((-2.0*Vtmp(i) + Vtmp(i+1))/(hx*hx));
    sOp(iMap.linearIndex(i),iMap.linearIndex(i))   =  alpha*((-2.0)/(hx*hx));
    sOp(iMap.linearIndex(i),iMap.linearIndex(i+1)) =  alpha*((1.0)/(hx*hx));

    i = nx-1;

    //V(i) =  alpha*((-2.0*Vtmp(i) + Vtmp(i-1))/(hx*hx));
    sOp(iMap.linearIndex(i),iMap.linearIndex(i))   = alpha*((-2.0)/(hx*hx));
    sOp(iMap.linearIndex(i),iMap.linearIndex(i-1)) = alpha*((1.0)/(hx*hx));


    // Compact the data and then sort the column indices in each row to
    // improve performance of the apply operator (optional)

    sOp.compact();
    sOp.sortColumnIndices();

    // Create test vector for matrix representation

    UCLAQ::DoubleVector1d w(n);
    UCLAQ::DoubleVector1d wExact(n);
    UCLAQ::DoubleVector1d wErr(n);


    for(long i = 0; i < nx; i++)
    {
        x = xMin + (i+1)*hx;
        w(iMap.linearIndex(i)) = sin(kx*pi*(x-xMin)/LX);
    }

    wExact = lambda*w;
    sOp.apply(w);

    // Check results(*)
    //
    // * Output a grid scaled L_2 norm so the norm is well-behaved
    //   as xPanels is increased.
    //

    wErr = wExact - w;

    cout << endl;
    cout << "XXXX Laplacian 1D Matrix Test Output XXXX " << endl;

    cout << "X-Panel Count : " << xPanels << endl;
    cout << "X-Wavenumber  : " << kx << endl;

    cout << "L_2    Error in operator = " << sqrt(hx)*wErr.norm2()  << endl;
    cout << "L_Inf  Error in operator = " << wErr.normInf()         << endl;

}
