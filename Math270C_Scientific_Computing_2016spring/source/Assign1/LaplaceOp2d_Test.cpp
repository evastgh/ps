
#include <cmath>
using namespace std;


#include "../DoubleVectorNd/UCLAQ_DoubleVector2d.h"
#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"
#include "../SparseOp/SparseOp.h"
#include "../SparseOp/IndexMap2d.h"
#include "../Assign2/LaplaceOp2d.h"

int main()
{
    long xPanels;
    long yPanels;
    double    kx;
    double    ky;

    cout << "Enter number of X-panels: ";
    cin >> xPanels;

    cout << "Enter number of Y-panels: ";
    cin >> yPanels;

    cout << "Enter wave number for x : ";
    cin >> kx;
    cout << "Enter wave number for y : ";
    cin >> ky;

//   Problem set up. Unit domain.

    double xMin = 0.0;
    double xMax = 1.0;
    double yMin = 0.0;
    double yMax = 1.0;
    double LX   = (xMax-xMin);
    double LY   = (yMax-yMin);
    double hx   = (xMax-xMin)/(double)(xPanels);
    double hy   = (yMax-yMin)/(double)(yPanels);

    double pi     =  3.141592653589793238;

    double alpha  = -1.0;                                           // Coefficient of discrete Laplace operator
    double lambda = alpha*((2.0/(hx*hx))*(cos((kx*pi*hx)/LX) - 1.0)+(2.0/(hy*hy))*(cos((ky*pi*hy)/LY) - 1.0)); // Exact eigenvalue of discrete operator

    // Create test vector consisting of the exact eigenvalue of the discrete operator.
    // Note:  The x-coordinate evaluation starts at the first interior point

    long nx = xPanels - 1; // Number of x-coordinate values
    long ny = yPanels - 1;

    UCLAQ::DoubleVector2d v(nx,ny);
    UCLAQ::DoubleVector2d vExact(nx,ny);
    UCLAQ::DoubleVector2d vErr(nx,ny);

    double x;
    double y;
    for(long i = 0; i < nx; i++){
        for(long j=0; j < ny; j++){
            x = xMin + (i+1)*hx;
            y = yMin + (j+1)*hy;
            v(i, j) = sin(kx*pi*(x-xMin)/LX)*sin(ky*pi*(y-yMin)/LY);
        }
    }


    // Instantiate operator

    LaplaceOp2d Lop2d(alpha, xPanels, yPanels, hx, hy);

    // Verify by checking operator on exact eigenvector of the discrete  operator.

    vExact = lambda*v;
    Lop2d.apply(v);

    // Check results(*)
    //
    // * Output a grid scaled L_2 norm so the norm is well-behaved
    //   as xPanels is increased.
    //

    vErr = vExact - v;

    cout << endl;
    cout << "XXXX  Laplacian 2D Operator Test Output XXXX "          << endl;

    cout << "X-Panel Count : " << xPanels << endl;
    cout << "Y-Panel Count : " << yPanels << endl;
    cout << "X-Wavenumber  : " << kx << endl;
    cout << "Y-Wavenumber  : " << ky << endl;

    cout << "L_2    Error in operator = " << sqrt(hx)*vErr.norm2()  << endl;
    cout << "L_Inf  Error in operator = " << vErr.normInf() << endl;

    //######################################################################
    //
    // Repeat the test using the M270::SparseOp sparse matrix representation
    // of the operator.
    //
    //######################################################################

    long n  = nx*ny;  // Number of unknowns


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

    IndexMap2d iMap(nx,ny);

    long i;
    long j;

    // Interior grid points not adjacent to the edge

    for(i = 1; i < nx-1; i++){
        for(j = 1; j < ny-1; j++){
            // V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));
            sOp(iMap.linearIndex(i,j),iMap.linearIndex(i-1,j)) =  alpha*((1.0)/(hx*hx));
            sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j-1)) =  alpha*((1.0)/(hy*hy));
            sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j))   =  alpha*((-2.0)/(hx*hx)+(-2.0)/(hy*hy));
            sOp(iMap.linearIndex(i,j),iMap.linearIndex(i+1,j)) =  alpha*((1.0)/(hx*hx));
            sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j+1)) =  alpha*((1.0)/(hy*hy));
        }
    }

    // Edge points

    for(j=1; j < ny-1; j++){
        i = 0;
        // V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j-1)) =  alpha*((1.0)/(hy*hy));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j))   =  alpha*((-2.0)/(hx*hx)+(-2.0)/(hy*hy));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i+1,j)) =  alpha*((1.0)/(hx*hx));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j+1)) =  alpha*((1.0)/(hy*hy));
        i = nx-1;
        // V(i,j) =  alpha*(-2.0*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i-1,j)) =  alpha*((1.0)/(hx*hx));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j-1)) =  alpha*((1.0)/(hy*hy));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j))   =  alpha*((-2.0)/(hx*hx)+(-2.0)/(hy*hy));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j+1)) =  alpha*((1.0)/(hy*hy));
    }

    for(i=1; i < nx-1; i++){
        j = 0;
        // V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j))/(hy*hy));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i-1,j)) =  alpha*((1.0)/(hx*hx));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j))   =  alpha*((-2.0)/(hx*hx)+(-2.0)/(hy*hy));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i+1,j)) =  alpha*((1.0)/(hx*hx));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j+1)) =  alpha*((1.0)/(hy*hy));
        j = ny-1;
        // V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + (-2.0*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));    
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i-1,j)) =  alpha*((1.0)/(hx*hx));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j-1)) =  alpha*((1.0)/(hy*hy));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j))   =  alpha*((-2.0)/(hx*hx)+(-2.0)/(hy*hy));
        sOp(iMap.linearIndex(i,j),iMap.linearIndex(i+1,j)) =  alpha*((1.0)/(hx*hx));
    }

    i=0;
    j=0;
    // V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j))/(hy*hy));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j))   =  alpha*((-2.0)/(hx*hx)+(-2.0)/(hy*hy));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i+1,j)) =  alpha*((1.0)/(hx*hx));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j+1)) =  alpha*((1.0)/(hy*hy));

    i=nx-1;
    j=0;
    // V(i,j) =  alpha*(-2.0*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + (Vtmp(i,j+1) - 2.0*Vtmp(i,j))/(hy*hy));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i-1,j)) =  alpha*((1.0)/(hx*hx));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j))   =  alpha*((-2.0)/(hx*hx)+(-2.0)/(hy*hy));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j+1)) =  alpha*((1.0)/(hy*hy));

    i=0;
    j=ny-1;
    // V(i,j) =  alpha*((Vtmp(i+1,j) - 2.0*Vtmp(i,j))/(hx*hx) + (-2.0*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j-1)) =  alpha*((1.0)/(hy*hy));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j))   =  alpha*((-2.0)/(hx*hx)+(-2.0)/(hy*hy));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i+1,j)) =  alpha*((1.0)/(hx*hx));

    i=nx-1;
    j=ny-1;
    // V(i,j) =  alpha*(- 2.0*Vtmp(i,j) + Vtmp(i-1,j))/(hx*hx) + (-2.0*Vtmp(i,j) + Vtmp(i,j-1))/(hy*hy));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i-1,j)) =  alpha*((1.0)/(hx*hx));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j-1)) =  alpha*((1.0)/(hy*hy));
    sOp(iMap.linearIndex(i,j),iMap.linearIndex(i,j))   =  alpha*((-2.0)/(hx*hx)+(-2.0)/(hy*hy));



    // Compact the data and then sort the column indices in each row to
    // improve performance of the apply operator (optional)

//    sOp.compact();
//    sOp.sortColumnIndices();

    // Create test vector for matrix representation

    UCLAQ::DoubleVector1d w(n);
    UCLAQ::DoubleVector1d wExact(n);
    UCLAQ::DoubleVector1d wErr(n);


    for(long i = 0; i < nx; i++){
        for(long j = 0; j < ny; j++){
            x = xMin + (i+1)*hx;
            y = yMin + (j+1)*hy;
            w(iMap.linearIndex(i,j)) = sin(kx*pi*(x-xMin)/LX)*sin(ky*pi*(y-yMin)/LY);
        }
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
    cout << "XXXX Laplacian 2D Matrix Test Output XXXX " << endl;

    cout << "X-Panel Count : " << xPanels << endl;
    cout << "Y-Panel Count : " << yPanels << endl;
    cout << "X-Wavenumber  : " << kx << endl;
    cout << "Y-Wavenumber  : " << ky << endl;

    cout << "L_2    Error in operator = " << sqrt(hx)*wErr.norm2()  << endl;
    cout << "L_Inf  Error in operator = " << wErr.normInf()         << endl;

}
