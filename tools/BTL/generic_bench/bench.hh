//=====================================================
// File   :  bench.hh
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
#ifndef BENCH_HH
#define BENCH_HH
#include "bench_parameter.hh"
#include <iostream>
#include "utilities.h"
#include "size_lin_log.hh"
#include "dump_file_x_y.hh"
#include <vector>
#include <string>
#include "timers/portable_perf_analyzer.hh"
//#include "timers/mixed_perf_analyzer.hh"
//#include "timers/x86_perf_analyzer.hh"
//#include "timers/STL_perf_analyzer.hh"

using namespace std;

template <template<class> class Perf_Analyzer, class Action>
void bench( int size_min, int size_max, int nb_point ){

  // bench name 
  
  string filename="bench_"+Action::name()+".dat";

  INFOS("starting " <<filename);

  // utilities 
  
  std::vector<double> tab_mflops(nb_point);
  std::vector<int> tab_sizes(nb_point);

  // matrices and vector size calculations

  size_lin_log(nb_point,size_min,size_max,tab_sizes);

  // loop on matrix size

  Perf_Analyzer<Action> perf_action;

  for (int i=nb_point-1;i>=0;i--){

    INFOS("size=" <<tab_sizes[i]<<"   ("<<nb_point-i<<"/"<<nb_point<<")");
    tab_mflops[i]= perf_action.eval_mflops(tab_sizes[i]);

  }

  // dump the result in a file  :

  dump_file_x_y(tab_sizes,tab_mflops,filename);

}

// default Perf Analyzer

template <class Action>
void bench( int size_min, int size_max, int nb_point ){

  // if the rdtsc is not available :
  bench<Portable_Perf_Analyzer,Action>(size_min,size_max,nb_point);
  // if the rdtsc is available :
  //  bench<Mixed_Perf_Analyzer,Action>(size_min,size_max,nb_point);


  // Only for small problem size. Otherwize it will be too long
  //bench<X86_Perf_Analyzer,Action>(size_min,size_max,nb_point);
  //bench<STL_Perf_Analyzer,Action>(size_min,size_max,nb_point);

}

#endif
