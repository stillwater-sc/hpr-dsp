//=====================================================
// File   :  blitz_interface.hh
// Author :  L. Plagne <laurent.plagne@edf.fr)>        
// Copyright (C) EDF R&D,  lun sep 30 14:23:30 CEST 2002
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
#ifndef BLITZ_INTERFACE_HH
#define BLITZ_INTERFACE_HH

#include "blitz/array.h"
#include <blitz/vector-et.h>
#include <blitz/vecwhere.h>
#include <vector>

BZ_USING_NAMESPACE(blitz)

template<class real>
class blitz_interface{
  
public :
  
  typedef real real_type ;

  typedef std::vector<real>  stl_vector;
  typedef std::vector<stl_vector > stl_matrix;
  
  typedef blitz::Array<real, 2>  gene_matrix;
  //typedef blitz::Array<real, 1>  gene_vector;
  typedef blitz::Vector<real>  gene_vector;
  
  static inline std::string name( void )
  {
    return "blitz";
  }
  
 
  static void free_matrix(gene_matrix & A, int N){
    
    return ;
  }
  
  static void free_vector(gene_vector & B){
    
    return ;
    
  }
  
  static inline void matrix_from_stl(gene_matrix & A, stl_matrix & A_stl){
    
    A.resize(A_stl.size(),A_stl[0].size());
    
    for (int i=0; i<A_stl.size() ; i++){
      for (int j=0; j<A_stl[i].size() ; j++){
	A(i,j)=A_stl[i][j];
      }
      
    }
  }
  
  static inline void vector_from_stl(gene_vector & B, stl_vector & B_stl){
    
    B.resize(B_stl.size());
    
    for (int i=0; i<B_stl.size() ; i++){
      B(i)=B_stl[i];
    }
  }
  
  static inline void vector_to_stl(gene_vector & B, stl_vector & B_stl){
    
    for (int i=0; i<B_stl.size() ; i++){
      B_stl[i]=B(i);
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
  
  
  
  static inline void matrix_vector_product_slow(gene_matrix & A, gene_vector & B, gene_vector & X, int N)
  {
    firstIndex i;
    secondIndex j;  
    

    X =  sum(A(i,j)*B(j),j);
    
  }
    

  static inline void matrix_matrix_product(const gene_matrix & A, const gene_matrix & B, gene_matrix & X, int N)
  {
    
    real somme;
    for (int i=0;i<N;i++){
      for (int j=0;j<N;j++){
	somme=0.0;
	for (int k=0;k<N;k++){
	  somme+=A(i,k)*B(k,j);
	}
	X(i,j)=somme;
      }
    }
  }

  static inline void ata_product(const gene_matrix & A, gene_matrix & X, int N)
  {
    
    real somme;
    for (int i=0;i<N;i++){
      for (int j=0;j<N;j++){
	somme=0.0;
	for (int k=0;k<N;k++){
	  somme+=A(k,i)*A(k,j);
	}
	X(i,j)=somme;
      }
    }
  }

  static inline void aat_product(const gene_matrix & A, gene_matrix & X, int N)
  {
    
    real somme;
    for (int i=0;i<N;i++){
      for (int j=0;j<N;j++){
	somme=0.0;
	for (int k=0;k<N;k++){
	  somme+=A(i,k)*A(j,k);
	}
	X(i,j)=somme;
      }
    }
  }

  static inline void matrix_vector_product(gene_matrix & A, gene_vector & B, gene_vector & X, int N)
  {
    
    real somme;
    
    for (int i=0 ; i< N ; i++){
      
      somme =  0.0;
      
      for (int j=0 ; j< N ; j++){
	
	somme+=A(i,j)*B[j];
	
      }
      
      X[i]=somme;
    }
    
  }

  static inline void axpy(const real coef, const gene_vector & X, gene_vector & Y, int N)
  {    
    Y+=coef*X;
  }

  static inline void copy_matrix(const gene_matrix & source, gene_matrix & cible, int N){
    for (int i=0;i<N;i++){
      for (int j=0;j<N;j++){
	cible(i,j)=source(i,j);
      }
    }
  }

  static inline void copy_vector(const gene_vector & source, gene_vector & cible, int N){
    for (int i=0;i<N;i++){
      cible(i)=source(i);
    }
  }




};

  
#endif
