#include <stdio.h>
#include <stdlib.h>
#include "execute.h"
#include "table.h"
#include "cursor.h"
#include "pager.h"
#include "tree.h"

ExecuteResult execute_btree(Statement* statement, Table* table) {
	print_tree(table->pager, 0, 0);
	return EXECUTE_SUCCESS;
}

ExecuteResult execute_const(Statement* statement) {
	print_const();
	return EXECUTE_SUCCESS;
}

ExecuteResult execute_insert(Statement *statement, Table *table)
{

	Row *row_to_insert = &(statement->row_to_insert);
	uint32_t key_to_insert = row_to_insert->id;
	Cursor* cursor = table_find(table, key_to_insert);

	void* node = get_page(table->pager, cursor->page_num);
	uint32_t num_cells = *leaf_node_num_cells(node);

	if(cursor->cell_num < num_cells) {
		uint32_t key_at_index = *leaf_node_key(node, cursor->cell_num);
		if (key_at_index == key_to_insert) {
			return EXECUTE_DUPLICATE_KEY;
		}
	}

	leaf_node_insert(cursor, row_to_insert->id, row_to_insert);

	return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *statement, Table *table)
{
	Cursor *cursor = table_start(table);

	Row row;
	while (!(cursor->end_of_table))
	{
		deserialize_row(cursor_value(cursor), &row);
		print_row(&row);
		cursor_advance(cursor);
	}

	free(cursor);
	return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement *statement, Table *table)
{
	switch (statement->type)
	{
		case (STATEMENT_BTREE):
			return execute_btree(statement, table);
			break;
			
		case (STATEMENT_CONST):
			return execute_const(statement);
			break;

		case (STATEMENT_INSERT):
			return execute_insert(statement, table);
			break;

		case (STATEMENT_SELECT):
			return execute_select(statement, table);
			break;

		default:
			return EXECUTE_FAILED;
			break;
	}
}
