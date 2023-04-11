#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#ifdef linux
#include <linux/limits.h>
#else
#include <limits.h>
#endif

int	  readchar();
char	 *readline();
char 	**parseline(char *line);

void	  free_command(char **);
