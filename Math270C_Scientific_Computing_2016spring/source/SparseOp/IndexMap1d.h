#ifndef _IndexMap1d_
#define _IndexMap1d_

/**
 *                       Class IndexMap1d
 * This class maps the vector index associated with rectangular grid data
 * values to the linear index associated with a matrix representation
 * of a linear operator on the grid data. 
 *
 */
class IndexMap1d
{
public :

/*! Constructs index map for a grid with xDim values in the first coordinate direction.
*/
    IndexMap1d(long xDim)
    {
    this->xDim = xDim;
    }

/*! Returns the linear index associated with the matrix representation
    based upon the vector index associated with the grid data values
*/
    long linearIndex(long i)
    {
        return i;
    }

/*! Sets i to be the vector index associated with the 
    linear index, k, of the matrix representation of the operator.  
*/
	void inverseIndex(long k, long& i)
	{
    i = k;
    } 

    long xDim;
};

#endif
