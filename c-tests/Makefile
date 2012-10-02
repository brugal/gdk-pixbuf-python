CC = gcc
CFLAGS = -g -Wall `gtk-config --cflags` `gdk-pixbuf-config --cflags`
LDFLAGS = `gtk-config --libs` `gdk-pixbuf-config --libs`
OBJS = test-gdk-pixbuf testanimation testpixbuf-drawable testpixbuf-scale testpixbuf

all: $(OBJS)

clean:
	rm -f $(OBJS)
