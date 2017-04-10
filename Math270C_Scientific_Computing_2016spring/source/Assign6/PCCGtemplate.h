#include <cmath>
#include <cstdio>
using namespace std;    
//
// PCCGtemplate : A  Pre-Conditioned Conjugate Gradient Template Class
//
//
// Member functions required for instantiation
//
//    Class                   |  Required member functions
//------------------------------------------------------------
//
// Otype (The operator)       |   Otype()
//                                Vtype apply(const Vtype& V)
//
//
// Ptype (The preconditioner  |   Ptype()
// inverse operator)          |   Vtype apply(Vtype)
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
//      side. It is through the assignment operator that the internal
//      vector temporaries are constructed.
//
//  This is an "instructional" implementation:
//
//  (*) The stopping criterion used in this implementation is
//
//              ||residual||_2 / ||b||_2 < tol
//
//
//  (*) The routine is written in terms of standard algebraic vector
//  operations +, -, etc. and not incremental vector operations
//  +=, -= etc. (which tend to be more efficient as they avoid
//  extraneous calls to the copy constructor) or level 1 BLAS.
//
//  Created for Math 270C : Chris Anderson : UCLA : 5/5/2015
//
#ifndef __PCCGtemplate__
#define __PCCGtemplate__

template <class Vtype, class Otype, class Ptype>
class PCCGtemplate
{

//##########################
//  Data members
//##########################

//  Iteration variables

    long          iter;
    long         itmax;
    double         tol;

    bool   verboseFlag;
    double      rnorm2;
    double      bnorm2;

//
//  Pointer to linear operator 
//
    Otype* A;  // Solving A x = b 
//
//  Pointer to the pre-conditioner inverse operator
//
    Ptype* M;  //  approximate solution = M * b 
//
//  Temporaries 
//
    Vtype b; Vtype x;
    Vtype p; Vtype r; Vtype w; Vtype z;

    Vtype rOrig;

//##########################
//  Member functions
//##########################

public :

   PCCGtemplate()
    {
        itmax = 10000;
        tol   = 1.0e-06;
        iter  = 0;
        A     = 0;
        M     = 0;

        verboseFlag   = false;
        rnorm2        = 0.0;
    }

    void setRightHandSide(Vtype rhs)
    {
      x = rhs;
      b = rhs;
      w = rhs; 
      z = rhs;
    };

    void setOperator(Otype& O)
    {A = &O;};

    void setPreconditioner(Ptype& P)
    {M = &P;};

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
    
    double beta_k  = 0.0;
    double alpha_k = 0.0;

    double rho_k       = 0.0;
    double r_dot_z_k   = 0.0;
    double r_dot_z_km1 = 0.0;

    iter    = 0;
    w       = x;

    A->apply(w);
    r        = b - w;

    rho_k   = r.dot(r);
    rnorm2 = sqrt(abs(rho_k));
    bnorm2 = sqrt(abs(b.dot(b)));

    while((iter < itmax)&&(rnorm2 >  tol*bnorm2))
    {

    z = r;

    M->apply(z);           // apply inverse of pre-conditioner

    iter  = iter+1;

    if(iter == 1)
    {
        p         = z;
        r_dot_z_k = r.dot(z);
    }
    else
    {
        r_dot_z_km1 = r_dot_z_k;
        r_dot_z_k   = r.dot(z);

        beta_k  = r_dot_z_k/r_dot_z_km1;
        p       = z + beta_k*p;      
    }
   
    w = p;
    A->apply(w);          // apply operator defining the system

    alpha_k     = r_dot_z_k/(p.dot(w));

    x = x + alpha_k*p;    // update solution
    r = r - alpha_k*w;    // update residual

    rho_k = r.dot(r);
    rnorm2 = sqrt(abs(rho_k));

    if(verboseFlag)
    {printf("Iteration %-6ld :  PCCG residual Norm : %10.5e \n",iter,rnorm2/bnorm2);}

    }

    }
};
#endif
