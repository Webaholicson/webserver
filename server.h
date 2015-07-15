#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

#define MAX_REQUEST_SIZE 	8192
#define MAX_CONNECTIONS 	100
#define ACCESS_LOG 			"access.log"
#define ERROR_LOG 			"error.log"
#define INDEX_FILE			"index.html"

struct WebServer {
	int num_requests;
	int socket;
	struct sockaddr_in socket_name;
	const char *hostname;
	uint16_t port;
};

extern int start (const char *hostname, uint16_t port);

extern int stop (void);

extern int handle_requests (void);

extern int handle_request (int fd);

extern int send_response (int fd);

extern int log_request(char *request);

#endif
