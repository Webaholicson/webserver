#ifndef REQUEST_H_
#define REQUEST_H_

#include "deps/http-parser/http_parser.h"

extern int header_field_cb (http_parser *_, const char *at, size_t len);

extern int header_value_cb (http_parser *_, const char *at, size_t len);

#endif
