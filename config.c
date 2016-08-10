#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <regex.h>

#include "server.h"

int load_config_files()
{
	DIR * config_dir = opendir (DEFAULT_CONFIG_PATH);

	if (config_dir == NULL) {
		perror ("opendir");
		exit (EXIT_FAILURE);
	}

	struct dirent *config_file = malloc (sizeof (struct dirent));

	char *filename = malloc (PATH_MAX);
	char *cwd = get_current_dir_name();

	while ((config_file = readdir (config_dir)) != NULL) {
		if (config_file->d_type == DT_REG) {
			strcpy (filename, cwd);
			strcat (filename, "/");
			strcat (filename, DEFAULT_CONFIG_PATH);
			strcat (filename, "/");
			strcat (filename, config_file->d_name);
			parse_config_file (filename);
		}
	}

	free (cwd);
	free (filename);
	closedir (config_dir);

	return 0;
}

int parse_config_file (const char *filename)
{
	FILE *fp = fopen (filename, "r");

	if (fp == NULL) {
		perror ("fopen");
		exit (EXIT_FAILURE);
	}

	if (strstr (filename, ".conf")) {
		setup_config (fp);
	} else if (strstr (filename, ".site")) {
		setup_site (fp);
	}

	return 0;
}

int setup_default_config()
{
	instance->config->listen_port = 8080;
	instance->config->host = "127.0.0.1";
	return 0;
}

int setup_config (FILE *fp)
{
	char line[200];
	char *pattern;
	regex_t compiled;
	// pattern = "/^[[:alnum:]_]+[[:space:]]+.*;$/";
	pattern = "^([[:alpha:]_]+)[[:space:]]+(.*);";

	if (regcomp(&compiled, pattern, REG_EXTENDED) != 0) {
		printf ("Error compiling RegExp: %s \n", pattern);
		regfree (&compiled);
		exit (EXIT_FAILURE);
	}

	while (fgets (line, 200, fp) != NULL) {
			regmatch_t matchptr;
			if (regexec(&compiled, &line, 1, &matchptr, 0) == REG_NOMATCH) {
				printf ("Error matching RegExp: %s %s \n", pattern, line);
				regfree (&compiled);
				exit (EXIT_FAILURE);
			}
	}

	return 0;
}
