#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "command.h"

int parse_command (int argc, char *argv[])
{
	int run = 0;
	int c;
	char *filename = malloc (sizeof (DEFAULT_CONFIG_FILE));
	strcpy (filename, DEFAULT_CONFIG_FILE);

	while ((c = getopt (argc, argv, "hvtc:s:")) != 1) {
		if (c == -1) {
			break;
		}

		switch (c) {
			case 'h':
				display_help();
				break;
			case 'v':
				printf("Webserver v0.1.0 By Antonio Mendes \n");
				break;
			case 't':
				break;
			case 'c':
				if (optarg == NULL) {
					exit (EXIT_FAILURE);
				}

				filename = realloc (filename, sizeof (optarg));
				strcpy (filename, optarg);
				run = 1;
				break;
			case 's':
				printf ("%s\n", optarg);
				if (optarg == NULL) {
					exit (EXIT_FAILURE);
				}

				if (strstr (optarg, "stop")) {
					handle_stop_signal();
				}

				if (strstr (optarg, "reload")) {
					handle_reload_signal();
				}

				break;
			default:
				signal (SIGTERM, (void *) stop);
				start_command (filename);
				break;
		}
	}

	return 0;
}

void display_help()
{
	printf ("Usage: webserver [-hvt] [-s signal] [-c filename]\n\n"
		"Options:\n"
		"-h\t\t\t: this help\n"
		"-v\t\t\t: show version and exit\n"
		"-t\t\t\t: test configuration and exit\n"
		"-s [signal]\t\t: send signal to a master process: stop, reload\n"
		"-c [filename]\t\t: set configuration file\n"
		"\n");
}

/**
 *	Start the webserver
 */
int start_command (const char *filename)
{
	if (start (filename) < 0) {
		exit (EXIT_FAILURE);
	}

	exit (EXIT_SUCCESS);
}

/**
 *	Handle stop signals sent with the -s option
 */
int stop_command ()
{
	if (is_running ()) {
		stop (SIGTERM);
	}

	return 0;
}

/**
 *	Handle stop signals sent with the -s option
 */
int handle_stop_signal ()
{
	int pid = is_running();

	if (pid)
		kill (pid, SIGTERM);

	return 0;
}

int handle_reload_signal()
{
	return 0;
}

int is_running()
{
	FILE *fp;
	char line[10];
	fp = fopen (PID_FILE, "r");

	if (fp == NULL) {
		perror ("fopen");
		exit (EXIT_FAILURE);
	}

	return (fgets (line, 10, fp) != NULL) ? atoi(line) : 0;
}
