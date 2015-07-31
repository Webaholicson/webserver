#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "command.h"

int parse_command (int argc, char *argv[])
{
	if (strstr (argv[1], "start")) {
		return start_command (argc, argv);
	} else {
		printf ("Invalid command argument: %s \n", argv[1]);
		exit (EXIT_FAILURE);
	}
}

int start_command (int argc, char *argv[])
{
	const char *hostname 	= "127.0.0.1";
	uint16_t port 			= 4000;

	if (argc >= 4) {
		if (strstr (argv[2], "-p")) {
			port = (uint16_t) atoi(argv[3]);
		} else if (strstr (argv[2], "-a")) {
			hostname = argv[3];
		} else {
			printf ("Invalid argument %s \n", argv[2]);
			exit (EXIT_FAILURE);
		}
	}

	if (argc >= 6) {
		if (strstr (argv[4], "-p")) {
			port = (uint16_t) atoi (argv[5]);
		} else if (strstr (argv[4], "-a")) {
			hostname = argv[5];
		} else {
			printf ("Invalid argument %s \n", argv[4]);
			exit (EXIT_FAILURE);
		}
	}

	if (start (hostname, port) < 0) {
		exit (EXIT_FAILURE);
	}

	exit (EXIT_SUCCESS);
}
