#ifndef TREE_H
#define TREE_H

#include <stdint.h>

 uint32_t* leaf_node_num_cells(void*);
 void* leaf_node_cell(void*, uint32_t);
 uint32_t* leaf_node_key(void*, uint32_t);
 void* leaf_node_value(void*, uint32_t);
 void initialize_leaf_node(void*);

#endif
