//
// RandOpDirichlet3d
//
// This operator class, derived from RandOp3d, initializes the interior values
// of a UCLAQ::GridFunction3d instance with random values that are uniformly
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

#include "RandOp3d.h"
#include "../GridFunctionNd/UCLAQ_GridFunction3d.h"

#ifndef _UCLAQ_RandOpDirichlet3d_
#define _UCLAQ_RandOpDirichlet3d_

namespace UCLAQ
{
class RandOpDirichlet3d : UCLAQ::RandOp3d
{
    public :

	RandOpDirichlet3d() : RandOp3d(){}

    virtual ~RandOpDirichlet3d(){}

    virtual void randomize(UCLAQ::GridFunction3d& v)
    {
    	RandOp3d::randomize(v);
        v.setBoundaryValues(0.0);

    }
};
 
}
#endif
