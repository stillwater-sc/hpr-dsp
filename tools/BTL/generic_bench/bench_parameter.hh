//=====================================================
// File   :  bench_parameter.hh
// Author :  L. Plagne <laurent.plagne@edf.fr)>        
// Copyright (C) EDF R&D,  lun sep 30 14:23:16 CEST 2002
//=====================================================
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
#ifndef BENCH_PARAMETER_HH
#define BENCH_PARAMETER_HH

// minimal time for each measurement
#define REAL_TYPE double
// minimal time for each measurement
#define MIN_TIME 2.0 
// nb of point on bench curves
#define NB_POINT 100
// min vector size for axpy bench
#define MIN_AXPY 20
// max vector size for axpy bench
#define MAX_AXPY 1000000
// min matrix size for matrix vector product bench
#define MIN_MV 10
// max matrix size for matrix vector product bench
#define MAX_MV 1000
// min matrix size for matrix matrix product bench
#define MIN_MM 10
// max matrix size for matrix matrix product bench
#define MAX_MM 1000
// min matrix size for LU bench
#define MIN_LU 10
// max matrix size for LU bench
#define MAX_LU 1000
// max size for tiny vector and matrix
#define TINY_MV_MAX_SIZE 5
// default nb_sample for x86 timer
#define DEFAULT_NB_SAMPLE 1000



#endif
