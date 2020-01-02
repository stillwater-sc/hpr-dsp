#pragma once
// timeRange.hpp: vector of time samples
// 
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-DSP project, which is released under an MIT Open Source License

#include "boost/numeric/mtl/mtl.hpp"

namespace sw {
namespace hprdsp {

template<typename Real>
mtl::dense_vector<Real>  timeRange(const Real& start, const Real& step, const Real& end) {
	using Vector = mtl::dense_vector<Real>;
	unsigned nrSamples = unsigned( (end - start)/step);
	Vector v(nrSamples);
	Real sample = start;
	for (unsigned i = 0; i < nrSamples; ++i) {
		v[i] = sample;
		sample += step;
	}
	return v;
};

} // namespace hprdsp
} // namespace sw
