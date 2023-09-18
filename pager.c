#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "table.h"
#include "pager.h"

Pager* pager_open(const char* filename) {
	int fd;
	Pager* pager;

	if((fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR)) < 0) {
		fprintf(stderr, "Unable to open file\n");
		exit(1);
	}

	off_t file_length = lseek(fd, 0, SEEK_END);

	if((pager = malloc(sizeof(Pager))) == NULL) {
		fprintf(stderr, "malloc failed in pager_open\n");
		exit(1);
	}

	pager->file_descriptor = fd;
	pager->file_length = file_length;
	pager->num_pages = (file_length / PAGE_SIZE);

	if (file_length % PAGE_SIZE != 0) {
		fprintf(stderr, "DB file is not a whole number of pages. Corrupt file\n");
		exit(1);
	}

	for(uint32_t i = 0; i < TABLE_MAX_PAGES; i++ ) {
		pager->pages[i] = NULL;
	}

	return pager;

}

void* get_page(Pager* pager, uint32_t page_num) {
	if (page_num > TABLE_MAX_PAGES) {
		printf("Tried to fetch page number out of bounds. %d > %d\n", page_num, TABLE_MAX_PAGES);
		exit(1);
	}

	if (pager->pages[page_num] == NULL) {
		// Cache miss
		void* page = malloc(PAGE_SIZE);
		uint32_t num_pages = pager->file_length / PAGE_SIZE;

		if(pager->file_length % PAGE_SIZE) {
			num_pages += 1;	
		}

		// search if it exists
		if(page_num <= num_pages) {
			lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
			ssize_t bytes_read = read(pager->file_descriptor, page, PAGE_SIZE);
			if (bytes_read == -1) {
				printf("%s\n", "Error reading file");
				exit(1);
			}
		}

		pager->pages[page_num] = page;

		if(page_num >= pager->num_pages) {
			pager->num_pages = page_num + 1;
		}
	}

	return pager->pages[page_num];
}

uint32_t get_unused_page_num(Pager* pager) {
	return pager->num_pages;
}

void pager_flush(Pager* pager, uint32_t page_num) {
	if (pager->pages[page_num] == NULL) {
		printf("%s\n", "Tried to flush null page");
		exit(1);
	}

	off_t offset = lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
	if(offset == -1) {
		printf("%s\n", "Error seeking");
		exit(1);
	}

	ssize_t bytes_written = write(pager->file_descriptor, pager->pages[page_num], PAGE_SIZE);
	if(bytes_written == -1) {
		printf("%s\n", "Error writing");
		exit(1);
	}
}
