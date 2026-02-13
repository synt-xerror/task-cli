CFLAGS  := $(shell pkg-config --cflags glib-2.0)
LDFLAGS := $(shell pkg-config --libs glib-2.0)
HOME	:= $($HOME)

task:
	gcc task.c $(CFLAGS) -o task $(LDFLAGS)

clean:
	rm task

install:
	mv task /usr/local/bin
