#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include "parser.h"

#define size_of_attribute(Struct, Attribute) sizeof(((Struct* )0)->Attribute)
#define TABLE_MAX_PAGES 100

extern const uint32_t ID_SIZE;
extern const uint32_t USERNAME_SIZE;
extern const uint32_t EMAIL_SIZE;

extern const uint32_t ID_OFFSET;
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET;
extern const uint32_t ROW_SIZE;

// TABLES
extern const uint32_t PAGE_SIZE;
extern const uint32_t ROWS_PER_PAGE;
extern const uint32_t TABLE_MAX_ROWS;

typedef struct {
	uint32_t num_rows;
	void* pages[TABLE_MAX_PAGES];
} Table;

void serialize_row(Row*, void*);
void deserialize_row(void*, Row*);
void* row_slot(Table*, uint32_t);
void print_row(Row*);
Table* new_table();
void free_table(Table*);

#endif
