include $(BENCH_BASE)/Makefile.in 

LIBS=$(LIBS_BASE) -L$(BLITZ_ROOT)/lib -lblitz
INCLUDES=$(INCLUDES_BASE) -I$(BLITZ_ROOT)
OPTIM=$(OPTIM_BASE) 
DEBUG=$(DEBUG_BASE)

CXXFLAGS = $(OPTIM) $(INCLUDES)



############################################################################

all : $(DEPEND_BASE) main

main:	Makefile main.o  
	$(CXX) -o main main.o $(LIBS) 


###########################################################################

main.o : $(DEPEND_BASE) main.cpp blitz_interface.hh 


