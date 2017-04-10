#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#include "../DoubleVectorNd/UCLAQ_DoubleVector2d.h"
#include "../Assign2/LaplaceOp2d.h"
#include "../Assign5/CGtemplate.h"
#include "../Timing/ClockIt.h"

#include "MultiGrid_PreCondOp2d.h"
#include "PCCGtemplate.h"

long CGTestLite(double stopTol, long maxIter, UCLAQ::DoubleVector2d u)
{
    long nx = u.getIndex1Size(), ny = u.getIndex2Size();
    long xPanels = nx+1, yPanels = ny+1;
    double hx = 1.0/(double)xPanels, hy = 1.0/(double)yPanels;
    double alpha = -1.0;

    // Initialize right hand side

    UCLAQ::DoubleVector2d f(nx, ny);

    // Initialize operators

    LaplaceOp2d Lop2d(alpha,xPanels,hx,yPanels,hy);
    CGtemplate <UCLAQ::DoubleVector2d, LaplaceOp2d> cgOp;
    //                  |                 |
    //                  |                 |
    //          vector class        operator class
    //

    // Associate linear operator that cgOp is to use

    cgOp.setOperator(Lop2d);

    // Specify iteration parameters and verbose flag

    cgOp.setExitTolerance(stopTol);
    cgOp.setIterationMax(maxIter);
    cgOp.clearVerboseFlag();

    // [C0] Determine/specify right hand side 

    f.setToValue(1.0);
    Lop2d.apply(f);

    // Specify starting iterate

    u.setToValue(0.0);

    // Solve the system

    cgOp.solve(f,u);

    return cgOp.getIterationCount();

}

long PC_CG_MultiGrid_TestLite(double stopTol, long maxIter, long maxMultiGridLevel, double GJomega, long relaxationCount, long minMultiGridLevel, UCLAQ::DoubleVector2d u)
{
    long nx = u.getIndex1Size(), ny = u.getIndex2Size();
    long xPanels = nx+1, yPanels = ny+1;
    double hx = 1.0/(double)xPanels, hy = 1.0/(double)yPanels;
    double alpha = -1.0;
    double xMin = 0.0, xMax = 1.0, yMin = 0.0, yMax = 1.0;

    // Initialize right hand side

    UCLAQ::DoubleVector2d f(nx, ny);
    
    // [C0] Determine/specify right hand side 

    LaplaceOp2d Lop2d(alpha,xPanels,hx,yPanels,hy);
    f.setToValue(1.0);
    Lop2d.apply(f);

    // Initialize operators

    MultiGrid_PreCondOp2d PCMultiGridOp(maxMultiGridLevel, relaxationCount, GJomega, alpha, xMin, xMax,yMin,yMax,minMultiGridLevel);
    PCCGtemplate <UCLAQ::DoubleVector2d, LaplaceOp2d, MultiGrid_PreCondOp2d> PCcgOp;

    PCcgOp.setRightHandSide(f);
    PCcgOp.setOperator(Lop2d);
    PCcgOp.setPreconditioner(PCMultiGridOp);
    PCcgOp.setIterationMax(maxIter);
    PCcgOp.setExitTolerance(stopTol);

// read 11.5.2.~~~

    // Set verbose flag

    //PCcgOp.setVerboseFlag();


    // Specify starting iterate

    u.setToValue(0.0);

    // Solve the system

    PCcgOp.solve(f,u);

    return PCcgOp.getIterationCount();
}

int main(){
    double stopTol = 1e-06;
    long maxIter = 1000;
    long xPanels, yPanels;

    // [C1] Record the time taken by non-pre-conditioned CG solver

    double CGtime, PCCGtime;
    long CGiterCount, PCCGiterCount;
    ClockIt CGclock, PCCGclock;
    long N = 10;
    UCLAQ::DoubleVector2d u, v;

    double GJomega = 0.8;
    long relaxationCount=2;
    long maxMultiGridLevel, minMultiGridLevel;

    ofstream outputFileStreamTime, outputFileStreamIter;
    outputFileStreamTime.open("PreCond_ResultsTime.csv");
    outputFileStreamIter.open("PreCond_ResultsIter.csv");

    outputFileStreamTime << " & CG & 0 & 1 & 2 & 3 & 4 & 5 & 6 \\\\" << endl << "\\hline" << endl;
    outputFileStreamIter<< " & CG & 0 & 1 & 2 & 3 & 4 & 5 & 6 \\\\" << endl << "\\hline" << endl;


    for(long k=0; k<3; k++){
        u.initialize(pow(2, k+6)-1, pow(2, k+6)-1);
        v.initialize(pow(2, k+6)-1, pow(2, k+6)-1);

        maxMultiGridLevel = k+5;

        outputFileStreamTime << maxMultiGridLevel << " & ";
        outputFileStreamIter << maxMultiGridLevel << " & ";
        
        CGclock.start();
        for(long i=0; i<N; i++)
            CGiterCount = CGTestLite(stopTol, maxIter, u);
        CGclock.stop();
        CGtime = CGclock.getSecElapsedTime()/(double)N;
        outputFileStreamTime << CGtime;
        outputFileStreamIter << CGiterCount;


        for(minMultiGridLevel = 0; minMultiGridLevel < maxMultiGridLevel; minMultiGridLevel++){
            PCCGclock.start();
            for(long i=0; i<N; i++)
                PCCGiterCount = PC_CG_MultiGrid_TestLite(stopTol,maxIter,maxMultiGridLevel,GJomega,relaxationCount,minMultiGridLevel,v);
            PCCGclock.stop();
            PCCGtime = PCCGclock.getSecElapsedTime()/(double)N;
            outputFileStreamTime << " & " << PCCGtime;
            outputFileStreamIter << " & " << PCCGiterCount;
        }
        for(long i=7; i > maxMultiGridLevel; i--){
            outputFileStreamTime << " & ";
            outputFileStreamIter << " & ";
        }
        outputFileStreamTime << "\\\\" << endl;
        outputFileStreamIter << "\\\\" << endl;
    }
    
    outputFileStreamTime.close();
    outputFileStreamIter.close();


    // [C3] multi-parameter test!

    N = 5;
    ofstream outputFileStreamMultiParameterTest, outputFileStreamMultiParameterTestdata;
    outputFileStreamMultiParameterTest.open("MultiParameterTest.csv");
    outputFileStreamMultiParameterTestdata.open("MultiParameterTest_data.csv");
    

    for(long k=0; k<3; k++){
        u.initialize(pow(2, k+6)-1, pow(2, k+6)-1);
        v.initialize(pow(2, k+6)-1, pow(2, k+6)-1);

        long minimalMinMultiGridLevel=0;
        double minimalGJomega=0.0;
        long minimalRelaxationCount=0;
        double minimalTimeTemp=1000.0;

        maxMultiGridLevel = k+5;

        for(minMultiGridLevel = 0; minMultiGridLevel < maxMultiGridLevel; minMultiGridLevel++){
            for(GJomega = 0.1; GJomega < 1.0; GJomega+=0.1){
                for(relaxationCount = 1; relaxationCount < 5; relaxationCount++){
                    PCCGclock.start();
                    for(long i=0; i<N; i++)
                        PCCGiterCount = PC_CG_MultiGrid_TestLite(stopTol,maxIter,maxMultiGridLevel,GJomega,relaxationCount,minMultiGridLevel,v);
                    PCCGclock.stop();
                    PCCGtime = PCCGclock.getSecElapsedTime()/(double)N;
                    outputFileStreamMultiParameterTestdata << maxMultiGridLevel << " & " << minMultiGridLevel << " & " << GJomega << " & " << relaxationCount << " & " << PCCGiterCount << " & " << PCCGtime << "\\\\" << endl;
                    if(PCCGtime < minimalTimeTemp){
                        minimalTimeTemp = PCCGtime;
                        minimalMinMultiGridLevel = minMultiGridLevel;
                        minimalGJomega = GJomega;
                        minimalRelaxationCount = relaxationCount;
                    }
                }
            }
            cout << "Tests at max-min level (" << maxMultiGridLevel << ", " << minMultiGridLevel << ") all done. " << endl;
        }
        outputFileStreamMultiParameterTest << maxMultiGridLevel << " & ";
        outputFileStreamMultiParameterTest << minimalMinMultiGridLevel << " & ";
        outputFileStreamMultiParameterTest << minimalGJomega << " & ";
        outputFileStreamMultiParameterTest << minimalRelaxationCount << " & ";
        outputFileStreamMultiParameterTest << minimalTimeTemp << "\\\\" << endl;
    }

    outputFileStreamMultiParameterTest.close();

}