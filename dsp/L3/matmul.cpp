// matmul.cpp example program comparing float vs posit matrix multiply algorithms
//
// Copyright (C) 2017-2018 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-BLAS project, which is released under an MIT Open Source license.

// warning C4996: 'std::copy::_Unchecked_iterators::_Deprecate': Call to 'std::copy' with parameters that may be unsafe - this call relies on the caller to check that the passed values are correct.
#pragma warning( disable : 4996)
#include "common.hpp"
#include <hprblas>

template<typename Ty>
void MeasureMatrixMultiplyPerformance(const std::string& metric) {
	using namespace std::chrono;
	unsigned dim = 32;
	for (unsigned i = 5; i < 8; ++i, dim *= 2) {
		std::cout << "Matrix dimensions are: " << dim << " x " << dim << std::endl;

		steady_clock::time_point t1 = steady_clock::now();
		mtl::dense2D<Ty> A(dim, dim), B(dim, dim), C(dim, dim);
		steady_clock::time_point t2 = steady_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
		double elapsed = time_span.count();
		std::cout << "  Construction     " << elapsed << " seconds.\n";

		t1 = steady_clock::now();
		mtl::mat::uniform_rand(A, -1.0, 1.0);
		mtl::mat::uniform_rand(B, -1.0, 1.0);
		t2 = steady_clock::now();
		time_span = duration_cast<duration<double>>(t2 - t1);
		elapsed = time_span.count();
		std::cout << "  Random fill      " << elapsed << " seconds.\n";

		t1 = steady_clock::now();
		int N = 10;
		for (int i = 0; i < N; ++i) {
			C = A * B;
		}
		t2 = steady_clock::now();
		time_span = duration_cast<duration<double>> (t2 - t1);
		elapsed = time_span.count();
		std::cout << "  Matmul iteration " << elapsed << " seconds.\n";
		double flops = double(N)*dim*dim*dim / elapsed * 1.0e-9;
		std::cout << "  Performance:     " << flops << " G" << metric << std::endl;
	}
}

int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;
	using namespace sw::hprblas;
	using namespace mtl;

	// a 32-bit float and a <27,1> posit have the same number of significand bits around 1.0
	constexpr size_t nbits = 27;
	constexpr size_t es = 2;
	constexpr size_t capacity = 10;

	typedef float            IEEEType;
	typedef posit<nbits, es> PositType;
	cout << dynamic_range(posit<nbits, es>()) << endl;

	float eps = std::numeric_limits<IEEEType>::epsilon();
	float epsminus = 1.0f - eps;
	float epsplus = 1.0f + eps;
	float max_fexp = std::numeric_limits<IEEEType>::max_exponent;
	float min_fexp = std::numeric_limits<IEEEType>::min_exponent;
	cout << "IEEE float: epsilon " << eps << " min exp " << min_fexp << " max exp " << max_fexp << endl;


		MeasureMatrixMultiplyPerformance<float>("spFLOPS");
		MeasureMatrixMultiplyPerformance<double>("dpFLOPS");
		MeasureMatrixMultiplyPerformance<PositType>("p27.2POPS");


	return EXIT_SUCCESS;
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (std::runtime_error& err) {
	std::cerr << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}