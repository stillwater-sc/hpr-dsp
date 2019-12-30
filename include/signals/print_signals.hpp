#pragma once
// print_signals.cpp: functions to aid in inspecting DSP data structures
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-DSP project, which is released under an MIT Open Source license.
#include <algorithm> // for min_element/max_element

namespace sw {
namespace hprdsp {

template<typename Scalar>
std::ostream& DisplaySample(std::ostream& ostr, const Scalar& value, const Scalar& min, const Scalar& max) {
	// min is 0 stars
	// 0   is 40 stars
	// max is 80 stars
	int maxStars = 80;
	float sample = float(value);
	float range = float(max - min);
	float midPoint = range/2.0f;
	float portion = (sample + midPoint)/range;
	int ub = int(maxStars * portion);
	for (int i = 0; i < ub; i++) {
		ostr << "*";
	}
	return ostr << std::endl;
}

template<typename Scalar, typename Vector>
void DisplaySignal(std::ostream& ostr, const Vector& samples) {
	Scalar min = *std::min_element(std::begin(samples), std::end(samples));
	Scalar max = *std::max_element(std::begin(samples), std::end(samples));
	// create a horizontal display
	int cnt = 0;
	ostr << std::fixed << std::setprecision(3);
	for (unsigned i = 0; i < size(samples); ++i) {
		ostr << std::setw(3) << cnt++ << " " << std::setw(6) << samples[i] << " ";
		DisplaySample(ostr, samples[i], min, max);
	}
	ostr << std::setprecision(5);
}

} // namespace hprdsp
} // namespace sw
