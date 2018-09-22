include $(BENCH_BASE)/Makefile.in 

INCLUDES=$(INCLUDES_BASE) -I$(FORTRAN_DIR) -I$(ATLAS_BLAS_INCLUDE) -I$(ATLAS_BLAS_INCLUDE2)
OPTIM=$(OPTIM_BASE)
DEBUG=$(DEBUG_BASE)

CXXFLAGS = $(OPTIM) $(INCLUDES)

LIBS=$(LIBS_BASE) -L$(ATLAS_BLAS_LIB) -llapack -lcblas -latlas

############################################################################

all : $(DEPEND_BASE) main

main:	Makefile main.o  
	$(CXX) -o main main.o   $(LIBS) 


###########################################################################

main.o : $(DEPEND_BASE) main.cpp ATLAS_interface.hh


