
#ifndef _SparseOp_
#define _SparseOp_

// Toggle off asserts if not in debug mode
#ifndef  _DEBUG
#define _NDEBUG
#endif

#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <vector>
#include <cstdlib>
using namespace std;


#define  INITIAL_ROWSIZE       10
#define  ROW_EXPANSION_FACTOR  2.0
//
//####################################################################
//                     SparseOp.h
//####################################################################
/*!
   \brief Sparse matrix representation of finite dimensional linear operators.

   This is not a general sparse matrix class, and it's primary purpose
   is to collect the non-zero entries of a matrix representation of the operator
   in such a way that the application of the operator to a one dimensional
   vector is carried out in a computationally efficient manner
   with minimal storage requirements.

   This class is templated with respect to a vector class <b>Vtype</b>.

   <b>Vtype</b> is a singly indexed vector class with (minimally) the following member functions:

   <pre>
   Vtype()                            (null constructor)
   initialize(const Vtype&)           (copy initializer)
   operator =                         (duplicate assignment)
   long getSize()                     (Returns the size (dimension) of the vector)
   </pre>

   Usage Notes:

   !!! Indexing starts at 0 for each matrix entry !!!

   Each row is repacked to an array of minimal size when consecutive calls to
   operator()(i,j) or setOperatorData(...) are called with row indices that differ.
   To avoid extraneous copying due to repacking, one should loop through the
   data assignment with the second index running the fastest, for example
   if S is the SparseOp instance then

   <pre>
   for(i = 0; i < N; i++)
   {
   for(j = 0; j < N; j++)
   {
     value =  *** computation of value ***

     S(i,j) = value;
   }}
   </pre>

   To improve performance by reducing the memory size and increasing locality of memory access,
   the member function compact() can be called followed by sortColumnIndices(). This combination
   of calls requires O(M) operations where M is the number of non-zero entries in the matrix.

   \author Chris Anderson (UCLA) Created for Math 270C from A fork of RC_SparseOp.h created by C. Anderson and R. Compton.
   \date   4/22/15
   \version 4.20.2016
*/

/*
#############################################################################
#
# Copyright 2016 Chris Anderson
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# For a copy of the GNU General Public License see
# <http://www.gnu.org/licenses/>.
#
#############################################################################
*/


template <class Vtype> class SparseOp
{
    
public :
SparseOp()
{
    rowCount       = 0;
    colCount       = 0;
    rowSizes       = 0;
    coeffValues    = 0;
    coeffColIndex  = 0;
    rowFilledSizes = 0;
    dropTol        = 0.0;
    
    colCount       = 0;

    initialRowSize     = INITIAL_ROWSIZE;
    rowExpansionFactor = ROW_EXPANSION_FACTOR;
    
    totalDataCount    =  0;
    totalDroppedCount =  0;
    totalInitialCount =  0;
    repackFlag        =  0;
    rowIndexCache     = -1;
}

/*!
Copy constructor. Create a duplicate instance.
*/
SparseOp(const SparseOp& S)
{
    rowCount       = 0;
    colCount       = 0;
    rowSizes       = 0;
    coeffValues    = 0;
    coeffColIndex  = 0;
    rowFilledSizes = 0;
    dropTol        = 0.0;

    initialRowSize     = INITIAL_ROWSIZE;
    rowExpansionFactor = ROW_EXPANSION_FACTOR;

    totalDataCount    =  0;
    totalDroppedCount =  0;
    totalInitialCount =  0;
    repackFlag        =  0;
    rowIndexCache     = -1;

    if((S.rowCount == 0)||(S.colCount == 0)) {return;}
    initialize(S);
}

/*!
Initialize an empty sparse representation of sparse matrix of size rowDimension X colDimension.
If a non-zero dropTolerance value is specified any element specified with an absolute value less
dropTolerance is ignored.
*/

SparseOp(long rowDimension, long colDimension, double dropTolerance = 0.0)
{
    this->rowCount   = 0;
    this->colCount   = 0;
    this->dropTol    = 0;
    rowSizes         = 0;
    coeffValues      = 0;
    coeffColIndex    = 0;
    rowFilledSizes   = 0;
    colCount         = 0;
    initialize(rowDimension, colDimension, INITIAL_ROWSIZE,ROW_EXPANSION_FACTOR,dropTolerance);
} 

/*!
Initialize an empty sparse representation of sparse matrix of size rowDimension X colDimension.
initialRowSize is an estimated number of non-zero elements per row. rowExpansionFactor, is the
multiplicative factor used to increase row storage, when the the allocated storage for a particular
row is exceeded.

If a non-zero dropTolerance value is specified any element specified with an absolute value less
dropTolerance is ignored.
*/

SparseOp(long rowDimension, long colDimension, long initialRowSize, double rowExpansionFactor,
double dropTolerance = 0.0)
{
    this->rowCount   = 0;
    this->colCount   = 0;
    this->dropTol    = 0;
    rowSizes         = 0;
    coeffValues      = 0;
    coeffColIndex    = 0;
    rowFilledSizes   = 0;
    colCount         = 0;
    initialize(rowDimension, colDimension, initialRowSize,rowExpansionFactor,dropTolerance);
} 


~SparseOp()
{
    destroyData();
}

/*!
Null initializer. All allocated memory is freed.
*/
void initialize()
{
    destroyData();
    rowCount       = 0;
    colCount       = 0;
    rowSizes       = 0;
    coeffValues    = 0;
    coeffColIndex  = 0;
    rowFilledSizes = 0;
    dropTol        = 0.0;
    
    initialRowSize     = INITIAL_ROWSIZE;
    rowExpansionFactor = ROW_EXPANSION_FACTOR;

    totalDataCount    =  0;
    totalDroppedCount =  0;
    totalInitialCount =  0;
    repackFlag        =  0;
    rowIndexCache     = -1;
}

/*!
Copy initializer. Initializes a duplicate instance.
*/
void initialize(const SparseOp& S)
{
    destroyData();
    if(S.rowCount == 0){initialize(); return;}

    rowCount             = S.rowCount;
    colCount             = S.colCount;
    rowSizes             = new long[rowCount];
    rowFilledSizes       = new long[rowCount];

    for(long i = 0; i < rowCount; i++)
    {
    rowSizes[i]       = S.rowFilledSizes[i];
    rowFilledSizes[i] = S.rowFilledSizes[i];
    }

    coeffValues       = new double*[rowCount];
    coeffColIndex     = new long*[rowCount];

    for(long i = 0; i < rowCount; i++)
    {
        coeffValues[i]   = new double[rowFilledSizes[i]];
        coeffColIndex[i] = new long[rowFilledSizes[i]];
    }
    //
    // Copy over data
    //
    for(long i = 0; i < rowCount; i++)
    {
    for(long k = 0; k < rowFilledSizes[i]; k++)
    {
    coeffValues[i][k]   = S.coeffValues[i][k];
    coeffColIndex[i][k] = S.coeffColIndex[i][k];
    }}


    totalDroppedCount =  S.totalDroppedCount;
    totalInitialCount =  S.totalInitialCount;
    rowIndexCache     = -1;
    repackFlag        =  0;

    dropTol            = S.dropTol;
    initialRowSize     = S.initialRowSize;
    rowExpansionFactor = S.rowExpansionFactor;
}


/*!
Initialize an empty sparse representation of sparse matrix of size rowDimension X colDimension.
If a non-zero dropTolerance value is specified any element specified with an absolute value less
dropTolerance is ignored.
*/


void initialize(long rowDimension, long colDimension, double dropTolerance = 0.0)
{
  initialize(rowDimension, colDimension, INITIAL_ROWSIZE,ROW_EXPANSION_FACTOR,dropTolerance);
}

/*!
Initialize an empty sparse representation of sparse matrix of size rowDimension X colDimension.
initialRowSize is an estimated number of non-zero elements per row. rowExpansionFactor, is the
multiplicative factor used to increase row storage, when the the allocated storage for a particular
row is exceeded.

If a non-zero dropTolerance value is specified any element specified with an absolute value less
dropTolerance is ignored.
*/

void initialize(long rowDimension, long colDimension, long initialRowSize, double rowExpansionFactor,
double dropTolerance = 0.0)
{
    destroyData();
  
    long i; 
    
    this->rowCount           = rowDimension;
    this->colCount           = colDimension;
    this->dropTol            = dropTolerance;
    this->initialRowSize     = initialRowSize;
    this->rowExpansionFactor = rowExpansionFactor;
    
    repackFlag      =  0;
    rowIndexCache   = -1;
    rowSizes        = new long[rowCount];
    rowFilledSizes  = new long[rowCount];
    
    coeffValues       = new double*[rowCount];
    coeffColIndex     = new long*[rowCount];
    
    for(i = 0; i < rowCount; i++)
    {
    rowSizes[i]       = initialRowSize;
    rowFilledSizes[i] = 0;
    coeffValues[i]      = new double[initialRowSize];
    coeffColIndex[i]    = new long[initialRowSize];
    }
    
    totalDataCount    = 0;
    totalDroppedCount = 0;
    totalInitialCount = 0;
}

/*!
Specifies the value of of the (rowIndex,colIndex) element of the matrix. Any existing value
is overwritten. If a non-zero value of dropTolerance is specified, then this operator is a no-op
when
<pre>
abs(coeffValue) < dropTolerance
</pre>
e.g. the value is ignored.
*/

void setOperatorData(long rowIndex, long colIndex, double coeffValue)
{
    // Bounds checking if _DEBUG defined

    assert(boundsCheck(rowIndex, 0, rowCount-1,1));
    assert(boundsCheck(colIndex, 0, colCount-1,2));

    long j;

    totalInitialCount += 1;
    if(rowIndexCache == -1) 
    {
      rowIndexCache = rowIndex;
    }
    
    if(fabs(coeffValue) < dropTol)
    {
        totalDroppedCount += 1;
        return;
    }
   
    //check if we are replacing an existing entry
    
    for(j = 0; j < rowFilledSizes[rowIndex]; j++)
    {
        if(colIndex == coeffColIndex[rowIndex][j]){
            coeffValues[rowIndex][j] = coeffValue;
            return;
        }
    }

    totalDataCount  += 1;
    long index = rowFilledSizes[rowIndex];

    if(index >= rowSizes[rowIndex]) 
    {
    	repackFlag = 0;
        resizeRow(rowIndex);
    }

    coeffValues[rowIndex][index]   = coeffValue;
    coeffColIndex[rowIndex][index] = colIndex;
    rowFilledSizes[rowIndex]++;

    //
    // Repack row if we've moved to a different row
    //
    if(rowIndex != rowIndexCache)
    {
       repackFlag = 1;
       resizeRow(rowIndexCache);
       rowIndexCache = rowIndex;
    }
}

/*!
    An inner class used to enable allocation and extraction of sparse matrix data utilizing
    SparseOp member function operator()(long row, long col).

    For example if the SparseOp instance is S, then to allocate
    and set the (i,j)th element one can use the syntax
    <pre>
    S(i,j) = 5.0;
    </pre>

    Similarly to extract a value, one can use

    <pre>
    z = S(i,j)
    </pre>

    If the (i,j)th value has been assigned a non-zero value, S(i,j) in this instance will
    return that value. If the (i,j)th value has not been assigned then a value of 0.0
    is returned.

    Additionally, the operators +=, -=, *=, and /= can be used in conjunction with double
    values, e.g.

    <pre>
    S(i,j) *= 5.0;
    </pre>

    Will multiply the (i,j)th element of the SparseOp instance by 5.0.


 */
class SparseOpRef
{
        public:

        /// Used for extraction of SparseOp element valu

        operator double() const
        {
            assert(sparseOpPtr->boundsCheck(i, 0, sparseOpPtr->rowCount-1,1));
            assert(sparseOpPtr->boundsCheck(j, 0, sparseOpPtr->colCount-1,2));

            for(long k = 0; k < sparseOpPtr->rowFilledSizes[i]; k++)
            {
                if(j == sparseOpPtr->coeffColIndex[i][k])
                {
                    return sparseOpPtr->coeffValues[i][k];
                }
            }
            return 0.0;
        }

        /// Used to insert or update a value into SparseOp instance

        void operator=(double value)
        {
            assert(sparseOpPtr->boundsCheck(i, 0, sparseOpPtr->rowCount-1,1));
            assert(sparseOpPtr->boundsCheck(j, 0, sparseOpPtr->colCount-1,2));

            sparseOpPtr->setOperatorData(i,j,value);
        }

        void operator+=(double value)
        {
            assert(sparseOpPtr->boundsCheck(i, 0, sparseOpPtr->rowCount-1,1));
            assert(sparseOpPtr->boundsCheck(j, 0, sparseOpPtr->colCount-1,2));

            double v  = sparseOpPtr->operator()(i,j);
                   v += value;

            sparseOpPtr->setOperatorData(i,j,v);
        }

        void operator-=(double value)
        {
            assert(sparseOpPtr->boundsCheck(i, 0, sparseOpPtr->rowCount-1,1));
            assert(sparseOpPtr->boundsCheck(j, 0, sparseOpPtr->colCount-1,2));

            double v  = sparseOpPtr->operator()(i,j);
                   v -= value;

            sparseOpPtr->setOperatorData(i,j,v);
        }

        void operator*=(double value)
        {
            assert(sparseOpPtr->boundsCheck(i, 0, sparseOpPtr->rowCount-1,1));
            assert(sparseOpPtr->boundsCheck(j, 0, sparseOpPtr->colCount-1,2));

            double v  = sparseOpPtr->operator()(i,j);
                   v *= value;

            sparseOpPtr->setOperatorData(i,j,v);
        }

        void operator/=(double value)
        {
            assert(sparseOpPtr->boundsCheck(i, 0, sparseOpPtr->rowCount-1,1));
            assert(sparseOpPtr->boundsCheck(j, 0, sparseOpPtr->colCount-1,2));

            double v  = sparseOpPtr->operator()(i,j);
                   v /= value;

            sparseOpPtr->setOperatorData(i,j,v);
        }

        long i; long j;
        SparseOp< Vtype >* sparseOpPtr;
};


/*!
When used to extract the (i,j)th element, the SparseOpRef
value returned is automatically converted to the (i,j)th value of the
SparseOp matrix. If the (i,j)th element of the SparseOp instance
has not been set, then the SparseOpRef is converted to the
value 0.0.

When used to assign the (i,j)th element, this member function
sets the (i,j)th element to the specified value.

If _DEBUG is defined then index bounds checking is performed.
*/

inline SparseOpRef  operator()( long i, long j )
{
    SparseOpRef S;

    S.i = i;
    S.j = j;
    S.sparseOpPtr = this;
    return S;
};

inline const SparseOpRef operator()( long i, long j ) const
{
    SparseOpRef S;

    S.i = i;
    S.j = j;
    S.sparseOpPtr = const_cast< SparseOp< Vtype >* >(this);
    return S;
};
/*!
This method overwrites the input vector instance V with the values of S*V
where S is this sparse operator instance. The row and column dimensions
of S must be equal.

If _DEBUG is defined then the required dimensional compatibility is checked.
*/
void apply(Vtype& V)
{
    assert(matrixVectorDimCheck(rowCount,colCount,V.getSize(), V.getSize()));

    vTmp.initialize(V); // initialize and copy V to vTmp

    long i; long j;
    for(i = 0; i < rowCount; i++)
    {
        V(i) = 0.0;
        for(j = 0; j < rowFilledSizes[i]; j++)
        {
            V(i) += vTmp(coeffColIndex[i][j])*coeffValues[i][j];
        }
    }
}


/*!
This method overwrites Vout with the values of S*Vin where S is this
sparse operator instance.


If _DEBUG is defined then the required dimensional compatibility is checked.
*/
void apply(const Vtype& Vin, Vtype& Vout) const
{
    assert(matrixVectorDimCheck(rowCount,colCount,Vin.getSize(), Vout.getSize()));

    long i; long j;
    for(i = 0; i < rowCount; i++)
    {
        Vout(i) = 0.0;
        for(j = 0; j < rowFilledSizes[i]; j++)
        {
            Vout(i) += Vin(coeffColIndex[i][j])*coeffValues[i][j];
        }
    }
}


/*!
This method overwrites the input vector instance V with the values of (transpose S)*V
where S is this sparse operator instance. The row and column dimensions
of S must be equal.

If _DEBUG is defined then the required dimensional compatibility is checked.
*/
void applyTranspose(Vtype& V)
{
    assert(matrixVectorDimCheck(rowCount,colCount,V.getSize(), V.getSize()));

    vTmp.initialize(V); // initialize and copy V to vTmp

    for(long i = 0; i < colCount; i++)
    {
    	V(i) = 0.0;
    }

    for(long i = 0; i < rowCount; i++)
    {
        for(long j = 0; j < rowFilledSizes[i]; j++)
        {
            V(coeffColIndex[i][j]) += vTmp(i)*coeffValues[i][j];
        }
    }
}


/*!
This method overwrites the vector instance Vout with the values of (transpose S)*Vin
where S is this sparse operator instance.

If _DEBUG is defined then the required dimensional compatibility is checked.
*/
void applyTranspose(const Vtype& Vin, Vtype& Vout) const
{
    assert(matrixVectorDimCheck(colCount,rowCount,Vin.getSize(), Vout.getSize()));

    for(long i = 0; i < colCount; i++)
    {
    	Vout(i) = 0.0;
    }

    for(long i = 0; i < rowCount; i++)
    {
        for(long j = 0; j < rowFilledSizes[i]; j++)
        {
            Vout(coeffColIndex[i][j]) += Vin(i)*coeffValues[i][j];
        }
    }
}



long getRowDimension() const {return rowCount;}
long getColDimension() const {return colCount;}



/*!
Returns the number of non-zero elements in the matrix
*/
long getTotalDataCount() const {return totalDataCount;}

/*!
Returns the number of non-zero elements that were ignored
*/
long getTotalDroppedCount() const {return totalDroppedCount;}


/*!
Returns the number of calls to the setOperatorData(...)
member function.
*/
long getTotalInitialCount() const {return totalInitialCount;}


/*!
Displays the matrix to the console.
The optional input format string specifies the format of a single entry using C printf output conventions.
 */

void printMatrix(std::string format = "%10.5e") const
{
    ostringstream  formatString(ostringstream::out);
    formatString.str(std::string());
    formatString << format << " ";

    // Get operator as a dense matrix
    //
    double* S  = new double[rowCount*colCount];
    getOperatorAsDenseMatrix(S);

    // Zero all entries

    long i; long j;
    for(i = 0; i < rowCount; i++)
    {
    for(j = 0; j < colCount; j++)
    {
    printf(formatString.str().c_str(), S[j+ i*colCount]);
    }
    printf("\n");
    }
    delete [] S;
}




/*!
The left hand side is initialized with the values of the right hand side.
If the left hand side is a null instance, then the left hand is initialized
as a duplicate.

If _DEBUG is defined then the required dimensional compatibility is checked when
the left hand side is a non-null instance.
*/

SparseOp& operator=(const SparseOp& rhs)
{
    if((rowCount == 0)||(colCount == 0))
    {
    this->initialize(rhs);
    return *this;
    }

    assert(matrixSumDimCheck(rowCount,colCount, rhs.rowCount, rhs.colCount));
    if(this == &rhs) return *this;
    this->initialize(rhs);
    return *this;
}


/*!
Incremental sum.

If _DEBUG is defined then the required dimensional compatibility is checked.
*/
SparseOp& operator+=(const SparseOp& rhs)
{
    assert(matrixSumDimCheck(rowCount,colCount, rhs.rowCount, rhs.colCount));
    long i,j;
    int jay;
    bool matched;

    for(i=0;i < rhs.rowCount; i++)
    {
        for(j = 0; j < rhs.rowFilledSizes[i]; j++)
        {
            //check if *this operator has a nonzero in the same place as the rhs operator
            matched = false;
            for(jay=0; jay < rowFilledSizes[i]; jay++)
                if(coeffColIndex[i][jay] == rhs.coeffColIndex[i][j]){
                    setOperatorData(i,coeffColIndex[i][jay],coeffValues[i][jay]+rhs.coeffValues[i][j]);
                    matched = true;
                    break;
                }
            if(!matched)
                setOperatorData(i,rhs.coeffColIndex[i][j],rhs.coeffValues[i][j]);
        }
    }
    return *this;
}

/*!
Returns sum of SparseOp instances.

If _DEBUG is defined then the required dimensional compatibility is checked.
*/
const SparseOp operator+(const SparseOp& rhs)const
{
    assert(matrixSumDimCheck(rowCount,colCount, rhs.rowCount, rhs.colCount));
    SparseOp result;
    result = *this;
    result += rhs;
    return result;
}

/*!
Incremental scalar multiplication
*/

SparseOp& operator*=(const double a)
{
    long i,j;
    for(i=0;i < rowCount; i++)
    {
        for(j = 0; j < rowFilledSizes[i]; j++)
        {
            setOperatorData(i,coeffColIndex[i][j], coeffValues[i][j]*a);
        }
    }
    return *this;
}


/*!
Scalar multiplication
*/
friend  SparseOp operator*(const double a, const SparseOp& X)
{
    SparseOp result;
    result = X;
    result *= a;
    return result;
}

/*!
Scalar multiplication
*/

const SparseOp operator*(const double a){
    SparseOp result;
    result = *this;
    result *= a;
    return result;
}

/*!
Returns the incremental difference.

If _DEBUG is defined then the required dimensional compatibility is checked.
*/

SparseOp& operator-=(const SparseOp& rhs)
{
    assert(matrixSumDimCheck(rowCount,colCount, rhs.rowCount, rhs.colCount));
    long i,j;
    int jay;
    bool matched;

    for(i=0;i < rhs.rowCount; i++)
    {
        for(j = 0; j < rhs.rowFilledSizes[i]; j++)
        {
            //check if *this operator has a nonzero in the same place as the rhs operator
            matched = false;
            for(jay=0; jay < rowFilledSizes[i]; jay++)
                if(coeffColIndex[i][jay] == rhs.coeffColIndex[i][j]){
                    setOperatorData(i,coeffColIndex[i][jay],coeffValues[i][jay]-rhs.coeffValues[i][j]);
                    matched = true;
                    break;
                }
            if(!matched)
                setOperatorData(i,rhs.coeffColIndex[i][j],-rhs.coeffValues[i][j]);
        }
    }
    return *this;

}

/*!
Returns the difference of two SparseOp instances.

If _DEBUG is defined then the required dimensional compatibility is checked.
*/
const SparseOp operator-(const SparseOp& rhs) const
{
    assert(matrixSumDimCheck(rowCount,colCount, rhs.rowCount, rhs.colCount));
    SparseOp result;
    result = *this;
    result -= rhs;
    return result;
}


/*!
Returns the incremental (matrix) product.

If _DEBUG is defined then the required dimensional compatibility is checked.
*/
SparseOp& operator*=(const SparseOp& rhs)
{

    long i,j,eye,jay;
    SparseOp result;
    double sum;

    assert(matrixMultDimCheck(rowCount,colCount, rhs.rowCount, rhs.colCount));

    result.initialize(rowCount, initialRowSize, rowExpansionFactor);

    for(i = 0; i < rowCount; i++){
        for(j = 0; j < rowCount; j++){
            sum = 0;
            for(eye = 0; eye < rowFilledSizes[i]; eye++){
                for(jay = 0; jay < rhs.rowFilledSizes[j]; jay++){
                    if(coeffColIndex[i][eye] == rhs.coeffColIndex[j][jay])
                        sum += coeffValues[i][eye] * rhs.coeffValues[j][jay];
                }
            }
            if(fabs(sum) > this->dropTol)
                result.setOperatorData(i,j,sum);
        }
    }
                
    *this = result;
    return *this;

}

/*!
Returns the (matrix) product of two SparseOp instances.

If _DEBUG is defined then the required dimensional compatibility is checked.
*/
const SparseOp operator*(const SparseOp& rhs) const
{
    assert(matrixMultDimCheck(rowCount,colCount, rhs.rowCount, rhs.colCount));
    SparseOp result;
    result = *this;
    result *= rhs;
    return result;
}


/*!
This method initializes the input SparseOp argument with the transpose
of the invoking instance.
*/

void createTranspose(SparseOp& S) const
{
	S.initialize();

    S.rowCount = colCount;
    S.colCount = rowCount;

    S.rowSizes        = new long[S.rowCount];
    S.rowFilledSizes  = new long[S.rowCount];


    // Capture the number of non-zero elements in each
    // row of the transpose

    for(long i = 0; i < S.rowCount; i++)
    {
    	S.rowSizes[i]       = 0;
    	S.rowFilledSizes[i] = 0;
    }


    for(long i = 0; i < rowCount; i++)
    {
    for(long k = 0; k < rowFilledSizes[i]; k++)
    {
    	S.rowSizes[coeffColIndex[i][k]] += 1;
    }}

    // Allocate arrays to store row data for the transpose

    S.coeffValues       = new double*[S.rowCount];
    S.coeffColIndex      = new long*[S.rowCount];

    for(long i = 0; i < S.rowCount; i++)
    {
        S.coeffValues[i]  = new double[S.rowSizes[i]];
        S.coeffColIndex[i] = new long[S.rowSizes[i]];
    }


    long colInsertIndex;
    long transposeRowIndex;

    // Copy over transpose data

    S.totalDataCount = 0;

    for(long i = 0; i < rowCount; i++)
    {
    for(long k = 0; k < rowFilledSizes[i]; k++)
    {
    	transposeRowIndex  = coeffColIndex[i][k];
    	colInsertIndex     = S.rowFilledSizes[transposeRowIndex];
    	S.coeffValues[transposeRowIndex][colInsertIndex]  = coeffValues[i][k];
    	S.coeffColIndex[transposeRowIndex][colInsertIndex] = i;
    	S.rowFilledSizes[transposeRowIndex] += 1;
    	S.totalDataCount += 1;
    }}


    S.totalDroppedCount =  0;
    S.totalInitialCount =  0;
    S.rowIndexCache     = -1;
    S.repackFlag        =  0;

    S.dropTol            = dropTol;
    S.initialRowSize     = initialRowSize;
    S.rowExpansionFactor = rowExpansionFactor;
}

/*!
This method initializes the input SparseOp argument with the lower triangular
component of the invoking instance, e.g. e.g. the L part of the decomposition
A = L + D + U

The diagonal is NOT included,
*/
void createLowerTriComponent(SparseOp& L)
{
	L.initialize();
	L.initialize(this->rowCount, this->colCount);

    long i; long j; long  jIndex;

    for(i = 0; i < rowCount; i++)
    {
        for(j = 0; j < rowFilledSizes[i]; j++)
        {
            jIndex = coeffColIndex[i][j];
            if(jIndex <  i) L(i,jIndex) = coeffValues[i][j];
        }
    }
    L.compact();
    L.sortColumnIndices();
}
/*!
This method initializes the input SparseOp argument with the upper triangular
component of the invoking instance, e.g. e.g. the U part of the decomposition
A = L + D + U

The diagonal is NOT included,
*/
void createUpperTriComponent(SparseOp& U)
{
	U.initialize();
	U.initialize(this->rowCount, this->colCount);

    long i; long j; long  jIndex;

    for(i = 0; i < rowCount; i++)
    {
        for(j = 0; j < rowFilledSizes[i]; j++)
        {
            jIndex = coeffColIndex[i][j];
            if(jIndex > i) U(i,jIndex) = coeffValues[i][j];
        }
    }

    U.compact();
    U.sortColumnIndices();
}

/*!
This method initializes the input SparseOp argument with the diagonal
component of the invoking instance, e.g. e.g. the D part of the decomposition
A = L + D + U
*/
void createDiagComponent(SparseOp& D)
{
	D.initialize();
	D.initialize(this->rowCount, this->colCount);

    long i; long j; long  jIndex;

    for(i = 0; i < rowCount; i++)
    {
        for(j = 0; j < rowFilledSizes[i]; j++)
        {
            jIndex = coeffColIndex[i][j];
            if(jIndex == i) D(i,jIndex) = coeffValues[i][j];
        }
    }
    D.compact();
    D.sortColumnIndices();
}

/*!
This method overwrites the input vector instance V with the solution of
the linear system associated with the lower triangular part of S that includes
the diagonal. The values in the upper triangular part of S, excluding the
diagonal,  are ignored.

This method assumes that all diagonals of the matrix are non-zero.


If _DEBUG is defined then the required dimensional compatibility is checked
*/
void applyLowerTriInverse(Vtype& V)
{
#ifdef _DEBUG
    assert(matrixMultDimCheck(rowCount,colCount,V.getSize(),1));
#endif

    long i; long j;

    double  Vsum;
    long  jIndex;
    double  diag;

    for(i = 0; i < rowCount; i++)
    {
        Vsum = 0.0;
        for(j = 0; j < rowFilledSizes[i]; j++)
        {
            jIndex = coeffColIndex[i][j];
            if(jIndex <  i) Vsum -= V(jIndex)*coeffValues[i][j];
            if(jIndex == i)
            {
             diag  = coeffValues[i][j];
             Vsum += V(i);
             }
        }
        if(abs(diag) < 1.0e-99)
        {
        cerr << "Error in SparseOp applyLowerTriInverse(...) " << endl;
        cerr << "Diagonal element < 1.0e-99 " << endl;
        cerr << "Row : " << i << endl;
        exit(0);
        }
        V(i) = Vsum/diag;
    }
}


/*!
This method overwrites the input vector instance V with the solution of
the linear system associated with the upper triangular part of S that includes
the diagonal. The values in the lower triangular part of S, excluding the
diagonal,  are ignored.

This method assumes that all diagonals of the matrix are non-zero.


If _DEBUG is defined then the required dimensional compatibility is checked
*/
void applyUpperTriInverse(Vtype& V)
{
#ifdef _DEBUG
    assert(matrixMultDimCheck(rowCount,colCount,V.getSize(),1));
#endif

    long i; long j;

    double  Vsum;
    long  jIndex;
    double  diag;

    for(i = rowCount-1; i >= 0; i--)
    {
        Vsum = 0.0;
        for(j = 0; j < rowFilledSizes[i]; j++)
        {
            jIndex = coeffColIndex[i][j];
            if(jIndex >  i) Vsum -= V(jIndex)*coeffValues[i][j];
            if(jIndex == i)
            {
             diag  = coeffValues[i][j];
             Vsum += V(i);
             }
        }
        if(abs(diag) < 1.0e-99)
        {
        cerr << "Error in SparseOp applyUpperTriInverse(...) " << endl;
        cerr << "Diagonal element < 1.0e-99 " << endl;
        cerr << "Row : " << i << endl;
        exit(0);
        }
        V(i) = Vsum/diag;
    }
}

/*!
This routine sorts the elements of each row so that the list of column indices associated with
each non-zero element in each row are in increasing order.
*/
void sortColumnIndices()
{
    long i;
    double* coeffValuesPtr;
    long*   coeffColIndexPtr;

    for(i = 0; i < rowCount; i++)
    {
    coeffValuesPtr   = coeffValues[i];
    coeffColIndexPtr = coeffColIndex[i];
    sortWithData(coeffColIndexPtr, coeffValuesPtr,rowFilledSizes[i]);
    }
}


/*!
This routine removes extraneous data that has been pre-allocated for each row.
*/
void compact()
{
    long i;
    for(i = 0; i < rowCount; i++)
    {
        if(rowFilledSizes[i] != rowSizes[i])
        {
        repackFlag = 1;
        resizeRow(i);
        }
    }
}

/*!
A routine that displays the structure of the matrix as a collection of "+" for non-zero values and "-" for zero values.
Due to the aspect ratio of display screens, the display of a square matrix will not be square.
 */
void printMatrixStructure() const
{
    double* S  = new double[rowCount*colCount];
    getOperatorAsDenseMatrix(S);

    long i; long j;
    for(i = 0; i < rowCount; i++)
    {
    for(j = 0; j < colCount; j++)
    {
    if(abs(S[j+ i*colCount])  == 0.0) printf("-");
    else                              printf("+");
    }
    printf("\n");
    }
    delete [] S;
}


/*!
Returns the initial estimate of the number of non-zero elements per row.
*/
long getInitialRowSize() const {return initialRowSize;}

/*!
Returns the multiplicative factor when the storage from a given row must be re-allocated.
*/
long getRowExpansionFactor() const {return rowExpansionFactor;}

/*!
A low level utility routine to extract the matrix data as a singly indexed double array.
This routine packs a double array S with the values of the dense matrix representation of the operator. The
data is stored by rows (C convention).

The input argument S is a pointer to an existing double array of size rowCount*colCount.

The (i,j)th element of the dense matrix can be accessed using

<pre>
Sij =  S[j+ i*colCount]
</pre>

*/
void getOperatorAsDenseMatrix(double* S) const
{
    // Zero all entries

    long i; long j;
    for(i = 0; i < rowCount; i++)
    {
    for(j = 0; j < colCount; j++)
    {
    S[j+ i*colCount] = 0.0;
    }}

    // Set non-zero entries

    for(i = 0; i < rowCount; i++)
    {
        for(j = 0; j < rowFilledSizes[i]; j++)
        {
            S[coeffColIndex[i][j] + i*colCount] = coeffValues[i][j];
        }
    }
}

//
// Internal utility routines and data members
//

protected:

void resizeRow(long rowIndex)
{
    //
    // Create new arrays for coefficient and index data 
    //
    long newSize;
    if(repackFlag == 0)
    {
        newSize   =  (long)(rowSizes[rowIndex]*rowExpansionFactor);
        if(newSize == rowSizes[rowIndex]) newSize++;
    }
    else
    {
        newSize = rowFilledSizes[rowIndex];
    }
    if(newSize > colCount) newSize = colCount;
    

    double* dataTemp  = new double[newSize];
    long*   indexTemp = new long[newSize];
        
    rowSizes[rowIndex] = newSize;

    // Copy over data 

    long k;
    for(k = 0; k < rowFilledSizes[rowIndex]; k++)
    {
    dataTemp[k]  = coeffValues[rowIndex][k];
    indexTemp[k] = coeffColIndex[rowIndex][k];
    }
    //
    // Swap pointers and then delete old data
    //
    delete [] coeffValues[rowIndex];
    delete [] coeffColIndex[rowIndex];
    
    coeffValues[rowIndex]   = dataTemp;
    coeffColIndex[rowIndex] = indexTemp;
    
    if(repackFlag == 1)
    {
      repackFlag = 0;
    }
}

void sortWithData(long* indexVals, double* coeffVals, long n) const
{
    long i,j,inc;
//
//  Shell sort
//
    long       iTmp;
    double     cTmp;
    inc=1;
    do 
    {
    inc *= 3;
    inc++;
    } while (inc <= n);
    do 
    {
        inc /= 3;
        for (i=inc+1;i<=n;i++) 
        {
            iTmp  =indexVals[i-1];
            cTmp  =coeffVals[i-1];
            j=i;
            while (indexVals[(j-inc)-1] > iTmp) 
            {
                indexVals[j-1]      = indexVals[(j-inc)-1];
                coeffVals[j-1]      = coeffVals[(j-inc)-1];
                j -= inc;
                if (j <= inc) break;
            }
            indexVals[j-1]  =   iTmp;
            coeffVals[j-1]  =   cTmp;
        }
    } while (inc > 1);
}

private:

//###################################################################
//                      Bounds Checking
//###################################################################
//
#ifdef _DEBUG
        bool boundsCheck(long i, long begin, long end, int coordinate) const
        {
        if((i < begin)||(i  > end))
        {
        cerr << "SparseOp index " << coordinate << " out of bounds " << endl;
        cerr << "Offending index value : " << i << " Acceptable Range [" << begin << "," << end << "]" << endl;
        return false;
        }
        return true;
        }
#else
        bool boundsCheck(long, long, long, int) const {return true;}
#endif
        #ifdef _DEBUG
        bool matrixVectorDimCheck(long aRow,long aCol, long vInSize, long vOutSize) const
        {
        if(aCol != vInSize)
        {
        cerr << "SparseOp incompatible matrix-vector multiplication sizes " <<  endl;
        cerr << "Left  operand ["<< aRow    << " X " << aCol << "]" << endl;
        cerr << "Right operand ["<< vInSize << " X " << 1 << "]" << endl;
        return false;
        }
        if(aRow != vOutSize)
        {
        cerr << "SparseOp incompatible matrix-vector multiplication return size" <<  endl;
        cerr << "Matrix size         : ["<< aRow    << " X " << aCol << "]" << endl;
        cerr << "Return vector Size :  ["<< vOutSize << " X " << 1 << "]"   << endl;
        return false;
        }
        return true;
        }
#else
        bool matrixVectorDimCheck(long aRow,long aCol, long bRow, long bCol) const {return true;}
#endif
#ifdef _DEBUG
        bool matrixMultDimCheck(long aRow,long aCol, long bRow, long bCol) const
        {
        if(aCol != bRow)
        {
        cerr << "SparseOp incompatible matrix sizes " <<  endl;
        cerr << "Left  operand ["<< aRow << " X " << aCol << "]" << endl;
        cerr << "Right operand ["<< bRow << " X " << bCol << "]" << endl;
        return false;
        }
        return true;
        }
#else
        bool matrixMultDimCheck(long aRow,long aCol, long bRow, long bCol) const {return true;}
#endif
#ifdef _DEBUG
        bool matrixSumDimCheck(long aRow,long aCol, long bRow, long bCol) const
        {
        if((aRow != bRow)||(aCol != bCol))
        {
        cerr << "SparseOp incompatible matrix sizes " <<  endl;
        cerr << "Left  operand ["<< aRow << " X " << aCol << "]" << endl;
        cerr << "Right operand ["<< bRow << " X " << bCol << "]" << endl;
        return false;
        }
        return true;
        }
#else
        bool matrixSumDimCheck(long aRow,long aCol, long bRow, long bCol) const {return true;}
#endif


void destroyData()
{
    long i;
    for(i = 0; i < rowCount; i++)
    {
    delete [] coeffValues[i];
    delete [] coeffColIndex[i];
    }
    delete [] coeffValues;
    delete [] coeffColIndex;
    
    delete [] rowSizes;
    delete [] rowFilledSizes;
    
    coeffValues    = 0;
    coeffColIndex  = 0;
    rowSizes       = 0;
    rowFilledSizes = 0;
}

double  dropTol;           // ignore matrix entries with magnitude less than dropTolerance

long    initialRowSize;
double  rowExpansionFactor;

long    rowCount;          // number of rows in the matrix
long*   rowSizes;          // the number of non-zero elements in each row
long*   rowFilledSizes;    // the number of filled elements in each row

long    colCount;          // number of columns in the matrix

long    totalDataCount;    // the total number of non-zero elements stored in the matrix
long    totalInitialCount; // the total number of calls to setOperatorData
long    totalDroppedCount; // the total number of elements dropped

double** coeffValues;     // array to hold pointers to coefficient values arrays
long**   coeffColIndex;   // array to hold pointers to arrays of column indices

Vtype vTmp;                // temporary for applyForwardOp;

int  rowIndexCache;
int     repackFlag;

};
#endif 
