#ifndef SITE_H_
#define SITE_H_

#include "request.h"
#include "config.h"

struct Site {
	const char *name;
	const char *dir;
	const char *email;
	const char *index;
	const char *error_log;
	const char *access_log;
};

extern int setup_site (FILE *fp);

extern int set_site_field (struct Site *site, const char *key, const char *val);

extern struct Site *match_site (char *request);

#endif
