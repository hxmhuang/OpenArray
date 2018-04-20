
#ifndef __NODE_HPP__
#define __NODE_HPP__
#include "Array.hpp"
#include "common.hpp"
#include <vector>
#include <memory>
#include <bitset>
#include <string>

class Node;

typedef std::shared_ptr<Node> NodePtr;
typedef std::vector<NodePtr> NodeList;

class Node {
private:
  int id;
  ArrayPtr m_data;
  NodeList m_input;
  NodeList m_output;
  size_t m_hash;
  NodeType m_type;
  bool m_is_seqs = false;
  bool m_is_scalar = false;
  int m_depth = 0;
  Shape m_global_shape = {{1, 1, 1}};
  int m_data_type;
  int3 m_lbound = {{0, 0, 0}};
  int3 m_rbound = {{0, 0, 0}};
  bool m_update_boundary = false;
  int pos = -1;
  bool m_is_pseudo = false;
  std::bitset<3> m_bs = std::bitset<3>(7);

  Box m_ref;
  int m_slice;

public:
  Node();

  Node(NodePtr u);
  //Node(ArrayPtr array);
  ~Node();
  
  void display(char const *prefix = "");

  int input_size() const;
  
  NodePtr& input(int i);

  NodePtr output(int i);

  void add_input(int pos, NodePtr in);

  void add_output(int pos, NodePtr out);

  void set_type(NodeType type);

  void set_data(const ArrayPtr& ptr);

  void set_id(int _id);

  int get_id() const;
  
  size_t hash();

  void set_hash(size_t);

  NodeType type();

  ArrayPtr& get_data();

  bool has_data();

  void reset();

  void clear_input();

  void clear_output();

  void clear_data();
  
  // MPI_Comm_world [1x1x1]
  bool is_scalar() const;

  void set_scalar(bool value=true);

  // MPI_Comm_self 
  bool is_seqs() const;

  void set_seqs(bool value=true);

  // MPI_Comm_self & [1x1x1]
  bool is_seqs_scalar() const;

  void set_depth(int d);

  void set_depth(int left_child, int right_child);

  int get_depth() const;

  void set_shape(const Shape &s);

  Shape shape();

  void set_data_type(int dt);

  int get_data_type() const;

  int3 get_lbound();

  int3 get_rbound();

  void set_lbound(int3 lb);

  void set_rbound(int3 rb);

  void set_lbound(int3 left_lb, int3 right_lb);

  void set_rbound(int3 left_rb, int3 ribht_rb);

  void set_update(bool flag = true);

  bool need_update();

  void set_pos(int p);

  int get_pos();

  void set_pseudo(bool ps);

  bool is_pseudo();

  void set_bitset(string s);

  void set_bitset();

  void set_bitset(bitset<3> bs);

  bitset<3> get_bitset();

  void set_ref(const Box& b);

  Box& get_ref();

  bool is_ref() const;

  bool is_ref_data() const;

  void set_slice(int k);

  int get_slice();

  ArrayPtr& get_ref_data();
};


#endif
