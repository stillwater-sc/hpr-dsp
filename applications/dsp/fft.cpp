// fft.cpp example program showing a fast fourier transform using error-free custom posit configurations
//
// Copyright (C) 2017-2019 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-DSP project, which is released under an MIT Open Source license.

#include "common.hpp"

/*

Mathematical 	C++ Symbol	Decimal Representation
Expression
pi				M_PI		3.14159265358979323846
pi/2			M_PI_2		1.57079632679489661923
pi/4			M_PI_4		0.785398163397448309616
1/pi			M_1_PI		0.318309886183790671538
2/pi			M_2_PI		0.636619772367581343076
2/sqrt(pi)		M_2_SQRTPI	1.12837916709551257390
sqrt(2)			M_SQRT2		1.41421356237309504880
1/sqrt(2)		M_SQRT1_2	0.707106781186547524401
e				M_E			2.71828182845904523536
log_2(e)		M_LOG2E		1.44269504088896340736
log_10(e)		M_LOG10E	0.434294481903251827651
log_e(2)		M_LN2		0.693147180559945309417
log_e(10)		M_LN10		2.30258509299404568402

*/

constexpr double PI = 3.141592653589793238460;  // best practice for C++

//using Scalar = float;
using Scalar = sw::unum::posit<32,2>;
using Complex = std::complex<Scalar>;
using Samples = mtl::dense_vector<Complex>;

#include <valarray>
// Cooley–Tukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
void fft_dac(std::valarray<Complex>& x)
{
	const size_t N = x.size();
	if (N <= 1) return;

	// divide
	std::valarray<Complex> even = x[std::slice(0, N / 2, 2)];
	std::valarray<Complex>  odd = x[std::slice(1, N / 2, 2)];

	// conquer
	fft_dac(even);
	fft_dac(odd);

	// combine
	for (size_t k = 0; k < N / 2; ++k)
	{
		Complex t = Complex(std::polar(1.0, -2 * PI * k / N)) * odd[k];
		x[k] = even[k] + t;
		x[k + N / 2] = even[k] - t;
	}
}

// Cooley-Tukey FFT (in-place, breadth-first, decimation-in-frequency)
// Better optimized but less intuitive
void fft(Samples &x) {
	// DFT
	size_t N = size(x), k = N, n;
	double thetaT = 3.14159265358979323846264338328L / N;
	Complex phiT = Complex(cos(thetaT), -sin(thetaT)), T;
	while (k > 1) {
		n = k;
		k >>= 1;
		phiT = phiT * phiT;
		T = 1.0L;
		for (size_t l = 0; l < k; l++) {
			for (size_t a = l; a < N; a += n) {
				size_t b = a + k;
				Complex t = x[a] - x[b];
				x[a] += x[b];
				x[b] = t * T;
			}
			T *= phiT;
		}
	}
	// Decimate
	unsigned int m = (unsigned int)log2(N);
	for (unsigned int a = 0; a < N; a++)
	{
		unsigned int b = a;
		// Reverse bits
		b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
		b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
		b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
		b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
		b = ((b >> 16) | (b << 16)) >> (32 - m);
		if (b > a)
		{
			Complex t = x[a];
			x[a] = x[b];
			x[b] = t;
		}
	}
	//// Normalize (This section make it not working correctly)
	//Complex f = 1.0 / sqrt(N);
	//for (unsigned int i = 0; i < N; i++)
	//	x[i] *= f;
}

// inverse fft (in-place)
void ifft(Samples& x)
{
	// conjugate the complex numbers
	x = mtl::conj(x);

	// forward fft
	fft(x);

	// conjugate the complex numbers again
	x = mtl::conj(x);

	// scale the numbers
	Complex scale = size(x);
	x /= scale;
}

void ForwardInverseFFT(size_t nrSamples) {
	Samples sinusoid(nrSamples), weights(nrSamples), scratch(nrSamples);

	Scalar twoPi = 2.0 * PI;
	Scalar base = twoPi / Scalar(nrSamples);
	for (int i = 0; i < nrSamples; i++) {
		sinusoid[i] = sin(Scalar(i) * base);
		scratch[i] = sinusoid[i];
		weights[i] = Scalar(0.5);
	}


	// input data
	std::cout << "input samples" << std::endl;
	for (int i = 0; i < nrSamples; ++i) {
		std::cout << scratch[i] << std::endl;
	}

	// forward fft
	fft(scratch);

	std::cout << "fft" << std::endl;
	for (int i = 0; i < nrSamples; ++i) {
		std::cout << scratch[i] << std::endl;
	}

	// inverse fft
	ifft(scratch);

	std::cout << std::endl << "ifft" << std::endl;
	for (int i = 0; i < nrSamples; ++i) {
		std::cout << scratch[i] << std::endl;
	}

	std::cout << std::endl << "difference between input and fwd/inv fft result\n";
	std::cout << "#   real    imag\n";
	Scalar reDiff, imDiff;
	for (int i = 0; i < nrSamples; ++i) {
		reDiff = scratch[i].real() - sinusoid[i].real();
		imDiff = scratch[i].imag() - sinusoid[i].imag();
		std::cout << std::setw(3) << i << "  " << std::setw(12) << reDiff << ", " << std::setw(12) << imDiff << std::endl;
	}
}

int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;

	const size_t nrSamples = 32;
	int nrOfFailedTestCases = 0;

	ForwardInverseFFT(nrSamples);

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
