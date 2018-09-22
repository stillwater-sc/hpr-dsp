include $(BENCH_BASE)/Makefile.in 

LIBS=$(LIBS_BASE) 
INCLUDES=$(INCLUDES_BASE)
OPTIM=$(OPTIM_BASE)
DEBUG=$(DEBUG_BASE) -D_DEBUG_

CXXFLAGS = $(OPTIM) $(INCLUDES)

############################################################################

all : $(DEPEND_BASE) main

main:	$(DEPEND_BASE) main.o  
	$(CXX) -o main main.o $(LIBS) 


###########################################################################

main.o : $(DEPEND_BASE) main.cpp C_interface.hh



