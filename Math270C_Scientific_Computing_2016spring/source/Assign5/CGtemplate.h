#include <cmath>
#include <cstdio>
using namespace std;

//
// CGtemplate : A Conjugate Gradient Template Class
// 
// 
// Member functions required for instantiation 
//
//    Class                   |  Required member function 
//------------------------------------------------------------
//   
// Otype (The operator)       |   Otype()               
//                                apply(const Vtype& V)
//                             
//
// Vtype (The vector class)   |   Vtype()  
//                            |   void operator  =(const Vtype& V)  
//                            |   Vtype operator +(const Vtype& V)
//                            |   Vtype operator -(const Vtype& V)
//                            |   Vtype operator *(double alpha)
//                            |   void  operator *=(double alpha)
//                            |   double dot(const Vtype& V)
//                            |   double normInf(const Vtype& V)
//
// !!!! In the vector assignment operator: If the left hand 
//      side is a null instance, e.g. a vector created by 
//      the null constructor, then the assignment operator should
//      create a new instance that is a duplicate of the right hand
//      side. It is through the assigment operator that the internal
//      vector temporaries are constructed. 
//       
//  This is an "instructional" implementation:
//
//  (*) The stopping criterion used in this implementation is 
//  
//              ||cg residual||_2 / ||b||_2 < tol
//  
//  (*) The routine is written in terms of standard algebraic vector
//  operations +, -, etc. and not incremental vector operations
//  +=, -= etc. (which tend to be more efficient as they avoid
//  extraneous calls to the copy constructor) or level 1 BLAS. 
//
//  Created for Math 270C : Chris Anderson : UCLA : 4/26/2016
//
#ifndef __CGtemplate__
#define __CGtemplate__

template <class Vtype, class Otype >
class CGtemplate 
{

//##########################
//  Data members
//##########################

//
//  Pointer to linear operator
//
    Otype* A;  // Solving A x = b

//  Iteration variables

    long          iter;
    long         itmax;
    double         tol;

    bool       verboseFlag;
    double          rnorm2;
    double          bnorm2;
//
//  Temporaries 
//
    Vtype p; Vtype r; Vtype w;

    Vtype rStar;

//##########################
//  Member functions
//##########################

public :

    CGtemplate()
    {
        itmax = 10000;
        tol   = 1.0e-06;
        iter  = 0;
        A     = 0;

        verboseFlag   = false;
        rnorm2        = 0.0;
    }

    void setOperator(Otype& O)
    {A = &O;};

    void setIterationMax(long iterationMax)
    {itmax = iterationMax;}

    long getIterationCount()
    {return iter;};

    void setExitTolerance(double value)
    {tol = value;};

    double getExitTolerance()
    {return tol;};

    double getRelativeResidualNorm()
    {return rnorm2/bnorm2;}

    void setVerboseFlag()
    {verboseFlag = true;}

    void clearVerboseFlag()
    {verboseFlag = false;}

    //
    // This routine solves A*x = b
    //
    // On input:  b contains the right hand side 
    //            x contains the starting vector 
    //
    // On return: x contains the solution
    //
    void solve(Vtype& b, Vtype& x)
    {
    double   beta_k;
    double  alpha_k;
    double    rho_k;
    double  rho_km1;

    iter     = 0;
    w       = x;
    A->apply(w);

    r        = b - w;
  
    rho_k   = r.dot(r);
    rnorm2 = sqrt(abs(rho_k));
    bnorm2 = sqrt(abs(b.dot(b)));

    while((iter < itmax)&&(rnorm2 >  tol*bnorm2))
    {

    iter  = iter+1;

    if(iter == 1)
    {
        p       = r;
    }
    else
    {
        beta_k  = rho_k/rho_km1;
        p       = r + beta_k*p;      
    }
   
    w = p;
    A->apply(w);

    alpha_k = rho_k/(p.dot(w));

    x = x + alpha_k*p;
    r = r - alpha_k*w;

    rho_km1 = rho_k;
    rho_k   = r.dot(r);

    rnorm2  = sqrt(abs(rho_k));

    if(verboseFlag)
    {printf("Iteration %-6ld :  CG residual Norm : %10.5e \n",iter,rnorm2);}
    }
    }
};
#endif
