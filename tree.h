#ifndef TREE_H
#define TREE_H

#include <stdint.h>
#include "cursor.h"

#define size_of(Size) sizeof(Size)

typedef enum {
	NODE_INTERNAL,
	NODE_LEAF
} NodeType;


extern const uint32_t LEAF_NODE_MAX_CELLS;

uint32_t* leaf_node_num_cells(void*);
void* leaf_node_cell(void*, uint32_t);
uint32_t* leaf_node_key(void*, uint32_t);
void* leaf_node_value(void*, uint32_t);
void initialize_leaf_node(void*);
void leaf_node_insert(Cursor*, uint32_t, Row*);
void print_const();
void print_leaf_node(void*);
NodeType get_node_type(void*);
void set_node_type(void*, NodeType);

#endif
