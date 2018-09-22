//=====================================================
// File   :  MTL_interface.hh
// Author :  L. Plagne <laurent.plagne@edf.fr)>        
// Copyright (C) EDF R&D,  lun sep 30 14:23:26 CEST 2002
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
#ifndef MTL_INTERFACE_HH
#define MTL_INTERFACE_HH

#include "mtl/matrix.h"
#include "mtl/mtl.h"
#include "mtl/utils.h"
#include "utilities.h"
#include <vector>
#include <string>

using namespace mtl;

template<class real>
class MTL_interface{

public :

  typedef real real_type ;

  typedef std::vector<real>  stl_vector;
  typedef std::vector<stl_vector > stl_matrix;
  
  static inline std::string name( void )
  {
    return "MTL";
  }



  typedef typename matrix< real, 
			   rectangle<>, 
			   dense<>, 
			   column_major >::type gene_matrix;
  
  typedef dense1D<real> gene_vector;
  

  static void free_matrix(gene_matrix & A, int N){

    return ;
  }
  
  static void free_vector(gene_vector & B){
    
    return ;
    
  }
  
  static inline void matrix_from_stl(gene_matrix & A_mtl, stl_matrix & A_stl){
    
    gene_matrix A(A_stl.size(),A_stl[0].size());
    for (int i=0; i<A_stl.size() ; i++){
      for (int j=0; j<A_stl[i].size() ; j++){
	A(i,j)=A_stl[i][j];
      }
      
    }
    
    A_mtl=A;
    
  }
  
  static inline void vector_from_stl(gene_vector & B, stl_vector & B_stl){
    
    B.resize(B_stl.size());
    
    for (int i=0; i<B_stl.size() ; i++){
      B[i]=B_stl[i];
    }
  }
  
  static inline void vector_to_stl(gene_vector & B, stl_vector & B_stl){
    
    for (int i=0; i<B_stl.size() ; i++){
      B_stl[i]=B[i];
    }
  }
  
  static inline void matrix_to_stl(gene_matrix & A, stl_matrix & A_stl){
    
    int N=A_stl.size();
    
    for (int i=0;i<N;i++){
      A_stl[i].resize(N);
      for (int j=0;j<N;j++){
	A_stl[i][j]=A(i,j);
      }
    }
  
  }

  static inline void copy_vector(const gene_vector & source, gene_vector & cible, int N){
    for (int i=0;i<N;i++){
      cible[i]=source[i];
    }
  }

  static inline void copy_matrix(const gene_matrix & source, gene_matrix & cible, int N){
    for (int i=0;i<N;i++){
      for (int j=0;j<N;j++){
	cible(i,j)=source(i,j);
      }
    }
  }


  static inline void matrix_vector_product(gene_matrix & A, gene_vector & B, gene_vector & X, int N)
  {
    scale(X,0.0);
    mult(A,B,X);
  }

  static inline void matrix_matrix_product(gene_matrix & A, gene_matrix & B, gene_matrix & X, int N)
  {
    scale(X,0.0);
    mult(A,B,X);

   //  typedef typename gene_matrix::shape Shape;

//     matmat_mult(A,B,X,Shape());
    
  }

  static inline void ata_product(gene_matrix & A, gene_matrix & X, int N)
  {
    scale(X,0.0);
    mult(trans(A),A,X);
  }

  static inline void aat_product(gene_matrix & A, gene_matrix & X, int N)
  {
    scale(X,0.0);
    mult(A,trans(A),X);
  }



  static inline void axpy(const real coef, gene_vector & X, gene_vector & Y, int N)
  { 
    add(scaled(X,coef),Y);

  }





};

#endif
