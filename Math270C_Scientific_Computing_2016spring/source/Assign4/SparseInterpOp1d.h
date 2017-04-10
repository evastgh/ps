#ifndef _SparseInterpOp1d_
#define _SparseInterpOp1d_
/**
 * This class implements an operator such that :
 *
 * The applyProlongate member function interpolates the interior grid values associated
 * with a grid of uniform mesh width 2*hx to the interior grid values associated
 * with a grid of uniform mesh width hx.
 *
 * The applyRestriction member function is (1/2) the transpose of the prologation operator
 * and maps the interior grid values associated with a grid with hx mesh width
 * the the interior grid values associated with a mesh width 2*hx. This restriction operator
 * is known as the "full weighting scheme"
 *
 * Assumptions:
 *
 * The number panels associated with the grids whose values are being interpolated
 * is a power of 2.
 *
 * The grid function being interpolated satisfies homogeneous Dirichlet boundary
 * conditions, e.g. if the interpolacion formula for an interior grid point value
 * requires a value on the grid boundaries, then those required values are
 * assumed to be 0.
 *
 *
 * April 19, 2016
 * C. Anderson
 *
 */

#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"
#include "../SparseOp/SparseOp.h"

class SparseInterpOp1d
{
public:

	SparseInterpOp1d()
	{initialize();}

    SparseInterpOp1d(long fineGridLevel)
	{initialize(fineGridLevel);}

	void initialize()
	{
		fineGridLevel = -1;
		interpOp.initialize();
	}

	void initialize(long fineGridLevel)
	{
		this->fineGridLevel = fineGridLevel;

		long xPanelsFine   = pow(2,fineGridLevel+1);
		long xPanelsCoarse = xPanelsFine/2;

		// Set up sparse operator

		long pcg;  // Coarse grid panel index

		long ifg;  // Fine   grid value index
		long icg;  // Coarse grid value index

        //
		// Sparse matrix representation of an operator
		// from interior grid points of the coarse grid
		// to the interior grid points of the fine grid
		//

		interpOp.initialize(xPanelsFine-1,xPanelsCoarse-1);

		// This operator is set up by sweeping over the
		// coarse grid panels and initializing the left edge
		// and center of each panel

		// Leftmost panel

		pcg = 0;
		icg = pcg -1;
		ifg = 0;

        // vFine(ifg) = (vCoarse(icg+ 1))/2.0;

	    interpOp(ifg,icg+1) = 0.5;

	    // Interior panels

		for(pcg = 1; pcg < xPanelsCoarse-1; pcg++)
		{
			icg = pcg    -1;
			ifg = 2*pcg - 1;

			// vFine(ifg)  = vCoarse(icg)

			interpOp(ifg,icg) = 1.0;

			ifg += 1;

			// vFine(ifg) = (vCoarse(icg) + vCoarse(icg+ 1))/2.0;

			interpOp(ifg,icg)   = 0.5;
			interpOp(ifg,icg+1) = 0.5;
		}

		// Rightmost panel

		pcg = xPanelsCoarse-1;
	    icg = pcg   -1;
		ifg = 2*pcg -1;

		// vFine(ifg)  = vCoarse(icg)

		interpOp(ifg,icg) = 1.0;

		ifg += 1;

		// vFine(ifg) = (vCoarse(icg) + vCoarse(icg+ 1))/2.0;

		interpOp(ifg,icg)   = 0.5;

		interpOp.compact();
        interpOp.sortColumnIndices();
	}

	void applyProlongation(UCLAQ::DoubleVector1d& v2H, UCLAQ::DoubleVector1d& vH)
	{
		interpOp.apply(v2H,vH);
	}

    void applyRestriction(UCLAQ::DoubleVector1d& vH, UCLAQ::DoubleVector1d& v2H)
	{
		interpOp.applyTranspose(vH,v2H);
		v2H *= 0.5;
	}

	long                        fineGridLevel;
	SparseOp <UCLAQ::DoubleVector1d> interpOp;
};




#endif
