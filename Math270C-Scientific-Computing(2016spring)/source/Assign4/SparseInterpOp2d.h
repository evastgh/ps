#ifndef _SparseInterpOp2d_
#define _SparseInterpOp2d_
/**
 * This class implements a 2D operator such that :
 *
 * The applyProlongate member function interpolates the interior grid values associated
 * with a grid of uniform mesh widths (2*hx,2*hy) to the interior grid values associated
 * with a grid of uniform mesh widths (hx,hy).
 *
 * The applyRestriction member function is (1/4) the transpose of the prologation operator
 * and maps the interior grid values associated with a grid with (hx,hy) mesh widths
 * the the interior grid values associated with a mesh width (2*hx,2*hy). This prolongation
 * operator is called the "full weighting approximation"
 *
 * Assumptions:
 *
 * The number panels associated with the grids whose values are being interpolated
 * is a power of 2 in each direction.
 *
 * The grid function being interpolated satisfies homogeneous Dirichlet boundary
 * conditions, e.g. if the interpolacion formula for an interior grid point value
 * requires a value on the grid boundaries, then those required values are
 * assumed to be 0.
 *
 * April 19, 2016
 * C. Anderson
 *
 */

#include "../DoubleVectorNd/UCLAQ_DoubleVector2d.h"
#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"
#include "../SparseOp/SparseOp.h"
#include "../SparseOp/IndexMap2d.h"

class SparseInterpOp2d
{
public:

	SparseInterpOp2d()
	{initialize();}

    SparseInterpOp2d(long fineGridLevel)
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

		long yPanelsFine   = pow(2,fineGridLevel+1);
		long yPanelsCoarse = yPanelsFine/2;

		// 2D --> 1D index mapping

		IndexMap2d coarseMap(xPanelsCoarse-1,yPanelsCoarse-1);
		IndexMap2d   fineMap(xPanelsFine-1,  yPanelsFine-1);

		// Set up sparse operator

		long pcgX;  // X coarse grid panel index
		long pcgY;  // Y coarse grid panel index

		long ifg;  // Fine   grid value index
		long icg;  // Coarse grid value index


		long jfg;  // Fine   grid value index
		long jcg;  // Coarse grid value index
        //
		// Sparse matrix representation of an operator
		// from interior grid points of the coarse grid
		// to the interior grid points of the fine grid
		//

		interpOp.initialize((xPanelsFine-1)*(yPanelsFine-1),(xPanelsCoarse-1)*(yPanelsCoarse-1));

		vFine.initialize((xPanelsFine-1)*(yPanelsFine-1));
		vCoarse.initialize((xPanelsCoarse-1)*(yPanelsCoarse-1));
//
//      Sweep over coarse grid panel regions and create interpolation operator
//      coefficients for the points in the lower left corner. The value associated
//      with the lower left corner has coarse grid index (icg,jcg) and fine grid
//      index (ifg,jfg).
//
//
//		o-----x-----o
//		|     |     |
//		|     |     |
//		X-----X-----x
//      |     |     |
//      |     |     |
//      X-----X-----o
//   (ifg,jfg)
//   (icg,jcg)


		// Interior coarse grid panel blocks

		for(pcgX = 1; pcgX < xPanelsCoarse-1; pcgX++)
		{
		for(pcgY = 1; pcgY < yPanelsCoarse-1; pcgY++)
		{
			icg = pcgX    -1;
			jcg = pcgY    -1;

			ifg = 2*pcgX - 1;
			jfg = 2*pcgY - 1;

			// vFine(ifg,jfg)    = vCoarse(icg,jcg)

			interpOp(fineMap.linearIndex(ifg,jfg),coarseMap.linearIndex(icg,jcg)) = 1.0;

			// vFine(ifg+1,jfg)   = (vCoarse(icg+1,jcg) +  vCoarse(icg,jcg))/2.0;

			interpOp(fineMap.linearIndex(ifg+1,jfg),coarseMap.linearIndex(icg+1,jcg)) = 0.5;
			interpOp(fineMap.linearIndex(ifg+1,jfg),coarseMap.linearIndex(icg,jcg))   = 0.5;

			// vFine(ifg,jfg+1)   = (vCoarse(icg,jcg+1) +  vCoarse(icg,jcg))2.0;

			interpOp(fineMap.linearIndex(ifg,jfg+1),coarseMap.linearIndex(icg,jcg+1)) = 0.5;
			interpOp(fineMap.linearIndex(ifg,jfg+1),coarseMap.linearIndex(icg,jcg))   = 0.5;

			// vFine(ifg+1,jfg+1) = (vCoarse(icg+1,jcg+1) + vCoarse(icg,jcg+1) + vCoarse(icg+1,jcg) + vCoarse(icg,jcg)/)4.0;

		    interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg+1,jcg+1)) = 0.25;
			interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg,jcg))     = 0.25;

			interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg,jcg+1))   = 0.25;
			interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg+1,jcg))   = 0.25;

		}
		}

		// Left and right edge blocks excluding corners

        pcgX = 0;

		for(pcgY = 1; pcgY < yPanelsCoarse-1; pcgY++)
		{
			icg = pcgX    -1;
			jcg = pcgY    -1;

			ifg = 2*pcgX - 1;
			jfg = 2*pcgY - 1;

			// vFine(ifg+1,jfg)   = (vCoarse(icg+1,jcg) +  vCoarse(icg,jcg))/2.0;

			interpOp(fineMap.linearIndex(ifg+1,jfg),coarseMap.linearIndex(icg+1,jcg)) = 0.5;

			// vFine(ifg+1,jfg+1) = (vCoarse(icg+1,jcg+1) + vCoarse(icg,jcg+1) + vCoarse(icg+1,jcg) + vCoarse(icg,jcg)/)4.0;

		    interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg+1,jcg+1)) = 0.25;
			interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg+1,jcg))   = 0.25;
		}

	    pcgX = xPanelsCoarse-1;

		for(pcgY = 1; pcgY < yPanelsCoarse-1; pcgY++)
		{
			icg = pcgX    -1;
			jcg = pcgY    -1;

			ifg = 2*pcgX - 1;
			jfg = 2*pcgY - 1;

			// vFine(ifg,jfg)    = vCoarse(icg,jcg)

			interpOp(fineMap.linearIndex(ifg,jfg),coarseMap.linearIndex(icg,jcg)) = 1.0;

			// vFine(ifg+1,jfg)   = (vCoarse(icg+1,jcg) +  vCoarse(icg,jcg))/2.0;

			interpOp(fineMap.linearIndex(ifg+1,jfg),coarseMap.linearIndex(icg,jcg))   = 0.5;

			// vFine(ifg,jfg+1)   = (vCoarse(icg,jcg+1) +  vCoarse(icg,jcg))2.0;

			interpOp(fineMap.linearIndex(ifg,jfg+1),coarseMap.linearIndex(icg,jcg+1)) = 0.5;
			interpOp(fineMap.linearIndex(ifg,jfg+1),coarseMap.linearIndex(icg,jcg))   = 0.5;

			// vFine(ifg+1,jfg+1) = (vCoarse(icg+1,jcg+1) + vCoarse(icg,jcg+1) + vCoarse(icg+1,jcg) + vCoarse(icg,jcg)/)4.0;

			interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg,jcg))     = 0.25;
			interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg,jcg+1))   = 0.25;

		}

		// Bottom and top (excluding corners)

		pcgY = 0;

		for(pcgX = 1; pcgX < xPanelsCoarse-1; pcgX++)
		{
			icg = pcgX    -1;
			jcg = pcgY    -1;

			ifg = 2*pcgX - 1;
			jfg = 2*pcgY - 1;

			// vFine(ifg,jfg+1)   = (vCoarse(icg,jcg+1) +  vCoarse(icg,jcg))2.0;

			interpOp(fineMap.linearIndex(ifg,jfg+1),coarseMap.linearIndex(icg,jcg+1)) = 0.5;

			// vFine(ifg+1,jfg+1) = (vCoarse(icg+1,jcg+1) + vCoarse(icg,jcg+1) + vCoarse(icg+1,jcg) + vCoarse(icg,jcg)/)4.0;

		    interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg+1,jcg+1)) = 0.25;
			interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg,jcg+1))   = 0.25;
		}

		pcgY = yPanelsCoarse-1;
	    for(pcgX = 1; pcgX < xPanelsCoarse-1; pcgX++)
		{
			icg = pcgX    -1;
			jcg = pcgY    -1;

			ifg = 2*pcgX - 1;
			jfg = 2*pcgY - 1;

			// vFine(ifg,jfg)    = vCoarse(icg,jcg)

			interpOp(fineMap.linearIndex(ifg,jfg),coarseMap.linearIndex(icg,jcg)) = 1.0;

			// vFine(ifg+1,jfg)   = (vCoarse(icg+1,jcg) +  vCoarse(icg,jcg))/2.0;

			interpOp(fineMap.linearIndex(ifg+1,jfg),coarseMap.linearIndex(icg+1,jcg)) = 0.5;
			interpOp(fineMap.linearIndex(ifg+1,jfg),coarseMap.linearIndex(icg,jcg))   = 0.5;

			// vFine(ifg,jfg+1)   = (vCoarse(icg,jcg+1) +  vCoarse(icg,jcg))2.0;

			interpOp(fineMap.linearIndex(ifg,jfg+1),coarseMap.linearIndex(icg,jcg))   = 0.5;

			// vFine(ifg+1,jfg+1) = (vCoarse(icg+1,jcg+1) + vCoarse(icg,jcg+1) + vCoarse(icg+1,jcg) + vCoarse(icg,jcg)/)4.0;

			interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg,jcg))     = 0.25;
			interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg+1,jcg))   = 0.25;

		}

	    // Corners

	    // lower left

        pcgX = 0;
        pcgY = 0;

        icg = pcgX    -1;
        jcg = pcgY    -1;

        ifg = 2*pcgX - 1;
        jfg = 2*pcgY - 1;

        // vFine(ifg+1,jfg+1) = (vCoarse(icg+1,jcg+1) + vCoarse(icg,jcg+1) + vCoarse(icg+1,jcg) + vCoarse(icg,jcg)/)4.0;

        interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg+1,jcg+1)) = 0.25;


        // lower right

		pcgX = xPanelsCoarse-1;
		pcgY = 0;

		icg = pcgX    -1;
		jcg = pcgY    -1;
		ifg = 2*pcgX - 1;
		jfg = 2*pcgY - 1;

        // vFine(ifg,jfg+1)   = (vCoarse(icg,jcg+1) +  vCoarse(icg,jcg))2.0;

        interpOp(fineMap.linearIndex(ifg,jfg+1),coarseMap.linearIndex(icg,jcg+1)) = 0.5;

        // vFine(ifg+1,jfg+1) = (vCoarse(icg+1,jcg+1) + vCoarse(icg,jcg+1) + vCoarse(icg+1,jcg) + vCoarse(icg,jcg)/)4.0;

        interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg,jcg+1))   = 0.25;


        // Upper left

 		pcgX = 0;
		pcgY = yPanelsCoarse-1;

		icg = pcgX    -1;
		jcg = pcgY    -1;
		ifg = 2*pcgX - 1;
		jfg = 2*pcgY - 1;

        // vFine(ifg+1,jfg)   = (vCoarse(icg+1,jcg) +  vCoarse(icg,jcg))/2.0;

        interpOp(fineMap.linearIndex(ifg+1,jfg),coarseMap.linearIndex(icg+1,jcg)) = 0.5;

        // vFine(ifg+1,jfg+1) = (vCoarse(icg+1,jcg+1) + vCoarse(icg,jcg+1) + vCoarse(icg+1,jcg) + vCoarse(icg,jcg)/)4.0;

        interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg+1,jcg))   = 0.25;

        // Upper right

 		pcgX = xPanelsCoarse-1;
		pcgY = yPanelsCoarse-1;

		icg = pcgX    -1;
		jcg = pcgY    -1;
		ifg = 2*pcgX - 1;
		jfg = 2*pcgY - 1;

        // vFine(ifg,jfg)    = vCoarse(icg,jcg)
        interpOp(fineMap.linearIndex(ifg,jfg),coarseMap.linearIndex(icg,jcg)) = 1.0;

        // vFine(ifg+1,jfg)   = (vCoarse(icg+1,jcg) +  vCoarse(icg,jcg))/2.0;

        interpOp(fineMap.linearIndex(ifg+1,jfg),coarseMap.linearIndex(icg,jcg))   = 0.5;

        // vFine(ifg,jfg+1)   = (vCoarse(icg,jcg+1) +  vCoarse(icg,jcg))2.0;

        interpOp(fineMap.linearIndex(ifg,jfg+1),coarseMap.linearIndex(icg,jcg))   = 0.5;

        // vFine(ifg+1,jfg+1) = (vCoarse(icg+1,jcg+1) + vCoarse(icg,jcg+1) + vCoarse(icg+1,jcg) + vCoarse(icg,jcg)/)4.0;

        interpOp(fineMap.linearIndex(ifg+1,jfg+1),coarseMap.linearIndex(icg,jcg))     = 0.25;


		interpOp.compact();
        interpOp.sortColumnIndices();
	}

	void applyProlongation(UCLAQ::DoubleVector2d& v2H, UCLAQ::DoubleVector2d& vH)
	{
		vector1dFrom2d(v2H,vCoarse);
		interpOp.apply(vCoarse,vFine);
		vector2dFrom1d(vFine,vH);
	}

    void applyRestriction(UCLAQ::DoubleVector2d& vH, UCLAQ::DoubleVector2d& v2H)
	{
    	vector1dFrom2d(vH,vFine);
		interpOp.applyTranspose(vFine,vCoarse);
		vCoarse *= 1.0/4.0;
		vector2dFrom1d(vCoarse,v2H);
	}


	long                        fineGridLevel;
	SparseOp <UCLAQ::DoubleVector1d> interpOp;

	UCLAQ::DoubleVector1d vFine;
	UCLAQ::DoubleVector1d vCoarse;

	private:

	//
    // These internal utility routines assume that the dimension of the
    // 1d vector is equal to the number of values in the 2d vector
	//
	// These conversions can be implemented by swapping the data pointers of
	// the 1D and 2D vectors. I choose not to do this here to reduce
	// code obfuscation.

    void vector1dFrom2d(UCLAQ::DoubleVector2d& v2d,UCLAQ::DoubleVector1d& v1d)
    {
    	double* v2dDataPtr = v2d.getDataPointer();
    	for(long k = 0; k < v1d.getSize(); k++)
    	{
    		v1d(k) = v2dDataPtr[k];
    	}
    }

    void vector2dFrom1d(UCLAQ::DoubleVector1d& v1d,UCLAQ::DoubleVector2d& v2d)
    {
    	double* v2dDataPtr = v2d.getDataPointer();
    	for(long k = 0; k < v1d.getSize(); k++)
    	{
    		v2dDataPtr[k] = v1d(k);
    	}
    }
};




#endif
