#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "command.h"


int main (int argc, char *argv[])
{
	if (argc > 1) {
		return parse_command (argc, argv);
	} else {
		printf ("Invalid number of arguments. \n");
		exit (EXIT_FAILURE);
	}
}
