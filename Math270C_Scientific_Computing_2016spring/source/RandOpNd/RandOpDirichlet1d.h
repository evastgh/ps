//
// RandOpDirichlet1d
//
// This operator class, derived from RandOp1d, initializes the interior values
// of a UCLAQ::GridFunction2d instance with random values that are uniformly
// distributed in [-1,1] and sets the boundary values to 0.0.
//
//
// Initial Construction : Oct. 7, 2015
// Latest  Revision     : Nov. 13, 2015
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

#include "RandOp1d.h"
#include "../GridFunctionNd/UCLAQ_GridFunction1d.h"

#ifndef _UCLAQ_RandOpDirichlet1d_
#define _UCLAQ_RandOpDirichlet1d_

namespace UCLAQ
{
class RandOpDirichlet1d : UCLAQ::RandOp1d
{
    public :

	RandOpDirichlet1d() : RandOp1d(){}

    virtual ~RandOpDirichlet1d(){}

    virtual void randomize(UCLAQ::GridFunction1d& v)
    {
    	RandOp1d::randomize(v);
        v.setBoundaryValues(0.0);

    }
};
 
}
#endif
