//=====================================================
// File   :  C_interface.hh
// Author :  L. Plagne <laurent.plagne@edf.fr)>        
// Copyright (C) EDF R&D,  lun sep 30 14:23:23 CEST 2002
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
#ifndef C_INTERFACE_HH
#define C_INTERFACE_HH

#include <vector>

template<class real>
class C_interface{
  
public :
  
  typedef real real_type ;

  typedef std::vector<real>  stl_vector;
  typedef std::vector<stl_vector > stl_matrix;

  typedef real * ptr_real ;
  
  typedef ptr_real * gene_matrix;
  
  typedef real * gene_vector;
  
  static void free_matrix(gene_matrix & A, int N){
    
    for (int i=0;i<N;i++){
      delete A[i];
    }
    
    delete A;
  }

  static void free_vector(gene_vector & B){

    delete B;
    
  }

  static inline void matrix_from_stl(gene_matrix & A, stl_matrix & A_stl){

    int N=A_stl.size();
    
    A = new ptr_real[N];  
    for (int i=0;i<N;i++){
      real * ligne = new real[N];
      A[i]=ligne;
      for (int j=0;j<N;j++){
	A[i][j]=A_stl[i][j];
      }
    }
    
  }
  
  static inline void vector_from_stl(gene_vector & B, stl_vector & B_stl){
    
    int N=B_stl.size();
    
    B=new real[N];  
    for (int i=0;i<N;i++){
      B[i]=B_stl[i];
    }
  }
  
  static inline void vector_to_stl(gene_vector & B, stl_vector & B_stl){
    
    int N=B_stl.size();
    
    for (int i=0;i<N;i++){
      B_stl[i]=B[i];
    }
  }

  static inline void matrix_to_stl(gene_matrix & A, stl_matrix & A_stl){
    
    int N=A_stl.size();
    
    for (int i=0;i<N;i++){
      A_stl[i].resize(N);
      for (int j=0;j<N;j++){
	A_stl[i][j]=A[i][j];
      }
    }
  
  }
  
  
 static inline std::string name( void )
  {
    return "C";
  }
  
  static inline void copy_matrix(gene_matrix & source, gene_matrix & cible, int N)
  {
    for (int i=0;i<N;i++){
      for (int j=0;j<N;j++){
	cible[i][j]=source[i][j];
      }
    }
    
  }

  static inline void copy_vector(gene_vector & source, gene_vector & cible, int N)
  {
    for (int i=0;i<N;i++){
      cible[i]=source[i];
    }
    
  }


  static inline void matrix_vector_product(const gene_matrix & A, const gene_vector & B, gene_vector & X, int N)
  {
    for (int i=0;i<N;i++){
      real somme=0.0;
      for (int j=0;j<N;j++){
	somme+=A[i][j]*B[j];
      }
      X[i]=somme;
    }
    
  }

  static inline void matrix_matrix_product(const gene_matrix & A, const gene_matrix & B, gene_matrix & X, int N)
  {
    
    real somme;
    for (int i=0;i<N;i++){
      for (int j=0;j<N;j++){
	somme=0.0;
	for (int k=0;k<N;k++){
	  somme+=A[i][k]*B[k][j];
	}
	X[i][j]=somme;
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
	  somme+=A[k][i]*A[k][j];
	}
	X[i][j]=somme;
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
	  somme+=A[i][k]*A[j][k];
	}
	X[i][j]=somme;
      }
    }
  }


  static inline void axpy(real coef, const gene_vector & X, gene_vector & Y, int N)
  {

    for (int i=0;i<N;i++){
      Y[i]+=coef*X[i];
    }
    
  }
  
  
};

#endif
