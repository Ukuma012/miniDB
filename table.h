#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include "parser.h"

#define size_of_attribute(Struct, Attribute) sizeof(((Struct* )0)->Attribute)

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);

ID_OFFSET = 0;
USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_OFFSET;
ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

#endif
