include $(BENCH_BASE)/Makefile.in 

INCLUDES=$(INCLUDES_BASE) -I$(FORTRAN_DIR) 
OPTIM=$(OPTIM_BASE)
DEBUG=$(DEBUG_BASE)
LIBS=$(LIBS_BASE) 

CXXFLAGS = $(OPTIM) $(INCLUDES)

F77 = g77
F77FLAGS=-O3

############################################################################

.SUFFIXES: .o .f 

.f.o:
	$(F77) $(F77FLAGS) -c *.f

###########################################################################

all : main

FORTRAN_OBJECT=dmxv.o smxv.o dmxm.o smxm.o daxpy.o saxpy.o data.o sata.o daat.o saat.o

main:	main.o $(FORTRAN_OBJECT)
	$(CXX) -o main main.o $(FORTRAN_OBJECT) $(LIBS) 


###########################################################################

main.o :  $(DEPEND_BASE) main.cpp f77_interface.hh f77_interface_base.hh

dmxv.o : dmxv.f

smxv.o : smxv.f

dmxm.o : dmxm.f

smxm.o : smxm.f

daxpy.o : daxpy.f

saxpy.o : saxpy.f

data.o : data.f

sata.o : sata.f

daat.o : daat.f

saat.o : saat.f



