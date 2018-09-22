main:	Makefile mean.o smooth regularize
	g++ -o main mean.o
mean.o: mean.cxx
	g++ -c mean.cxx -I../generic_bench -I../generic_bench/utils #-D_DEBUG_

smooth: smooth.o
	g++ -o smooth smooth.o
smooth.o: smooth.cxx
	g++ -c smooth.cxx -I../generic_bench -I../generic_bench/utils #-D_DEBUG_

regularize: regularize.o
	g++ -o regularize regularize.o
regularize.o: regularize.cxx
	g++ -c regularize.cxx -I../generic_bench -I../generic_bench/utils #-D_DEBUG_


clean:
	rm -f *.o *.ii *.int.c *.s *~ \#* main core rm *.a
	rm -rf ti_files
	rm -f smooth regularize *.dat
