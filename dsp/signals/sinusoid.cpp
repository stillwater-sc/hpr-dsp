// sinusoid.cpp: example program to generate vector valued signals
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-DSP project, which is released under an MIT Open Source license.

// configure the number system to use
#include <universal/posit/posit>
// pull in HPR-DSP
#include <hprdsp>

constexpr double PI = 3.141592653589793238460;

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

	// create the time vector
	Vector t = timeRange<Scalar>(0, 0.0125, 1);
	Scalar twoPi = 2 * PI;
	// Vector v = sin(twoPi * t);	
	// Vector ts = twoPi * t; // this doesn't work as there isn't a suitable conversion from scaled_view to Vector
	
	// let's do the scale of the time vector manually
	Vector ts(size(t));
	unsigned i = 0;
	for (auto t_step : t) {
		ts[i++] = twoPi * t_step;
	}
	Vector v;
	v = sin(ts);  // vector-valued sin function

	DisplaySignal<Scalar, Vector>(cout, v);

	cout << "Is Vector a proper vector: " << (isVector<Vector>::value ? "yes" : "no") << endl;

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
