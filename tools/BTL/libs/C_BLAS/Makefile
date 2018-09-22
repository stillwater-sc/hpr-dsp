include $(BENCH_BASE)/Makefile.in 

INCLUDES=$(INCLUDES_BASE) -I$(FORTRAN_DIR) -I$(C_BLAS_INCLUDE) 
OPTIM=$(OPTIM_BASE)
DEBUG=$(DEBUG_BASE)

CXXFLAGS = $(OPTIM) $(INCLUDES)

LIBS=$(LIBS_BASE) $(C_BLAS_LIB) $(F77_BLAS_LIB) -lg2c

############################################################################

all : $(DEPEND_BASE) main

main:	Makefile main.o  
	$(CXX) -o main main.o   $(LIBS) 


###########################################################################

main.o : $(DEPEND_BASE) main.cpp C_BLAS_interface.hh


