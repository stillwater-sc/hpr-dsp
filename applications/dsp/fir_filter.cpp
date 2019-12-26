// fir_filter.cpp example program showing a FIR filter using error-free custom posit configurations
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-DSP project, which is released under an MIT Open Source license.

#define MTL_INITIALIZER_LISTS
#include <boost/numeric/mtl/mtl.hpp>
// select and configure the number system 
#include <universal/posit/posit>


const double pi = 3.14159265358979323846;  // best practice for C++

int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;

	const size_t nbits = 16;
	const size_t es = 1;
	const size_t vecSize = 32;
	int nrOfFailedTestCases = 0;

	posit<nbits, es> p;
	vector< posit<nbits, es> > sinusoid(vecSize), weights(vecSize);

	for (int i = 0; i < vecSize; i++) {
		sinusoid[i] = sin((float(i) / float(vecSize)) *2.0 * pi);

		weights[i] = 0.5f;
	}

	// dot product
	posit<nbits, es> fir;
	fir = 0.0f;
	for (int i = 0; i < vecSize; i++) {
		fir += sinusoid[i] * weights[i];
	}
	cout << "Value is " << fir << endl;

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
