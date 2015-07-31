#ifndef SITE_H_
#define SITE_H_

#include "deps/lua/src/lua.h"
#include "deps/lua/src/lauxlib.h"
#include "deps/lua/src/lualib.h"
#include "deps/http-parser/http_parser.h"

#include "config.h"

#define SITE_NUM_FIELDS 7

struct Site {
	char *name;
	char *dir;
	char *email;
	char *index;
	char *error_log;
	char *access_log;
};

extern int setup_site (FILE *fp);

extern int set_site_field (struct Site *site, char *key, char *val);

extern struct Site *match_site (char *request);

extern int header_field_cb (http_parser *_, const char *at, size_t len);

extern int header_value_cb (http_parser *_, const char *at, size_t len);

#endif
