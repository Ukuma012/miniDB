#include <stdio.h>
#include <stdlib.h>
#include "execute.h"
#include "table.h"
#include "cursor.h"
#include "tree.h"

ExecuteResult execute_insert(Statement *statement, Table *table)
{
	void* node = get_page(table->pager, table->root_page_num);
	if ((*leaf_node_num_cells(node) >= LEAF_NODE_MAX_CELLS)) {
		return EXECUTE_TABLE_FULL;
	}

	Row *row_to_insert = &(statement->row_to_insert);
	Cursor *cursor = table_end(table);

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
