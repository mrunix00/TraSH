#include "read.h"
#include "exec.h"

int
main() {
	char *line;
	char **command;
	while (1) {
		printf("[trash]$ ");
		line = readline();
		command = parseline(line);
		if (strcmp(command[0], "exit") == 0) {
			free(line);
			free_command(command);
			return EXIT_SUCCESS;
		}
		runcmd(command);
		free(line);
		free_command(command);
	}
}
