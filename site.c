#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "site.h"

char *site_table_keys[SITE_NUM_FIELDS] = { "name", "dir", "error_log", "access_log", "email", "index", "type" };

int setup_site (FILE *fp)
{
	char line[100];
	char *content = malloc (1024);
	strcpy (content, "");

	while (fgets (line, 100, fp) != NULL) {
		strcat (content, line);
	}

	fclose (fp);

	if (strlen (content) < 2) {
		return 0;
	}

	lua_getglobal (server_config->luastate, "wscl");
	lua_pushstring (server_config->luastate, content);
	lua_call (server_config->luastate, 1, 1);
	free (content);

	int i;
	int table = lua_gettop (server_config->luastate);
	struct Site *site = malloc (1024);

	for (i = 0; i < SITE_NUM_FIELDS; i++) {
		lua_getfield (server_config->luastate, table, site_table_keys[i]);
		char *val = lua_tostring(server_config->luastate, lua_gettop(server_config->luastate));
		set_site_field (site, site_table_keys[i], val);
		lua_pop (server_config->luastate, 1);
	}

	server_config->sites[server_config->num_of_sites] = site;
	server_config->num_of_sites++;

	lua_pop(server_config->luastate, 1);
//	printf ("On stack: %d\n", lua_gettop (server_config->luastate));

//	lua_Debug ar;
//	lua_getinfo (server_config->luastate, ">Snu", &ar);
//	printf ("%s \n", ar.source);

	return 0;
}

int set_site_field (struct Site *site, char *key, char *val)
{
	if (strstr (key, "name")) {
		site->name = val;
	} else if (strstr (key, "email")) {
		site->email = val;
	} else if (strstr (key, "dir")) {
		site->dir = val;
	} else if (strstr (key, "index")) {
		site->index = val;
	} else if (strstr (key, "access_log")) {
		site->access_log = val;
	} else if (strstr (key, "error_log")) {
		site->error_log = val;
	}

	return 0;
}

struct Site *match_site(char *request)
{
	// TODO: Create request and response files
	// TODO: Move request parsing code to request file
	// TODO: Move response building to response file

	struct Site *site;
	return site;

	if (site->name == NULL) {
		printf ("No site match \n");
		exit (EXIT_FAILURE);
	}

	/* http_parser_settings settings;
	http_parser *parser = malloc (sizeof(http_parser));
	settings.on_header_field = header_field_cb;
	settings.on_header_value = header_value_cb;
	http_parser_init (parser, HTTP_REQUEST);
	parser->data = request;
	http_parser_execute(parser, &settings, request, strlen (request));

	return site; */
}

int header_field_cb(http_parser *_, const char *at, size_t len)
{
	return 0;
}

int header_value_cb(http_parser *_, const char *at, size_t len)
{
	return 0;
}
