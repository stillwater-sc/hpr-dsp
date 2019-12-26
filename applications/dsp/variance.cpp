// variance.cpp: example program calculating the variance of a signal
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-DSP project, which is released under an MIT Open Source license.

// configure the number system to use
#include <universal/posit/posit>
// pull in HPR-BLAS
#include <hprblas>

constexpr double PI = 3.141592653589793238460;  // best practice for C++

int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;
	using namespace sw::hprblas;

	constexpr size_t nrSamples = 32;
	int nrOfFailedTestCases = 0;

	using Scalar = posit<32,2>;
	using Samples = mtl::dense_vector<Scalar>;

	Samples s1(nrSamples), s2(nrSamples), s3(nrSamples);

	Scalar twoPi = 2.0 * PI;
	Scalar base = twoPi / Scalar(nrSamples);
	for (int i = 0; i < nrSamples; i++) {
		s1[i] = sin(Scalar(i) * base) + 1;
	}

	// calculate mean value of input signal
	Scalar mean = sw::hprblas::sum(nrSamples, s1)/Scalar(nrSamples);
	s2 = mean;
	s3 = s1 - s2;
	
	cout << "s1\n" << s1 << endl;	
	cout << "s2\n" << s2 << endl;	
	cout << "s3\n" << s3 << endl;



	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
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
