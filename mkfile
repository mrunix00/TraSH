</$objtype/mkfile

CC=pcc
TARG=trash

CFLAGS=-D_POSIX_SOURCE -D_LIMITS_EXTENSION

default:V: 
	$CC $CFLAGS src/*.c -o $TARG

clean:V:
	rm -rf *.[$OS] $TARG
