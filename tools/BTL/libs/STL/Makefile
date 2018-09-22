include $(BENCH_BASE)/Makefile.in 

LIBS=$(LIBS_BASE) 
INCLUDES=$(INCLUDES_BASE)
LIBS=$(LIBS_BASE)
OPTIM=$(OPTIM_BASE)
DEBUG=$(DEBUG_BASE)

CXXFLAGS = $(OPTIM) $(INCLUDES) 



all : $(DEPEND_BASE) main

main:	Makefile main.o 
	$(CXX) -o main main.o $(LIBS) 


###########################################################################

main.o : Makefile main.cpp  STL_interface.hh 


