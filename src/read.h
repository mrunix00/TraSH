#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef linux
#include <linux/limits.h>
#else
#include <limits.h>
#endif

char	**read_command();
void	  free_command(char **cmd);
