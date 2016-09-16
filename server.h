#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <regex.h>
#include <signal.h>

#include "request.h"
#include "config.h"

struct WebServer *instance;

struct WebServer {
	sig_atomic_t is_running;
	sig_atomic_t can_shutdown;
	int num_requests;
	int socket;
	struct sockaddr_in socket_name;
	const char *hostname;
	uint16_t port;
	struct Config *config;
	http_parser *http_parser;
};

extern int start (const char *filename);

extern void stop (int signum);

extern int handle_requests (void);

extern int handle_request (int fd);

extern int send_response (int fd, struct Site *site);

extern int log_request(char *request);

extern int update_pid_file(int status);

#endif
