include Makefile.in

BENCH_LIB=$(BENCH_BASE)/libs

all : C STL f77 blitz ATLAS MTL ublas INTEL_BLAS STL_algo tiny_blitz tvmet##C_BLAS

blitz : test_conf  
	( cd $(BENCH_LIB)/blitz ; make )

MTL : test_conf  
	(cd $(BENCH_LIB)/MTL ; make )

f77 : test_conf  
	(cd $(BENCH_LIB)/f77 ; make )

C : test_conf  
	(cd $(BENCH_LIB)/C ; make )

STL : test_conf  
	(cd $(BENCH_LIB)/STL ; make )

ATLAS : test_conf  
	(cd $(BENCH_LIB)/ATLAS ; make )

ublas : test_conf  
	(cd $(BENCH_LIB)/ublas ; make )

C_BLAS : test_conf  
	(cd $(BENCH_LIB)/C_BLAS ; make )

INTEL_BLAS : test_conf  
	(cd $(BENCH_LIB)/INTEL_BLAS ; make )

STL_algo : test_conf  
	(cd $(BENCH_LIB)/STL_algo ; make )

tiny_blitz : test_conf  
	(cd $(BENCH_LIB)/tiny_blitz ; make )

tvmet : test_conf  
	(cd $(BENCH_LIB)/tvmet ; make )




distclean:
	@for DIR in `find . -name [Mm]akefile -exec dirname {} \;`;\
	do\
	(\
		cd $$DIR ;\
		make clean ;\
	)\
	done

exec:
	@for DIR in `find . -name main -exec dirname {} \;`;\
	do\
	(\
		echo starting $$DIR calculation ;\
		cd $$DIR ;\
		./main ;\
		echo done ;\
	)\
	done


