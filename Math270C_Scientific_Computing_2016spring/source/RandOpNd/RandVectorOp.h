//
// RandVectorOp
//
// An operator, templated with respect to a vector class, that initializes the values of
// a vector instance with random values that are uniformly distributed in [-1,1].
//
// Required member functions of vector class:
//
// long getDimension()      : returns the number of elements in the vector 
// double* getDataPointer() : returns a pointer to the first data value in the vector
// 
// It is assumed that the value data associated with the vector 
// are stored in contiguous memory locations. 
// 
//
// The 64 bit random number generator used is "Mersenne Twister"
// generator mt19937_64 available in <random>.
//
// Use of this header requires a compiler that supports c++11
// constructs.
//
// Initial version April 12, 2016
/*
#############################################################################
#
# Copyright  2015 Chris Anderson
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
#ifndef _UCLAQ_RandVectorOp_
#define _UCLAQ_RandVectorOp_

#include <random>
using namespace std;

#define RandVectorOp_DEFAULT_SEED 3141592

namespace UCLAQ
{
template <class Vtype> class RandVectorOp
{
    public :

	RandVectorOp()
    {
		// Initialize the random generator with the default seed

	    seed = RandVectorOp_DEFAULT_SEED;
	    randomGenerator.seed(seed);

	    // Initialize the distribution to be uniform in the interval [-1,1]

	    uniform_real_distribution<double>::param_type distParams(-1.0,1.0);
	    distribution.param(distParams);
    }

    virtual ~RandVectorOp()
    {}

    void resetSeed(int seed)
    {
    this->seed = seed;
    randomGenerator.seed(seed);
    }

    void resetWithRandomSeed()
    {
    this->seed = (int)time(0);
    resetSeed(seed);
    }

    virtual void randomize(Vtype& v)
    {
        long i;
        double* valuesPtr = v.getDataPointer();
        for(i = 0; i < v.getDimension(); i++)
        {
        valuesPtr[i] =   distribution(randomGenerator);
        }
    }

    int                                            seed;
    mt19937_64                          randomGenerator;
	uniform_real_distribution<double>      distribution;
};

#undef RandVectorOp_DEFAULT_SEED  
 
}
#endif
