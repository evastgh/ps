//
//  PCGMREStemplate : A template class implementing pre-conditioned GMRES(k), e.g.
//  pre-conditioned GMRES using a subspace of size k.
//
//  The value of k must be  >= 2
// 
//  The procedure is an implementation of GMRES based on the paper
//
//  "GMRES: A GENERALIZED MINIMAL RESIDUAL ALGORITHM FOR SOLVING NONSYMMETRIC LINEAR SYSTEMS"
//  by YOUCEF SAAD AND MARTIN H. SCHULTZ,  SIAM J. ScI. STAT. COMPUT.Vo|. 7, No. 3, July 1986
//
//  The residual required for the internal restart is computed explicitly and not recursively.
//
//  Member functions required for instantiation
//
//    Class                    |  Required member function 
//------------------------------------------------------------
//   
// Otype (The operator)       |   Otype()               
//                            |   apply(Vtype)
//
// Ptype (The preconditioner  |   Ptype()
// inverse operator)          |   Vtype apply(Vtype)
//                                   
//
// Vtype (The vector class)   |   Vtype()                         // null constructor
//                            |   Vtype(const Vtype& V)           // copy constructor
//                            |   void initialize(const Vtype& V) // duplicate V
//                            |   void operator =(const Vtype& V)  
//                            |   void operator +(const Vtype& V)
//                            |   void operator -(const Vtype& V)
//                            |   void operator *(double alpha)
//                            |   double dot(const Vtype& V)
//
//
//  The stopping criterion used in this implementation is 
//  
//              ||residual||/||b|| < tol
//
//
//  When the verbose output flag is set then the routine prints out
//  the relative norm of the residual.
//
//  Created for Math 270C : Chris Anderson : UCLA : 05/9/2016
// 
//
#include <cmath>
#include <cstdio>
#include <cstdlib>

#ifndef __PCGMREStemplate__
#define __PCGMREStemplate__

template <class Vtype, class Otype, class Ptype>
class PCGMREStemplate
{
//
//##########################
//  Data members
//##########################
//
protected :

//
//  Pointer to linear operator
//
    Otype* A;  // Solving A x = b 
//
//  Pointer to the pre-conditioner inverse operator
//
    Ptype* M;  //  approximate solution = M * b


    Vtype* V;  // pointer to array of vectors for the approximating Krylov
               // subspace. 
//
//  local data to implement the procedure
//
    double** h;
    double*  hData;
    double*  s;
    double* cs;
    double* sn;
    double*  y;

    Vtype* vTmp;
//
//  local method parameters
//
    double residual;
    long   maxIterations;
    double exitTolerance;
    long   iterCount;
    long   subspaceSize;

    int    verboseFlag;

//
//##########################
//  Member functions
//##########################
//

public :

PCGMREStemplate()
{
    subspaceSize        = 10;
    residual            = 0.0;
    maxIterations       = 100;
    exitTolerance       = 1.0e-05;
    iterCount           = 0;
    A                   = 0;
    M                   = 0;
    V                   = 0;
    vTmp                = 0;
    verboseFlag         = 0;

    hData = 0;
    h     = 0;
    s     = 0;
    cs    = 0;
    sn    = 0;
    y     = 0;
}

PCGMREStemplate(long subspaceSize)
{
    this->subspaceSize  = subspaceSize;
    residual            = 0.0;
    maxIterations       = 100;
    exitTolerance       = 1.0e-05;
    iterCount           = 0;
    A                   = 0;
    M                   = 0;
    V                   = 0;
    vTmp                = 0;
    verboseFlag         = 0;

    hData = 0;
    h     = 0;
    s     = 0;
    cs    = 0;
    sn    = 0;
    y     = 0;
}

~PCGMREStemplate()
{
    destroyLocalData();
}

void setOperator(Otype& O){A = &O;};

void setPreconditioner(Ptype& O){M = &O;};

void setSubspaceSize(long subspaceSize)
{this->subspaceSize = subspaceSize;}

void setIterationMax(long maxIterations) {this->maxIterations = maxIterations;}

void   setExitTolerance(double exitTolerance) {this->exitTolerance = exitTolerance;};
double getExitTolerance()                     {return exitTolerance;};

long   getIterationCount(){return iterCount;};

 double getRelativeResidualNorm()
 {return residual;}

void setVerboseFlag()  {verboseFlag = true; }
void clearVerboseFlag(){verboseFlag = false;}

//
// This routine solves the preconditioned system
//
//      M^(-1)*A*x = M^(-1)*f
//
// where M is the pre-conditioner whose apply(...)
// operator implements v <- M^(-1)(v).
//
// On input:  f contains the right hand side
//            x contains the starting vector
//
// On return: x contains the solution
//
int solve(Vtype& f, Vtype& x)
{
	// Create right hand side for
	// the preconditioned system

    Vtype b    = f;
    M->apply(b);

    createLocalData(b);

    long i; long j; long k;
    
    iterCount    = 0;

    Vtype  r     = b;
    Vtype Ax     = b;

    if(norm(x) > 1.0e-15) 
    {
    	Ax = x;
        A->apply(Ax);     // r = b - Ax; if x != 0
        M->apply(Ax);
        r  -= Ax;         // r = r - Ax;
    }
  
    double normb = norm(b);
    double beta  = norm(r);
    if (abs(normb) < 1.0e-15) normb = 1.0;

    residual = norm(r)/normb;

    if(residual <= exitTolerance) 
    {
    iterCount      = 0;
    return 0;
    }

// m = maximal power of operator in Krylov subspace
  
    long m = subspaceSize - 1; 
    if(maxIterations < subspaceSize) m = maxIterations;

    j = 1;
    while (j <= maxIterations) 
    {
    V[0] = r;
    V[0] *= 1.0/beta;

    //V[0] = r *(1.0/beta);    
    
    for(i = 0; i < subspaceSize; i++) s[i] = 0.0;

    s[0] = beta;
    
    for(i = 0; i < m && j <= maxIterations; j++, i++) 
    {
    Ax = V[i];
    A->apply(Ax);
    M->apply(Ax);

    for (k = 0; k <= i; k++) 
    {
        h[k][i]  = Ax.dot(V[k]);
        (*vTmp)  = V[k];
        (*vTmp) *= h[k][i];
        Ax      -= (*vTmp);

        //Ax = Ax - V[k]*h[k][i];
    }
    h[i+1][i] = norm(Ax);
    V[i+1]    = Ax;
    V[i+1]   *= (1.0/h[i+1][i]);

    //V[i+1]  = Ax*(1.0/h[i+1][i]); 

    for (k = 0; k < i; k++)
    {
        ApplyPlaneRotation(h[k][i], h[k+1][i], cs[k], sn[k]);
    }
      
    GeneratePlaneRotation(h[i][i], h[i+1][i], cs[i],sn[i]);
    ApplyPlaneRotation(h[i][i], h[i+1][i], cs[i], sn[i]);
    ApplyPlaneRotation(s[i], s[i+1], cs[i], sn[i]);
      
    residual = abs(s[i+1])/normb;

    if(verboseFlag == 1) printf("%ld  %10.5g \n",j,residual);

    if((residual < exitTolerance)||(j == maxIterations))
    {
        Update(x, i);
        iterCount = j;
        return 0;
    }
    }

    Update(x, m - 1);

    Ax = x;
    A->apply(Ax);
    M->apply(Ax);
    r  = b;
    r -= Ax; //r  = b - Ax;
    beta     = norm(r);

    residual = beta/normb;

    if(verboseFlag == 1) printf("%ld  %10.5g \n",j,residual);

    if (residual  < exitTolerance) 
    {
      iterCount = j;
      return 0;
    }

  }
  iterCount     = j;
  exitTolerance = residual;
  return 1;
}

void Update(Vtype& x, long k)
{
  // Backsolve:  

    long i;
    long j;

    for(i = 0; i <=k; i++) y[i] = s[i];

    for (i = k; i >= 0; i--) 
    {
        y[i] /= h[i][i];

        for (j = i-1; j >= 0; j--) 
        {
        y[j] -= h[j][i] * y[i];
        }
    }

    for (j = 0; j <= k; j++) 
    {
    (*vTmp)  = V[j];
    (*vTmp) *= y[j];
    x += (*vTmp);

    //x += V[j] * y[j];
    }

}

void GeneratePlaneRotation(double &dx, double &dy, double &cs, double &sn)
{
  double temp;
  if (abs(dy) < 1.0e-14)
  {
    cs = 1.0;
    sn = 0.0;
  }
  else if (abs(dy) > abs(dx))
  {
    temp = dx / dy;
    sn = 1.0 / sqrt( 1.0 + temp*temp );
    cs = temp * sn;
  }
  else
  {
    temp = dy / dx;
    cs = 1.0 / sqrt( 1.0 + temp*temp );
    sn = temp * cs;
  }
}

void ApplyPlaneRotation(double &dx, double &dy, double &cs, double &sn)
{
  double temp  =  cs * dx + sn * dy;
  dy = -sn * dx + cs * dy;
  dx = temp;
}


double norm(Vtype& v)
{
    double dotp = v.dot(v);
    return sqrt(abs(dotp));
}

void createLocalData(Vtype& v)
{
    destroyLocalData();

    // Create approximating subspace

    if(subspaceSize <= 0)
    {
    printf("GMRES Error : Subspace size not specified \n");
    printf("XXXX Program Halted XXXX \n");
    exit(0);
    }

    V = new Vtype[subspaceSize];
    for(long i = 0; i < subspaceSize; i++)
    {
    V[i].initialize(v);
    }


    long M = subspaceSize;

    hData = new double[(M*M)];
    h     = create2dArrayStructure(hData,M,M);
    s     = new double[M];
    cs    = new double[M];
    sn    = new double[M];
    y     = new double[M];

    vTmp  = new Vtype(V[0]); 
}

void destroyLocalData()
{
    if(V     != 0) delete [] V;
    if(hData != 0) delete [] hData;
    if(h     != 0) destroy2dArrayStructure(h);
    if(s     != 0) delete [] s;
    if(cs    != 0) delete [] cs;
    if(sn    != 0) delete [] sn;
    if(y     != 0) delete [] y;
    if(vTmp  != 0) delete vTmp;

    hData = 0;
    h     = 0;
    s     = 0;
    cs    = 0;
    sn    = 0;
    y     = 0;
}

//
// Internal helper functions for creating a 2D array
//
double** create2dArrayStructure(double* data, long m, long n)
{
   int i;
   double** A   = new double*[m];
   for(i = 0; i < m; i++){A[i] = &data[i*n];}
   return A;
}

void destroy2dArrayStructure(double** A)
{
   delete [] A;
}

};
#endif 
