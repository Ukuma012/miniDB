#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include "parser.h"
#include "pager.h"

#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)

extern const uint32_t ID_SIZE;
extern const uint32_t USERNAME_SIZE;
extern const uint32_t EMAIL_SIZE;

extern const uint32_t ID_OFFSET;
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET;
extern const uint32_t ROW_SIZE;

// TABLES
extern const uint32_t PAGE_SIZE;

typedef struct
{
	Pager *pager;
	uint32_t root_page_num;
} Table;

void serialize_row(Row *, void *);
void deserialize_row(void *, Row *);
void print_row(Row *);
Table *db_open(const char *);
void db_close(Table *);

#endif
