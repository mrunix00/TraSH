PROG=		trash
SRCS=		src/*.c

CFLAGS+=	-g -fPIE -fPIC -fstack-protector-strong -Wall -Werror -O0

all:		$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS)
clean:
	rm -rf $(PROG) *core *vgcore
