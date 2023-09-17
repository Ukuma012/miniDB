#ifndef CURSOR_H
#define CURSOR_H

#include "table.h"
#include <stdbool.h>

typedef struct {
	Table* table;
	uint32_t page_num;
	uint32_t cell_num;
	bool end_of_table;
} Cursor;

Cursor* table_start(Table*);
void cursor_advance(Cursor*);
void* cursor_value(Cursor* cursor);

#endif
