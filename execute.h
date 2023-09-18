#ifndef EXECUTE_H
#define EXECUTE_H

#include "parser.h"
#include "table.h"

typedef enum {
	EXECUTE_SUCCESS,
	EXECUTE_DUPLICATE_KEY,
	EXECUTE_FAILED
} ExecuteResult;

ExecuteResult execute_statement(Statement*, Table* );

#endif
