#ifndef CONFIG_H_
#define CONFIG_H_

#include "deps/lua/src/lua.h"
#include "deps/lua/src/lauxlib.h"
#include "deps/lua/src/lualib.h"

#include "site.h"

#define MAX_SITES 				50
#define DEFAULT_CONFIG_PATH 	"conf.d/default"

struct Config {
	int num_of_sites;
	struct Site *sites[MAX_SITES];
	lua_State *luastate;
};

struct Config *server_config;

extern int load_config_files ();

extern int parse_config_file (char *filename);

extern int load_wscl (void);

extern int setup_config (FILE *fp);

#endif
