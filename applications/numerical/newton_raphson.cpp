// newton_raphson.cpp: example program showing the Newton-Raphson algorithm using valid arithmetic
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
// select and configure number system
#include <universal/posit/posit>

int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;

	const size_t nbits = 16;
	const size_t es = 1;
	const size_t vecSize = 32;




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