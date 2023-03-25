#include "exec.h"
#include "builtin.h"

void
command_exec(char **cmd) {
	pid_t pid;

	pid = fork();
	if (pid == 0) {
		if (execvp(cmd[0], cmd) == -1) {
			fprintf(stderr, "[-] Error: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	} else if (pid < 0) {
		fprintf(stderr, "[-] fork() failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		int status;
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

void
runcmd(char **cmd) {
	if (strcmp(cmd[0], "cd") == 0) cd(cmd[1]);
	else if(strcmp(cmd[0], "help") == 0) help();
	else command_exec(cmd);
}
