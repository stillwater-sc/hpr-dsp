// generators.hpp: finite impulse response filters
// 
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-DSP project, which is released under an MIT Open Source License

namespace sw {
namespace hprdsp {

template<typename Scalar>
struct ElementaryFunction {
	ElementaryFunction() {};
	virtual Scalar operator()(Scalar x) = 0;
};

template<typename Scalar, typename Vector>
Vector signalgen(const Scalar& start, const Scalar& end, const Scalar& incr, ElementaryFunction<Scalar>* f) {
	Scalar N = (end - start)/incr;
	Vector signal(ceil(N));
	signal[0] = (*f)(start);
	return signal;
}

} // namespace hprdsp
} // namespace sw
