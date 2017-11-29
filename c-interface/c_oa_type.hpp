#ifndef __C_OA_TYPE_HPP__
#define __C_OA_TYPE_HPP__

#include "../ArrayPool.hpp"
#include "../NodePool.hpp"

#define L 0
#define R 1

extern "C" {

  void array_assign_array(void* &A, void* &B, int & pa, int & pb);

  void node_assign_node(void* &A, void* &B);

  void destroy_array(void* A);

  void destroy_node(void* A);

  void display_array(void* A);

  void display_node(void* A);

  void ones(void* & ptr, int m, int n, int k, int stencil_width = 1, 
    int data_type = DATA_DOUBLE, 
    MPI_Fint fcomm = 0);

  void zeros(void* & ptr, int m, int n, int k, int stencil_width = 1, 
    int data_type = DATA_DOUBLE, 
    MPI_Fint fcomm = 0);

  void rands(void* & ptr, int m, int n, int k, int stencil_width = 1, 
    int data_type = DATA_DOUBLE, 
    MPI_Fint fcomm = 0);

  void seqs(void* & ptr, int m, int n, int k, int stencil_width = 1, 
    int data_type = DATA_DOUBLE, 
    MPI_Fint fcomm = 0);
    
  ///:mute
  ///:set TYPE = [['int'], ['float'], ['double']]
  ///:endmute
  ///:for t in TYPE
  void consts_${t[0]}$(void* &ptr, int m, int n, int k, ${t[0]}$ val, 
    int stencil_width = 1, MPI_Fint fcomm = 0);

  ///:endfor

  ///:for t in TYPE
  void new_seqs_scalar_node_${t[0]}$(void* &ptr, ${t[0]}$ val, 
    MPI_Fint fcomm = 0);

  ///:endfor

  void new_node_array(void* &ptr, void* &ap);

  void new_node_op2(void* &ptr, int nodetype, void* &u, void* &v);

  void new_node_op1(void* &ptr, int nodetype, void* &u);
}

#endif