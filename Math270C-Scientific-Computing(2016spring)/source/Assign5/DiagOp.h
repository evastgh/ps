#ifndef _DiagOp_
#define _DiagOp_
#include "../DoubleVectorNd/UCLAQ_DoubleVector1d.h"

//
// The apply operator of this class implements the operator w = D*v
// where v and w are UCLAQ::DoubleVector1d instances of dimension n
// and D is a diagonal matrix whose entries
//
// are d_i = i+1 where i = 0 ... n-1
//
// (Using C-style indexing for diagonal entries).
//
//
class DiagOp
{
public:

    DiagOp()
    {}

    void apply(UCLAQ::DoubleVector1d& V)
    {
    // capture V

    vTmp.initialize(V);

    for(long i = 0; i < V.getDimension(); i++)
    {
      V(i) = (double)(i+1)*vTmp(i);
    }
    }

    //  Temporary

    UCLAQ::DoubleVector1d vTmp;
};
#endif
