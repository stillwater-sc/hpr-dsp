// lu_decomposition.cpp example program comparing float vs posit LU decomposition algorithms
//
// Copyright (C) 2017-2018 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-BLAS project, which is released under an MIT Open Source license.

#include "common.hpp"
#include <hprblas>

template<size_t nbits, size_t es, size_t capacity = 10>
void CroutCycle(mtl::dense2D< sw::unum::posit<nbits, es> >& A, mtl::dense_vector< sw::unum::posit<nbits, es> >& x, mtl::dense_vector< sw::unum::posit<nbits, es> >& b)
{
	using namespace sw::hprblas;

	size_t d = size(b);
	assert(size(A) == d*d);
	mtl::dense2D< sw::unum::posit<nbits, es> > LU(d,d);
	using namespace std::chrono;
	steady_clock::time_point t1 = steady_clock::now();
	Crout(A, LU);
	steady_clock::time_point t2 = steady_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	double elapsed = time_span.count();
	std::cout << "Crout took " << elapsed << " seconds." << std::endl;
	std::cout << "Performance " << (uint32_t)(d*d*d / (1000 * elapsed)) << " KOPS/s" << std::endl;
	SolveCrout(LU, b, x);
	printMatrix(std::cout, "Crout LU", LU);
	printVector(std::cout, "Crout Solution", x);
}

template<size_t nbits, size_t es, size_t capacity = 10>
void CroutFDPCycle(mtl::dense2D< sw::unum::posit<nbits, es> >& A, mtl::dense_vector< sw::unum::posit<nbits, es> >& x, mtl::dense_vector< sw::unum::posit<nbits, es> >& b)
{
	using namespace sw::hprblas;

	size_t d = size(b);
	assert(size(A) == d*d);
	mtl::dense2D< sw::unum::posit<nbits, es> > LU(d, d);
	using namespace std::chrono;
	steady_clock::time_point t1 = steady_clock::now();
	CroutFDP(A, LU);
	steady_clock::time_point t2 = steady_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	double elapsed = time_span.count();
	std::cout << "Crout with FDP took " << elapsed << " seconds." << std::endl;
	std::cout << "Performance " << (uint32_t)(d*d*d / (1000 * elapsed)) << " KOPS/s" << std::endl;
	SolveCroutFDP(LU, b, x);
	printMatrix(std::cout, "Crout FDP LU", LU);
	printVector(std::cout, "Crout FDP Solution", x);
}

template<size_t nbits, size_t es, size_t capacity = 10>
void ComparePositDecompositions(std::vector< sw::unum::posit<nbits, es> >& A, std::vector< sw::unum::posit<nbits, es> >& x, std::vector< sw::unum::posit<nbits, es> >& b) {
	size_t d = b.size();
	assert(A.size() == d*d);
	using namespace sw::hprblas;
	std::vector< sw::unum::posit<nbits, es> > LU(d*d);

	{
		using namespace std::chrono;
		steady_clock::time_point t1 = steady_clock::now();
		Crout(A, LU);
		steady_clock::time_point t2 = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		double elapsed = time_span.count();
		std::cout << "Crout took " << elapsed << " seconds." << std::endl;
		std::cout << "Performance " << (uint32_t)(d*d*d / (1000 * elapsed)) << " KOPS/s" << std::endl;

		SolveCrout(LU, b, x);
		printMatrix(std::cout, "Crout LU", LU);
		printVector(std::cout, "Solution", x);
	}

	std::cout << std::endl;
#if 0
	{
		using namespace std::chrono;
		steady_clock::time_point t1 = steady_clock::now();
		DoolittleFDP(A, LU);
		steady_clock::time_point t2 = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		double elapsed = time_span.count();
		std::cout << "Doolittle took " << elapsed << " seconds." << std::endl;
		std::cout << "Performance " << (uint32_t)(d*d*d / (1000 * elapsed)) << " KOPS/s" << std::endl;
		SolveDoolittle(LU, b, x);
		printMatrix(std::cout, "Doolittle LU", LU);
		printVector(std::cout, "Solution", x);
	}


	std::cout << std::endl;

	{
		using namespace std::chrono;
		steady_clock::time_point t1 = steady_clock::now();
		CholeskyFDP(A, LU);
		steady_clock::time_point t2 = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		double elapsed = time_span.count();
		std::cout << "Cholesky took " << elapsed << " seconds." << std::endl;
		std::cout << "Performance " << (uint32_t)(d*d*d / (1000 * elapsed)) << " KOPS/s" << std::endl;
		SolveCholesky(LU, b, x);
		printMatrix(std::cout, "Cholesky LU", LU);
		printVector(std::cout, "Solution", x);
	}
#endif
}


template<typename Ty>
void CompareIEEEDecompositions(std::vector<Ty>& A, std::vector<Ty>& x, std::vector<Ty>& b) {
	size_t d = b.size();
	assert(A.size() == d*d);
	using namespace sw::hprblas;
	std::vector<Ty> LU(d*d);

	{
		using namespace std::chrono;
		steady_clock::time_point t1 = steady_clock::now();
		Crout(A, LU);
		steady_clock::time_point t2 = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		double elapsed = time_span.count();
		std::cout << "Crout took " << elapsed << " seconds." << std::endl;
		std::cout << "Performance " << (uint32_t)(d*d*d / (1000 * elapsed)) << " KOPS/s" << std::endl;

		SolveCrout(LU, b, x);
		printMatrix(std::cout, "Crout LU", LU);
		printVector(std::cout, "Solution", x);
	}


	std::cout << std::endl;

	{
		using namespace std::chrono;
		steady_clock::time_point t1 = steady_clock::now();
		Doolittle(A, LU);
		steady_clock::time_point t2 = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		double elapsed = time_span.count();
		std::cout << "Doolittle took " << elapsed << " seconds." << std::endl;
		std::cout << "Performance " << (uint32_t)(d*d*d / (1000 * elapsed)) << " KOPS/s" << std::endl;
		SolveCrout(LU, b, x);
		printMatrix(std::cout, "Doolittle LU", LU);
		printVector(std::cout, "Solution", x);

		SolveDoolittle(LU, b, x);
		printMatrix(std::cout, "Doolittle LU", LU);
		printVector(std::cout, "Solution", x);
	}


	std::cout << std::endl;

	{
		using namespace std::chrono;
		steady_clock::time_point t1 = steady_clock::now();
		Cholesky(A, LU);
		steady_clock::time_point t2 = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		double elapsed = time_span.count();
		std::cout << "Cholesky took " << elapsed << " seconds." << std::endl;
		std::cout << "Performance " << (uint32_t)(d*d*d / (1000 * elapsed)) << " KOPS/s" << std::endl;
		SolveCrout(LU, b, x);
		printMatrix(std::cout, "Cholesky LU", LU);
		printVector(std::cout, "Solution", x);

		SolveCholesky(LU, b, x);
		printMatrix(std::cout, "Cholesky LU", LU);
		printVector(std::cout, "Solution", x);
	}
}


int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;
	using namespace sw::hprblas;

	// a 32-bit float and a <27,1> posit have the same number of significand bits around 1.0
	constexpr size_t nbits = 27;
	constexpr size_t es = 1;
	constexpr size_t capacity = 10;

	typedef float            IEEEType;
	typedef posit<nbits, es> PositType;
	cout << "Using " << dynamic_range(posit<nbits, es>()) << endl;

#if 0
	float eps = std::numeric_limits<float>::epsilon();
	float epsminus = 1.0f - eps;
	float epsplus = 1.0f + eps;
	// We want to solve the system Ax=b
	int d = 5;
	vector<IEEEType> Uieee = {     // define the upper triangular matrix
		1.0, 2.0, 3.0, 4.0, 5.0,
		0.0, 1.0, 2.0, 3.0, 4.0,
		0.0, 0.0, 1.0, 2.0, 3.0,
		0.0, 0.0, 0.0, 1.0, 2.0,
		0.0, 0.0, 0.0, 0.0, 1.0,
	};
	vector<IEEEType> Lieee = {     // define the lower triangular matrix
		1.0, 0.0, 0.0, 0.0, 0.0,
		2.0, 1.0, 0.0, 0.0, 0.0,
		3.0, 2.0, 1.0, 0.0, 0.0,
		4.0, 3.0, 2.0, 1.0, 0.0,
		5.0, 4.0, 3.0, 2.0, 1.0,
	};
	vector<IEEEType> Aieee(d*d);
	matmul(Lieee, Uieee, Aieee);   // construct the A matrix to solve
								   // define a difficult solution
	vector<IEEEType> xieee = {
		epsplus,
		epsplus,
		epsplus,
		epsplus,
		epsplus
	};
	vector<IEEEType> bieee(d);
	matvec(Aieee, xieee, bieee);   // construct the right hand side

	vector<PositType> Uposit = {   // define the upper triangular matrix
		1.0, 2.0, 3.0, 4.0, 5.0,
		0.0, 1.0, 2.0, 3.0, 4.0,
		0.0, 0.0, 1.0, 2.0, 3.0,
		0.0, 0.0, 0.0, 1.0, 2.0,
		0.0, 0.0, 0.0, 0.0, 1.0,
	};
	vector<PositType> Lposit = {   // define the lower triangular matrix
		1.0, 0.0, 0.0, 0.0, 0.0,
		2.0, 1.0, 0.0, 0.0, 0.0,
		3.0, 2.0, 1.0, 0.0, 0.0,
		4.0, 3.0, 2.0, 1.0, 0.0,
		5.0, 4.0, 3.0, 2.0, 1.0,
	};
	vector<PositType> Aposit(d*d);
	matmul(Lposit, Uposit, Aposit);   // construct the A matrix to solve
	printMatrix(cout, "A", Aposit);
	// define a difficult solution
	vector<PositType> xposit = {
		epsplus,
		epsplus,
		epsplus,
		epsplus,
		epsplus
	};
	vector<PositType> bposit(d);
	matvec<nbits, es>(Aposit, xposit, bposit);   // construct the right hand side

	cout << "LinearSolve regular dot product" << endl;
	CompareIEEEDecompositions(Aieee, xieee, bieee);
	cout << endl << ">>>>>>>>>>>>>>>>" << endl;
	cout << "LinearSolve fused-dot product" << endl;
	ComparePositDecompositions(Aposit, xposit, bposit);
#endif
	mtl::dense_vector<PositType> x(5), b(5), xprime(5);
	mtl::dense2D<PositType> A(5, 5);
	mtl::mat::uniform_rand(A, -1.0, 1.0);

	x = 1.0;
	b = A * x;
	cout << endl; 
	printMatrix(cout, "Matrix A(5x5):\n", A); 
	cout << endl;
	cout << endl;
	printVector(cout, "RHS    b(5)  :\n", b);
	cout << endl;
	CroutCycle<nbits,es,capacity>(A, xprime, b);
	printVector(cout, "RHS    x(5)  :\n", xprime);
	cout << endl;
	CroutFDPCycle<nbits, es, capacity>(A, xprime, b);
	printVector(cout, "RHS    x(5)  :\n", xprime);
	return EXIT_SUCCESS;
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const posit_arithmetic_exception& err) {
	std::cerr << "Uncaught posit arithmetic exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (std::runtime_error& err) {
	std::cerr << "Uncaught run-time exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}
