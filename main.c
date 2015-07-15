#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "server.h"
#include "command.h"


int main (int argc, char *argv[])
{
	if (argc > 1) {
		return parse_command (argc, argv);
	} else {
		printf ("Invalid number of arguments. \n\n");
		display_help();
		exit (EXIT_FAILURE);
	}
}

void display_help()
{
	printf ("Usage: webserver <command> [<args>]\n\n"
		"List of commands:\n\n"
		"start\t\tRuns the server\n"
		"version\t\tDisplays the version\n"
		"\n");
}
