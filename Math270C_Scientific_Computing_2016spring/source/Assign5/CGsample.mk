#
#  CGsample.mk : Sample "minimal" make file for CGsample.exe
#
#  Execute this makefile by typing "make -f  CGsample.mk" at the command
#  prompt. If you edit this file, be aware that in makefiles tabs are
#  significant. 
#
#  To clean the directory of .o files and .exe files type
#  "make -f "CGsample.mk clean" at the command line.  
#
#  The executable created by this make file is  CGsample.exe
#
#  04/19/2016
#
CC         =  g++
INCLUDES  += -I../270C_Classes  -I../Assign2  # Specifying location of C++ support files and files with Assign2 classes

DEFINES=                          # Specify DEFINES= -D _DEBUG to enable array bounds checking
                                  # otherwise just leave the rest of the line empty

CCFLAGS= -O2 -std=c++11           # Need to use C++ 11 constructs

CGsample.exe : CGsample.o  
	$(CC) CGsample.o -o CGsample.exe 

CGsample.o: CGsample.cpp  
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDES) $< 

%.o  : %.cpp 
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDES) $< 

clean :
	rm *.o
	rm *.exe
