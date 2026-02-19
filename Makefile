CFLAGS  := $(shell pkg-config --cflags glib-2.0)
LDFLAGS := $(shell pkg-config --libs glib-2.0)
HOME	:= $(HOME)

task:
	gcc -c toybox.c -o toybox.o
	ar rcs libtoybox.a toybox.o
	gcc task.c -L. -ltoybox $(CFLAGS) -o task $(LDFLAGS)

clean:
	rm -f task libtoybox.a toybox.o

install:
	mv task /usr/local/bin
