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

template<typename Scalar>
struct Sine : public sw::hprdsp::ElementaryFunction<Scalar> {
	Sine() {};
	virtual Scalar operator()(Scalar x) {
		return sin(x);
	}
};

int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;
	using namespace sw::hprblas;
	using namespace sw::hprdsp;

	constexpr size_t nrSamples = 32;
	int nrOfFailedTestCases = 0;

	using Scalar = posit<16, 1>;
	using Vector = mtl::dense_vector<Scalar>;

	Vector sinusoid;

	ElementaryFunction<Scalar>* sine = new Sine<Scalar>();

	sinusoid = signalgen<Scalar,Vector>(Scalar(0), Scalar(PI), Scalar(PI / 4), sine);

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
