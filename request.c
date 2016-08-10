#include "request.h"

int header_field_cb (http_parser *_, const char *at, size_t len)
{
  return 0;
}

int header_value_cb (http_parser *_, const char *at, size_t len)
{
  return 0;
}
