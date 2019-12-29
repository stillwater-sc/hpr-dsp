// generator.cpp: example program to generate sampled signals
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-DSP project, which is released under an MIT Open Source license.

// configure the number system to use
#include <universal/posit/posit>
// pull in HPR-DSP
#include <hprdsp>

constexpr double PI = 3.141592653589793238460;  // best practice for C++


int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;
	using namespace sw::hprblas;
	using namespace sw::hprdsp;

	constexpr unsigned nrSamples = 32;
	int nrOfFailedTestCases = 0;

	using Scalar = posit<16, 1>;
	using Vector = mtl::dense_vector<Scalar>;


	Scalar freq = 1.0e6; // 1MHz
	Scalar vlow = 0;  // Volt
	Scalar vhigh = 1; // Volt
	Scalar startTime = 0; // in seconds
	Sinusoid<Scalar> sine(freq, vlow, vhigh);
	SignalGenerator<Scalar> signalgen(2 * freq, startTime);
	Vector samples = signalgen.sample<Vector>(nrSamples, &sine);

	cout << "samples\n" << samples << endl;

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
