#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "server.h"

struct WebServer *instance;

int start (const char *hostname, uint16_t port)
{
	int web_server_socket = socket (PF_INET, SOCK_STREAM, 0);

	if (web_server_socket < 0) {
		perror ("socket");
		exit (EXIT_FAILURE);
	}

	struct sockaddr_in socket_name;
	struct hostent *hostinfo;

	socket_name.sin_family = AF_INET;
	socket_name.sin_port = htons (port);
	hostinfo = gethostbyname (hostname);

	if (hostinfo == NULL) {
		printf ("Unknown host %s.\n", hostname);
		exit (EXIT_FAILURE);
	}

	socket_name.sin_addr = *(struct in_addr *) hostinfo->h_addr;

	if (bind (web_server_socket, (struct sockaddr *) &socket_name, sizeof (socket_name)) < 0) {
		perror ("bind");
		exit (EXIT_FAILURE);
	}

	if (listen (web_server_socket, MAX_CONNECTIONS) < 0) {
	  perror ("listen");
	  exit (EXIT_FAILURE);
	}

	printf("Server running on %s:%d \n", hostname, port);
	printf("To stop the server press Ctrl+C \n");

	instance = malloc(sizeof(struct WebServer));

	instance->socket_name	= socket_name;
	instance->hostname		= hostname;
	instance->port			= port;
	instance->socket 		= web_server_socket;
	instance->num_requests 	= 0;

	handle_requests();

	return stop();
}

int stop (void)
{
	close(instance->socket);
	free(instance);
	return 0;
}

int handle_requests (void)
{
	int i;
	socklen_t size;
	fd_set pending_fd_set, active_fd_set;
	FD_ZERO(&pending_fd_set);
	FD_SET(instance->socket, &pending_fd_set);

	active_fd_set = pending_fd_set;

	if (select (FD_SETSIZE, &active_fd_set, NULL, NULL, NULL) < 0) {
		perror ("select");
		exit (EXIT_FAILURE);
	}

	while (1) {
		for (i = 0; i < FD_SETSIZE; ++i) {
			if (FD_ISSET(i, &active_fd_set)) {
				if (i == instance->socket) {
					int new;
					size = sizeof(instance->socket_name);
					new = accept(instance->socket, (struct sockaddr *) &instance->socket_name, &size);
					if (new < 0) {
						perror ("accept");
						exit (EXIT_FAILURE);
					}

					FD_SET (new, &active_fd_set);
				} else {
					handle_request(i);
					close(i);
					FD_CLR(i, &active_fd_set);
				}
			}
		}
	}

	return 0;
}

int handle_request(int fd)
{
	char buffer[MAX_REQUEST_SIZE];
	int nbytes;

	nbytes = read (fd, buffer, MAX_REQUEST_SIZE);
	if (nbytes < 0) {
		perror ("read");
		exit (EXIT_FAILURE);
	} else if (nbytes == 0) {
		return -1;
	} else {
		log_request (buffer);
		return send_response(fd);
	}
}

int send_response(int fd)
{
	const char *headers = "HTTP/1.1 200 OK\n" \
			"Content-Type: text/html;charset=utf-8\n" \
			"Content-Length: length\n\n";

	FILE *fp;

	fp = fopen (INDEX_FILE, "r");

	if (fp == NULL) {
		printf ("Failed to open file: %s \n", INDEX_FILE);
		exit (EXIT_FAILURE);
	}

	char body[1024];

	char response[3072];
	strcpy (response, headers);

	while (fscanf (fp, " %[^\n]s",body) != EOF) {
		strcat (response, body);
	}

	fclose(fp);

	int nbytes;
	nbytes = write (fd, response, strlen(response) + 1);

	if (nbytes < 0) {
		perror ("write");
		exit (EXIT_FAILURE);
	}

	return 0;
}

int log_error(char *error)
{
	FILE *error_log;
	error_log = fopen (ERROR_LOG, "a");

	if (error_log == NULL) {
		perror ("fopen");
		exit (EXIT_FAILURE);
	}

	fprintf (error_log, "[%s %s]\n%s", __DATE__, __TIME__, error);
	fclose (error_log);

	return 0;
}

int log_request(char *request)
{
	FILE *access_log;
	access_log = fopen (ACCESS_LOG, "a");

	if (access_log == NULL) {
		perror ("fopen");
		exit (EXIT_FAILURE);
	}

	fprintf (access_log, "[%s %s]\n%s", __DATE__, __TIME__, request);
	fclose (access_log);

	return 0;
}
