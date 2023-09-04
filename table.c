#include <string.h>
#include "table.h"

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
