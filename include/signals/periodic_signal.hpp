// periodic_signal.hpp: stateful signal model that represents a periodic signal through time
// 
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the HPR-DSP project, which is released under an MIT Open Source License

namespace sw {
namespace hprdsp {

// abstract base class representing a signal concept
template<typename Real>
class PeriodicSignal {
public:
	PeriodicSignal(Real freq, Real vlow, Real vhigh) : freq(freq), vlow(vlow), vhigh(vhigh) {}
	virtual Real operator()(Real t) = 0;
	inline Real frequency() const { return freq; }
	inline Real low() const { return vlow; }
	inline Real high() const { return vhigh; }
private:
	Real freq; // cycles per second
	Real vlow, vhigh;
};

// sinusoid
template<typename Real>
class Sinusoid : public PeriodicSignal<Real> {
public:
	Sinusoid(Real freq, Real vlow, Real vhigh) 
	  : PeriodicSignal(freq, vlow, vhigh)
	{
		voltageRange = vhigh - vlow;
	}
	virtual Real operator()(Real t) {
		return sin(t*frequency()) * voltageRange;
	}
private:
	Real voltageRange;
};


} // namespace hprdsp
} // namespace sw
