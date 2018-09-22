include $(BENCH_BASE)/Makefile.in 

LIBS=$(LIBS_BASE) 
INCLUDES=-I. $(INCLUDES_BASE) -I$(TVMET_INCLUDES)
OPTIM=$(OPTIM_BASE) 
DEBUG=$(DEBUG_BASE)

CXXFLAGS = $(OPTIM) $(INCLUDES)



############################################################################

all : $(DEPEND_BASE) main

main:	Makefile main.o  
	$(CXX) -o main main.o $(LIBS) 


###########################################################################

main.o : $(DEPEND_BASE) main.cpp tvmet_interface.hh
