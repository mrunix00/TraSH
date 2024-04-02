#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int	  readchar(void);
char	 *readline(void);
char 	**parseline(char *line);

void	  free_command(char **);
