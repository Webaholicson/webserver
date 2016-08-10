#ifndef CONFIG_H_
#define CONFIG_H_

#define MAX_REQUEST_SIZE 			8192
#define MAX_CONNECTIONS 			100
#define ACCESS_LOG 			  		"log/access.log"
#define ERROR_LOG 			  		"log/error.log"
#define INDEX_FILE			  		"www/index.html"
#define PID_FILE			  			"webserver.pid"
#define DEFAULT_CONFIG_FILE		"default.conf"
#define MAX_SITES 						50
#define SITE_NUM_FIELDS 			7
#define DEFAULT_CONFIG_PATH 	"conf.d"
#define DEFAULT_MAX_INCLUDE 	20
#define CONFIG_FILE_SIZE 			1024

#include "site.h"

struct Config {
	int listen_port;
	const char *host;
	char *include[DEFAULT_MAX_INCLUDE];
	int num_of_sites;
	struct Site *sites[MAX_SITES];
};

extern int load_config_files ();

extern int parse_config_file (const char *filename);

extern int setup_config (FILE *fp);

extern int setup_default_config (void);

#endif
