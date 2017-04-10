#
#  MultiGrid1d.mk : Sample "minimal" make file for MultiGrid1d.exe
#
#  Execute this makefile by typing "make -f MultiGrid1d.mk" at the command
#  prompt. If you edit this file, be aware that in makefiles tabs are
#  significant. 
#
#  To clean the directory of .o files and .exe files type
#  "make -f "MultiGrid1d.mk clean" at the command line.  
#
#  The executable created by this make file is MultiGrid1d.exe
#
#  04/25/2016
#
CC         =  g++
INCLUDES  += -I../270C_Classes  -I../Assign2  # Specifying location of C++ support files and files with Assign2 classes

DEFINES=                          # Specify DEFINES= -D _DEBUG to enable array bounds checking
                                  # otherwise just leave the rest of the line empty

CCFLAGS= -O2 -std=c++11           # Need to use C++ 11 constructs

MultiGrid1d.exe : MultiGrid1d.o   ../Assign2/GaussJacobiOp1d.h ./SparseInterpOp1d.h ./MultiGridVcycle1d.h
	$(CC) MultiGrid1d.o -o MultiGrid1d.exe 

MultiGrid1d.o: MultiGrid1d.cpp  ../Assign2/GaussJacobiOp1d.h  ./SparseInterpOp1d.h ./MultiGridVcycle1d.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDES) $< 

%.o  : %.cpp 
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDES) $< 

clean :
	rm *.o
	rm *.exe
