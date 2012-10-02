CC = gcc
#PYGTK_H = /site/home/acano/gtk/bindings/pygtk-0.6.3
PYGTK_H = /usr/include/pygtk
#CFLAGS = -Wall -g `gtk-config --cflags` `gdk-pixbuf-config --cflags` -I/usr/include/python1.5 -I$(PYGTK_H)
CFLAGS = -DDEBUG__PYGDKPIXBUF -Wall -g -I. `gtk-config --cflags` `gdk-pixbuf-config --cflags` -I/usr/include/python2.1 -I$(PYGTK_H) -I/usr/include
LIBS = `gtk-config --libs` `gdk-pixbuf-config --libs` -L/usr/lib/gdk-pixbuf/loaders -lpixbufloader-bmp -lpixbufloader-gif -lpixbufloader-ico -lpixbufloader-jpeg -lpixbufloader-png -lpixbufloader-pnm -lpixbufloader-ras -lpixbufloader-tiff -lpixbufloader-xbm -lpixbufloader-xpm

#LIBS = `gtk-config --libs` `gdk-pixbuf-config --libs`

all:	_GdkPixbuf.so _GdkPixbufLoader.so

_GdkPixbuf.so:	_GdkPixbuf.c pygdkpixbuf.h PixelsObject.c
	$(CC) $(CFLAGS) $(LIBS) -shared _GdkPixbuf.c -o _GdkPixbuf.so

_GdkPixbufLoader.so: _GdkPixbufLoader.c pygdkpixbuf.h
	$(CC) $(CFLAGS) $(LIBS) -shared _GdkPixbufLoader.c -o _GdkPixbufLoader.so
