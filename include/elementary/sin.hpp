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


template<bool value>
using enableif = typename std::enable_if<value>::type;

	// is T a Vector?
template<typename T>
struct isVector { constexpr static bool value = false; };

template<typename R>
struct isVector<mtl::dense_vector<R> > { constexpr static bool value = true; };

	/*
	MTL already has vector-valued trigonometry functions

// vector valued sine function
template<typename Vector, enableif< isVector<Vector>::value >...>
Vector sin(const Vector& timeSamples) {
	Vector v(size(timeSamples));
	unsigned i = 0;
	for (auto t : timeSamples) {
		v[i++] = sin(t);
	}
	return v;
}
	*/

} // namespace hprdsp
} // namespace sw
