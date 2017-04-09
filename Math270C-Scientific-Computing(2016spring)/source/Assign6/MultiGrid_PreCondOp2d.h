/*
 * MultiGrid_PreCondOp2d.h
 *
 *  Created on: May 3, 2016
 *      Author: anderson
 */

#include "../DoubleVectorNd/UCLAQ_DoubleVector2d.h"
#include "../Assign4/MultiGridVcycle2d.h"

#ifndef _MultiGrid_PreCondOp2d_
#define _MultiGrid_PreCondOp2d_

/**
 *                       Class MultiGrid_PreCondOp2d
 *
 *  A class whose apply(...) member function implements M^(-1) associated with the
 *  a Multigrid V-cycle of a specified depth.
 *
 *  This class is based upon an underlaying MultiGridVcycle2d class whose apply(...) method implements
 *  one step of the MultiGridVcycle2d member function applyVcycle(...) starting with a
 *  starting iterate equal to the zero vector, and hence an approximate inverse map.
 *
 */
    
class MultiGrid_PreCondOp2d
{
public:

    MultiGrid_PreCondOp2d(){};

    MultiGrid_PreCondOp2d(int maxMultiGridLevel,long relaxationCount, double GJomega,double alpha, double xMin, double xMax,double yMin,double yMax,
    		int minMultiGridLevel = 0)
    {
    mgVcycle.initialize(maxMultiGridLevel,relaxationCount,GJomega, alpha, xMin, xMax,yMin,yMax,minMultiGridLevel);
    }

    void initialize(int maxMultiGridLevel,long relaxationCount, double GJomega,double alpha, double xMin, double xMax,double yMin,double yMax,
    		int minMultiGridLevel = 0)
    {
    mgVcycle.initialize(maxMultiGridLevel,relaxationCount,GJomega, alpha, xMin, xMax,yMin,yMax,minMultiGridLevel);
    }

    // Input  : V  = right hand side of the operator
    // Output : V overwritten with one V-cycle starting from an initial iterate of 0
    //
    // This apply(...) operator evaluates the approximate inverse map associated with
    // one step of a multi-grid V-cycle

    void apply(UCLAQ::DoubleVector2d& V)
    {
      mgVcycle.setRightHandSide(V);
      V.setToValue(0.0);
      mgVcycle.applyVcycle(V);
    }

    void setRelaxationParameter(double omega)
	{
	mgVcycle.setRelaxationParameter(omega);
	}


    MultiGridVcycle2d mgVcycle;
};


#endif  
