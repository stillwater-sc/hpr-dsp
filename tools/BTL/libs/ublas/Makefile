include $(BENCH_BASE)/Makefile.in 

INCLUDES=$(INCLUDES_BASE) -I$(BOOST_ROOT)

OPTIM=$(OPTIM_BASE) -DNDEBUG -finline-functions 


DEBUG=$(DEBUG_BASE)

CXXFLAGS = $(OPTIM) $(INCLUDES) -ftemplate-depth-30

LIBS=$(LIBS_BASE) 

############################################################################

all : $(DEPEND_BASE) main


main:	Makefile main.o 
	$(CXX) -o main main.o $(LIBS) 


###########################################################################

main.o : $(DEPEND_BASE)  main.cpp ublas_interface.hh 

