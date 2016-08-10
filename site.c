#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

char *site_table_keys[SITE_NUM_FIELDS] = { "name", "dir", "error_log", "access_log", "email", "index", "type" };

int setup_site (FILE *fp)
{
	char line[100];
	char *content = malloc (CONFIG_FILE_SIZE);
	strcpy (content, "");

	while (fgets (line, 100, fp) != NULL) {
		strcat (content, line);
	}

	fclose (fp);

	if (strlen (content) < 2) {
		return 0;
	}

	free (content);

	int i;
	struct Site *site = malloc (CONFIG_FILE_SIZE);

	for (i = 0; i < SITE_NUM_FIELDS; i++) {
		const char *val = "name";
		set_site_field (site, site_table_keys[i], val);
	}

	instance->config->sites[instance->config->num_of_sites] = site;
	instance->config->num_of_sites++;

	return 0;
}

int set_site_field (struct Site *site, const char *key, const char *val)
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

	struct Site *site = malloc (sizeof (struct Site));
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
