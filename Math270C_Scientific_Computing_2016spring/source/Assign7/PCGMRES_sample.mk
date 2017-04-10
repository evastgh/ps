#
#  PCGMRES_sample.mk : Sample "minimal" make file for PCGMRES_sample.exe
#
#  Execute this makefile by typing "make -f  PCGMRES_sample.mk" at the command
#  prompt. If you edit this file, be aware that in makefiles tabs are
#  significant. 
#
#  To clean the directory of .o files and .exe files type
#  "make -f "PCGMRES_sample.mk clean" at the command line.  
#
#  The executable created by this make file is  PCGMRES_sample.exe
#
#  5/3/2016
#
CC         =  g++
INCLUDES  += -I../270C_Classes    # Specifying location of C++ support files

DEFINES=                          # Specify DEFINES= -D _DEBUG to enable array bounds checking
                                  # otherwise just leave the rest of the line empty

CCFLAGS= -O2 -std=c++11           # Need to use C++ 11 constructs

PCGMRES_sample.exe : PCGMRES_sample.o  
	$(CC) PCGMRES_sample.o -o PCGMRES_sample.exe 

PCGMRES_sample.o: PCGMRES_sample.cpp 
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDES) $< 

%.o  : %.cpp 
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDES) $< 

clean :
	rm *.o
	rm *.exe
