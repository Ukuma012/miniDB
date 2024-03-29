#include <stdio.h>
#include <stdlib.h>
#include "table.h"
#include "pager.h"
#include "tree.h"
#include "cursor.h"

Cursor *table_start(Table *table)
{
	Cursor* cursor = table_find(table, 0);

	void* node = get_page(table->pager, cursor->page_num);
	uint32_t num_cells = *leaf_node_num_cells(node);
	cursor->end_of_table = (num_cells == 0);

	return cursor;
}

Cursor* table_find(Table* table, uint32_t key) {
	uint32_t root_page_num = table->root_page_num;
	void* root_node = get_page(table->pager, root_page_num);

	if (get_node_type(root_node) == NODE_LEAF) {
		return leaf_node_find(table, root_page_num, key);
	} else {
		return internal_node_find(table, root_page_num, key);
	}
}


void cursor_advance(Cursor *cursor)
{
	uint32_t page_num = cursor->page_num;
	void* node = get_page(cursor->table->pager, page_num);

	cursor->cell_num += 1;
	if(cursor->cell_num >= (*leaf_node_num_cells(node))) {
		uint32_t next_page_num = *leaf_node_next_leaf(node);
		if (next_page_num == 0) {
			cursor->end_of_table = true;
		} else {
			cursor->page_num = next_page_num;
			cursor->cell_num = 0;
		}
	}
}

void *cursor_value(Cursor *cursor)
{
	uint32_t page_num = cursor->page_num;
	void* page = get_page(cursor->table->pager, page_num);
	return leaf_node_value(page, cursor->cell_num);
}

Cursor* leaf_node_find(Table* table, uint32_t page_num, uint32_t key) {
	void* node = get_page(table->pager, page_num);	
	uint32_t num_cells = *leaf_node_num_cells(node);

	Cursor* cursor = malloc(sizeof(Cursor));
	cursor->table = table;
	cursor->page_num = page_num;

	// Binary Search
	uint32_t min_index = 0;
	uint32_t max_index = num_cells;
	while(max_index != min_index) {
		uint32_t index = (min_index + max_index) / 2;
		uint32_t key_at_index = *leaf_node_key(node, index);

		if(key == key_at_index) {
			cursor->cell_num = index;
			return cursor;
		}

		if (key < key_at_index) {
			max_index = index;
		} else {
			min_index = index + 1;
		}
	}

	cursor->cell_num = min_index;
	return cursor;
}

Cursor* internal_node_find(Table* table, uint32_t page_num, uint32_t key) {
	void* node = get_page(table->pager, page_num);

	uint32_t child_index = internal_node_find_child(node, key);
	uint32_t child_num = *internal_node_child(node, child_index);
	void* child = get_page(table->pager, child_num);
	switch (get_node_type(child)) {
		case NODE_LEAF:
			return leaf_node_find(table, child_num, key);
		case NODE_INTERNAL:
			return internal_node_find(table, child_num, key);
		default:
			return 0;
	}
}