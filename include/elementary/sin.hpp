#pragma once
// sin.hpp: vector sine function
// 
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-DSP project, which is released under an MIT Open Source License
#include <boost/numeric/mtl/mtl.hpp>

namespace sw {
namespace hprdsp {

	// TODO: we need to protect this to access a Vector concept (needs to have size() and operator[]
	// Vector = mtl::dense_vector<Real>
// vector valued sine function
template<typename Vector>
Vector myVectorSine(const Vector& timeSamples) {
	Vector v(size(timeSamples));
	unsigned i = 0;
	for (auto t : timeSamples) {
		v[i++] = sin(t);
	}
	return v;
}

} // namespace hprdsp
} // namespace sw
