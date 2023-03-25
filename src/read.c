#include "read.h"

char**
read_command() {
	char **command = malloc(2 * sizeof(char*)) , buff[ARG_MAX];
	uint64_t number_of_arguments = 0;
	int c, i = 0;

	while ((c = getchar()) != EOF) {
		if (ferror(stdin)) {
			fprintf(stderr, "[-] Failed reading stdin: %s\n", strerror(errno));
			return NULL;
		} else if (c == '\\') {
			c = getchar();
			if (c == '\n') continue;
			buff[i++] = c;
		} else if (c != ' ' && c != '\t' && c != '\n') {
			buff[i++] = c;
		} else {
			buff[i] = '\0';
			number_of_arguments++;
			command = realloc(command, (number_of_arguments + 1) * sizeof(char*));
			command[number_of_arguments - 1] = strdup(buff);
			buff[0] = '\0';
			i = 0;
			if (c == '\n') break;
		}
	}
	if (number_of_arguments == 0) {
		command[number_of_arguments++] = strdup("exit");
	}
	command[number_of_arguments] = NULL;
	return command;
}

void
free_command(char **cmd) {
	for (int i = 0; cmd[i] != NULL; i++)
		free(cmd[i]);
	free(cmd);
}
