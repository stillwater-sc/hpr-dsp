// dot.cpp: example program contrasting a BLAS L1 ?dot routine between FLOAT and POSIT
//
// Copyright (C) 2017-2018 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-BLAS project, which is released under an MIT Open Source license.

#include <ratio>
#include <chrono>
#include <iostream>
#include <ctime>

#include <vector>
#include <hprblas>

using namespace std;
using namespace sw::hprblas;

int main(int argc, char** argv)
try {
	const size_t nbits = 32;
	const size_t es = 2;
	const size_t vecSize = 1024;

	int nrOfFailedTestCases = 0;
	// steady_clock example
	using namespace std::chrono;

	cout << "DOT product examples" << endl;
	vector<float> x(vecSize), y(vecSize);
	float fresult;

	randomVectorFillAroundOneEPS(vecSize, x);  //	sampleVector("x", x);
	randomVectorFillAroundOneEPS(vecSize, y);  // 	sampleVector("y", y);
	fresult = sw::hprblas::dot<float>(vecSize, x, 1, y, 1);
	cout << "DOT product is " << setprecision(20) << fresult << endl;

	using Posit = sw::unum::posit<nbits, es>;
	vector<Posit> px(vecSize), py(vecSize);
	Posit presult;
	randomVectorFillAroundOneEPS(vecSize, px);  //	sampleVector("px", px);
	randomVectorFillAroundOneEPS(vecSize, py);  // 	sampleVector("py", py);

	steady_clock::time_point t1 = steady_clock::now();
	presult = sw::hprblas::dot<Posit>(vecSize, px, 1, py, 1);
	steady_clock::time_point t2 = steady_clock::now();
	double ops = vecSize * 2.0; // dot product is vecSize products and vecSize adds
	cout << "DOT product is " << setprecision(20) << presult << endl;
	//sampleVector("px", px);  // <-- currently shows bad conversions....

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	double elapsed = time_span.count();
	std::cout << "It took " << elapsed << " seconds." << std::endl;
	std::cout << "Performance " << (uint32_t) (ops / (1000*elapsed)) << " KOPS" << std::endl;
	std::cout << std::endl;

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
