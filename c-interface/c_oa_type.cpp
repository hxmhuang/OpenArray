#include "c_oa_type.hpp"
#include "../Function.hpp"
#include "../Operator.hpp"

extern "C" {

  void array_assign_array(void* &A, void* &B, int & pa, int & pb) {
    destroy_array(A);
    if (pb == R) {
      A = B;
      B = NULL;
    } else {
      int dt = (*(ArrayPtr*) B)->get_data_type();
      ArrayPtr ap = ArrayPool::global()->get(
        (*(ArrayPtr*) B)->get_partition(), dt
      );
      switch(dt) {
        case DATA_INT:
          oa::internal::copy_buffer(
            (int*) (ap->get_buffer()),
            (int*) ((*(ArrayPtr*) B)->get_buffer()),
            ap->buffer_size()
          );
          break;
        case DATA_FLOAT:
          oa::internal::copy_buffer(
            (float*) (ap->get_buffer()),
            (float*) ((*(ArrayPtr*) B)->get_buffer()),
            ap->buffer_size()
          );
          break;
        case DATA_DOUBLE:
          oa::internal::copy_buffer(
            (double*) (ap->get_buffer()),
            (double*) ((*(ArrayPtr*) B)->get_buffer()),
            ap->buffer_size()
          );
          break;
      }
      ArrayPtr* tmp = new ArrayPtr();
      *tmp = ap;
      A = (void*) tmp;
    }
    pa = L;
  }

  void node_assign_node(void* &A, void* &B) {
    destroy_node(A);
    A = B;
  }

  void destroy_array(void* A) {
    //cout<<"destroy_array called"<<endl;
    if (A != NULL) delete((ArrayPtr*) A);
  }

  void destroy_node(void* A) {
    if (A != NULL) delete((NodePtr*) A);
  }

  void display_array(void* A) {
    (*(ArrayPtr*) A)->display();
  }

  void display_node(void* A) {
    (*(NodePtr*) A)->display();
  }

  void ones(void* & ptr, int m, int n, int k, int stencil_width, 
    int data_type, MPI_Fint fcomm) {
    MPI_Comm comm = MPI_Comm_f2c(fcomm);
    Shape s = {m, n, k};
    ArrayPtr ap = oa::funcs::ones(comm, s, stencil_width, data_type);

    ArrayPtr* A = new ArrayPtr();
    *A = ap;

    if (ptr != NULL) destroy_array(ptr);
    ptr = (void*) A;
  }

  void zeros(void* & ptr, int m, int n, int k, int stencil_width, 
    int data_type, MPI_Fint fcomm) {
    MPI_Comm comm = MPI_Comm_f2c(fcomm);
    Shape s = {m, n, k};
    ArrayPtr ap = oa::funcs::zeros(comm, s, stencil_width, data_type);
    
    ArrayPtr* A = new ArrayPtr();
    *A = ap;

    if (ptr != NULL) destroy_array(ptr);
    ptr = (void*) A;
  }

  void rands(void* & ptr, int m, int n, int k, int stencil_width, 
    int data_type, MPI_Fint fcomm) {
    MPI_Comm comm = MPI_Comm_f2c(fcomm);
    Shape s = {m, n, k};
    ArrayPtr ap = oa::funcs::rand(comm, s, stencil_width, data_type);
    
    ArrayPtr* A = new ArrayPtr();
    *A = ap;

    if (ptr != NULL) destroy_array(ptr);
    ptr = (void*) A;
  }

  void seqs(void* & ptr, int m, int n, int k, int stencil_width, 
    int data_type, MPI_Fint fcomm) {
    MPI_Comm comm = MPI_Comm_f2c(fcomm);
    Shape s = {m, n, k};
    ArrayPtr ap = oa::funcs::seqs(comm, s, stencil_width, data_type);

    ArrayPtr* A = new ArrayPtr();
    *A = ap;

    if (ptr != NULL) destroy_array(ptr);
    ptr = (void*) A;
  }

  ///:mute
  ///:set TYPE = [['int'], &
                ['float'], &
                ['double']]
  ///:endmute

  ///:for t in TYPE
  void consts_${t[0]}$(void* &ptr, int m, int n, int k, ${t[0]}$ val, 
    int stencil_width, MPI_Fint fcomm) {
    MPI_Comm comm = MPI_Comm_f2c(fcomm);
    Shape s = {m, n, k};
    ArrayPtr ap = oa::funcs::consts(comm, s, val, stencil_width);
    ArrayPtr* A = new ArrayPtr();
    *A = ap;

    if (ptr != NULL) destroy_array(ptr);
    ptr = (void*) A;
  }

  ///:endfor

  ///:for t in TYPE
  void new_seqs_scalar_node_${t[0]}$(void* &ptr, ${t[0]}$ val, 
    MPI_Fint fcomm) {
    MPI_Comm comm = MPI_Comm_f2c(fcomm);
    NodePtr np = oa::ops::new_seqs_scalar_node(comm, val);
    NodePtr* A = new NodePtr();
    *A = np;

    if (ptr != NULL) destroy_array(ptr);
    ptr = (void*) A;
  }
    
  ///:endfor

  void new_node_array(void* &ptr, void* &ap) {
    NodePtr np = oa::ops::new_node(*(ArrayPtr*)ap);
    NodePtr* A = new NodePtr();
    *A = np;

    if (ptr != NULL) destroy_node(ptr);
    ptr = (void*) A;
  }

  void new_node_op2(void* &ptr, int nodetype, void* &u, void* &v) {
    NodePtr np = oa::ops::new_node((NodeType)nodetype, *(NodePtr*)u, *(NodePtr*)v);
    NodePtr* A = new NodePtr();
    *A = np;

    if (ptr != NULL) destroy_node(ptr);
    ptr = (void*) A;
  }

  void new_node_op1(void* &ptr, int nodetype, void* &u) {
    NodePtr np = oa::ops::new_node((NodeType)nodetype, *(NodePtr*)u);
    NodePtr* A = new NodePtr();
    *A = np;

    if (ptr != NULL) destroy_node(ptr);
    ptr = (void*) A;
  }
}
