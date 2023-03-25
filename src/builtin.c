#include "builtin.h"

void
cd(char *directory) {
	if (directory == NULL) {
		fprintf(stderr, "[-] cd: destination expected!\n");
		return;
	}
	if (chdir(directory) == -1)
		fprintf(stderr, "[-] cd error: %s\n", strerror(errno));
}

void help() {
	printf("TraSH shell 0.0.1 by Mr.UNIX (Ibrahim Kaikaa)\n"
	    "Built-in commands:\n" "cd [dir]\n" "help\n");
}
