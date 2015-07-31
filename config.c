#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "config.h"

int load_config_files()
{
	DIR * config_dir = opendir (DEFAULT_CONFIG_PATH);

	if (config_dir == NULL) {
		perror ("opendir");
		exit (EXIT_FAILURE);
	}

	struct dirent *config_file = malloc (sizeof (struct dirent));
	server_config->luastate	= luaL_newstate();
	luaL_openlibs (server_config->luastate);

	char *filename = malloc (PATH_MAX);
	char *cwd = get_current_dir_name();

	load_wscl();

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

int load_wscl()
{
	char *filename = malloc (PATH_MAX);
	char *cwd = get_current_dir_name();

	strcpy (filename, cwd);
	strcat (filename, "/conf.d/");
	strcat (filename, "wscl.lua");
	int result = luaL_dofile (server_config->luastate, filename);

	if (result > 1) {
		printf ("Could not open file: %s %d \n", filename, result);
		exit (EXIT_FAILURE);
	}

	free (filename);
	return 0;
}

int parse_config_file (char *filename)
{
	FILE *fp = fopen (filename, "r");

	if (fp == NULL) {
		perror (fopen);
		exit (EXIT_FAILURE);
	}

	if (strstr (filename, ".conf")) {
		setup_config (fp);
	} else if (strstr (filename, ".site")) {
		setup_site (fp);
	}

	return 0;
}

int setup_config (FILE *fp)
{
	return 0;
}
