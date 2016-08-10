#ifndef COMMAND_H_
#define COMMAND_H_

#include "server.h"

extern void display_help (void);

extern int parse_command (int argc, char *argv[]);

extern int start_command (const char *filename);

extern int handle_stop_signal (void);

extern int handle_reload_signal (void);

extern int is_running (void);

#endif
