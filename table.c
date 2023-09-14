#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "table.h"
#include "pager.h"
#include "tree.h"

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);

const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

// TABLES
const uint32_t PAGE_SIZE = 4096;

void serialize_row(Row* source, void* dest) {
	memcpy(dest + ID_OFFSET, &(source->id), ID_SIZE);
	memcpy(dest + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
	memcpy(dest + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void* source, Row* dest) {
	memcpy(&(dest->id), source + ID_OFFSET, ID_SIZE);
	memcpy(&(dest->username), source + USERNAME_OFFSET, USERNAME_SIZE);
	memcpy(&(dest->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

void print_row(Row* row) {
	printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

Table* db_open(const char* filename) {
	Pager* pager = pager_open(filename);

	Table* table;
	table = malloc(sizeof(Table));

	table->pager = pager;
	table->root_page_num = 0;

	if(pager->num_pages == 0) {
		// New database file. Initialize page 0 as leaf node
		void* root_node = get_page(pager, 0);
		initialize_leaf_node(root_node);
	}

	return table;

}

void db_close(Table* table) {
	Pager* pager = table->pager;

	for (uint32_t i = 0; i < pager->num_pages; i++) {
		if (pager->pages[i] == NULL) {
			continue;
		}
		pager_flush(pager, i);
		free(pager->pages[i]);
		pager->pages[i] = NULL;
	}

	int result = close(pager->file_descriptor);
	if(result == -1) {
		printf("Error closing db file\n");
		exit(1);
	}

	for(uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
		void* page = pager->pages[i];
		if (page) {
			free(page);
			pager->pages[i] = NULL;
		}
	}
	free(pager);
	free(table);
}
