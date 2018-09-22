include $(BENCH_BASE)/Makefile.in 

INCLUDES=$(INCLUDES_BASE) -I$(FORTRAN_DIR) -I$(INTEL_BLAS_INCLUDE) 
OPTIM=$(OPTIM_BASE)
DEBUG=$(DEBUG_BASE)

CXXFLAGS = $(OPTIM) $(INCLUDES)

LIBS=$(LIBS_BASE) $(INTEL_BLAS_LIB) 

############################################################################

all : $(DEPEND_BASE) main

main:	Makefile main.o  
	$(CXX) -o main main.o   $(LIBS) 


###########################################################################

main.o : $(DEPEND_BASE) main.cpp INTEL_BLAS_interface.hh


