#include "read.h"
#include "exec.h"

int
main() {
	char **command;
	while (1) {
		printf("[trash]$ ");
		command = read_command();
		if (strcmp(command[0], "exit") == 0) {
			free_command(command);
			return EXIT_SUCCESS;
		}
		runcmd(command);
		free_command(command);
	}
}
