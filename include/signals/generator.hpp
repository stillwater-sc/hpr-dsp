#pragma once
// generators.hpp: finite impulse response filters
// 
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-DSP project, which is released under an MIT Open Source License

#include "periodic_signal.hpp"
namespace sw {
namespace hprdsp {

// signal generator
template<typename Real>
class Sampler {
public:
	Sampler(const Real& sampleFrequencyInHertz, const Real& startTime) : period(Real(1.0)/sampleFrequencyInHertz), currentTime(startTime) {}
	inline void settime(const Real& newTime) {
		currentTime = newTime;
	}
	Real tick() {
		Real s = currentTime;
		currentTime += period;
		return s;
	}
private:
	Real period; // sample frequency in Hertz, period is in seconds
	Real currentTime;   // current time in sec           <--- the base dimension has a big impact on the dynamic range requirements of the abstract Real
};

template<typename Real>
class SignalGenerator : public Sampler<Real> {
public:
	SignalGenerator(const Real& sampleFrequencyInHertz, const Real& startTime)
		: Sampler(sampleFrequencyInHertz, startTime) {}

	template<typename Vector>
	Vector sample(unsigned nrSamples, PeriodicSignal<Real>* f) {
		Vector signal(nrSamples);
		for (unsigned i = 0; i < nrSamples; ++i) {
			signal[i] = (*f)(tick());
		}
		return signal;
	}
};

} // namespace hprdsp
} // namespace sw
