#ifndef _SORop2d_
#define _SORop2d_


#include "../DoubleVectorNd/UCLAQ_DoubleVector2d.h"
using namespace std;

class SORop2d
{
public:
	double alpha;
	double hx, hy;
	long xPanels, yPanels;
	long nx, ny;
	double omega;
	UCLAQ::DoubleVector2d f;

	SORop2d(){
		initialize();
	}

	SORop2d(double _alpha, long _xPanels, double _hx, long _yPanels, double _hy, double _omega){
		initialize(_alpha, _xPanels, _hx, _yPanels, _hy, _omega);
	}

	void initialize(){
		alpha = 0.0;
		hx = 0.0;
		hy = 0.0;
		xPanels = 0;
		yPanels = 0;
		nx = 0;
		ny = 0;
		omega = 0.0;
		f.initialize();
	}

	void initialize(double _alpha, long _xPanels, double _hx, long _yPanels, double _hy, double _omega){
		alpha = _alpha;
		xPanels = _xPanels;
		hx = _hx;
		yPanels = _yPanels;
		hy = _hy;
		omega = _omega;
		nx = xPanels-1;
		ny = yPanels-1;
		f.initialize(nx, ny);
	}

	virtual ~SORop2d(){}

	void setRightHandSide(UCLAQ::DoubleVector2d& _f){
		f = _f;
	}

	void apply(UCLAQ::DoubleVector2d& V){
    	double vStar;
    	long i, j;
    	double diag = -1.0/( alpha*(2.0/(hx*hx) + 2.0/(hy*hy) ) );	// diagonal element of M inverse
    	double entryX = alpha*1.0/(hx*hx);
    	double entryY = alpha*1.0/(hy*hy);


    	i=0;
    	j=0;
    	vStar =  diag*(f(i, j) - entryX*(V(i+1,j)) - entryY*(V(i, j+1)));
    	V(i, j) = omega*vStar + (1.0-omega)*V(i, j);

    	for(j=1; j < ny-1; j++){
        	vStar =  diag*(f(i, j) - entryX*V(i+1,j) - entryY*(V(i, j+1) + V(i, j-1)));
        	V(i, j) = omega*vStar + (1.0-omega)*V(i, j);
        }

    	j=ny-1;
    	vStar =  diag*(f(i, j) - entryX*(V(i+1,j)) - entryY*(V(i, j-1)));
    	V(i, j) = omega*vStar + (1.0-omega)*V(i, j);



    	for(i = 1; i < nx-1; i++){
    		j=0;
        	vStar =  diag*(f(i, j) - entryX*(V(i+1,j) + V(i-1,j)) - entryY*V(i, j+1));
        	V(i, j) = omega*vStar + (1.0-omega)*V(i, j);    		
        	for(j=1; j < ny-1; j++){
            	vStar =  diag*(f(i, j) - entryX*(V(i+1,j) + V(i-1,j)) - entryY*(V(i, j+1) + V(i, j-1)));
            	V(i, j) = omega*vStar + (1.0-omega)*V(i, j);
            }
        	j = ny-1;
        	vStar =  diag*(f(i, j) - entryX*(V(i+1,j) + V(i-1,j)) - entryY*V(i, j-1));
    		V(i, j) = omega*vStar + (1.0-omega)*V(i, j);
    	}

	    i=nx-1;
    	j=0;
    	vStar =  diag*(f(i, j) - entryX*(V(i-1,j)) - entryY*(V(i, j+1)));
    	V(i, j) = omega*vStar + (1.0-omega)*V(i, j);
    	for(j=1; j < ny-1; j++){
        	vStar =  diag*(f(i, j) - entryX*V(i-1,j) - entryY*(V(i, j+1) + V(i, j-1)));
    		V(i, j) = omega*vStar + (1.0-omega)*V(i, j);
    	}
    	j=ny-1;
    	vStar =  diag*(f(i, j) - entryX*(V(i-1,j)) - entryY*(V(i, j-1)));
    	V(i, j) = omega*vStar + (1.0-omega)*V(i, j);


	}

    void setRelaxationParameter(double _omega){
        omega = _omega;
    }

};

#endif /* _SOROP2D_H_ */