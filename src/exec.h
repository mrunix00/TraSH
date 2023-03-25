#include <sys/wait.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	 command_exec(char **cmd);
void	 runcmd(char **cmd);
