#include "read.h"

#ifdef linux
#include <linux/limits.h>
#else
#include <limits.h>
#endif

int
readchar(void) {
	struct termios oldattr, newattr;
	int ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}

char*
readline(void) {
	char *input;
	int c, pos = 0, length = 0;
	size_t size = 1024;

	input = malloc(size);
	while (1) {
		c = readchar();
		if (ferror(stdin) || feof(stdin)) {
			perror("[-] Failed reading stdin");
			return NULL;
		}
		switch (c) {
			case 4:
				length = -1;
				goto end;
			case '\n':
				if (length > 0 && input[length - 1] == '\\') {
					length--;pos--;
					printf("\n> ");
				} else
					goto end;
				break;
			case '\033':
				readchar(); /* skip '[' character */
				c = readchar();
				if (c == 'C' && pos < length) { /* Right arrow key */
					printf("\033[C");
					pos++;
				}
				if (c == 'D' && pos > 0) { /* Left arrow key */
					printf("\033[D");
					pos--;
				}
				break;
			case '\b':
			case 127:
				if (pos > 0) {
					memmove(&input[pos - 1], &input[pos],
					    length - pos + 1);
					pos--; length--;
					putchar('\b');
					for (int i = pos; i < length; i++)
						putchar(input[i]);
					putchar(' ');
					for (int i = pos; i <= length; i++)
						putchar('\b');
				}
				break;
			default:
				if (!isprint(c))
					continue;
				if (length >= size) {
					size += 1024;
					input = realloc(input, size);
				}
				memmove(&input[pos + 1], &input[pos], length - pos + 1);
				input[pos] = c;
				length++;
				pos++;
				putchar(c);
				for (int i = pos; i < length; i++)
                			putchar(input[i]);
				for (int i = pos; i < length; i++)
                			putchar('\b');
		}
	}
end:
	if (length == -1) {
		free(input);
		input = strdup("exit");
		return input;
	}
	if (length >= size)
		input = realloc(input, size + 1);
	input[length] = '\0';
	
	putchar('\n');
	return input;
}

char**
parseline(char *line) {
	char **output = malloc(sizeof(char*)),
	      *c = line,
	      *buff = malloc(ARG_MAX);
	size_t number_of_arguments = 0;
	int i = 0;
	while (1) {
		if (*c == '\\') {
			c++;
			if (*c != '\0') buff[i++] = *c;
		}else if (*c != ' ' && *c != '\t' && *c != '\0') {
			buff[i++] = *c;
		} else {
			buff[i] = '\0';
			number_of_arguments++;
			output = realloc(output, (number_of_arguments + 1) * sizeof(char*));
			output[number_of_arguments - 1] = strdup(buff);
			if (*c == '\0') break;
			buff[0] = '\0';
			i = 0;
		}
		c++;
	}

	if (number_of_arguments == 0) {
		output[number_of_arguments++] = strdup("exit");
	}
	output[number_of_arguments] = NULL;
	free(buff);
	return output;
}

void
free_command(char **cmd) {
	for (int i = 0; cmd[i] != NULL; i++)
		free(cmd[i]);
	free(cmd);
}
