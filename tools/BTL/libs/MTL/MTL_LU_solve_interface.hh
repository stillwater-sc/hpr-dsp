//=====================================================
// File   :  MTL_LU_solve_interface.hh
// Author :  L. Plagne <laurent.plagne@edf.fr)>        
// Copyright (C) EDF R&D,  lun sep 30 14:23:27 CEST 2002
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
#ifndef MTL_LU_SOLVE_INTERFACE_HH
#define MTL_LU_SOLVE_INTERFACE_HH

#include "mtl/matrix.h"
#include "mtl/mtl.h"
#include "mtl/utils.h"
#include "utilities.h"
#include <vector>
#include <string>
#include <mtl/lu.h>

using namespace mtl;

template<class real>
class MTL_LU_solve_interface : public MTL_interface<real>
{

public :

  typedef typename MTL_interface<real>::gene_matrix gene_matrix;
  typedef typename MTL_interface<real>::gene_vector gene_vector;


  typedef dense1D<int> Pivot_Vector;

  inline static void new_Pivot_Vector(Pivot_Vector & pivot,int N)
  {

    pivot.resize(N);

  }

  inline static void free_Pivot_Vector(Pivot_Vector & pivot)
  {
    
    return;

  }
  

  
  inline static void LU_factor(gene_matrix & LU, Pivot_Vector & pivot, int N)
  {

    lu_factor(LU,pivot);

  }

  inline static void LU_solve(const gene_matrix & LU, const Pivot_Vector pivot, const gene_vector &B, gene_vector X, int N)
  {

    lu_solve(LU,pivot,B,X);

  }







};

#endif
