#!/usr/bin/python
import gtklib

from gtk import *
import GdkPixbuf
import GDK
import sys
import string

if len(sys.argv) != 4:
	print "usage: %s <image file> <new width> <new height>" % sys.argv[0]
	sys.exit (1)

filename = sys.argv[1]
width = string.atoi (sys.argv[2])
height = string.atoi (sys.argv[3])

pixbuf = GdkPixbuf.GdkPixbufFromFile (filename)
pixbuf = pixbuf.scale_simple (width, height, GDK.INTERP_NEAREST)

win = GtkWindow ()
win.connect ("destroy", mainquit)

pixmap = pixbuf.xmake_pixmap ()
win.add (pixmap)

win.show_all ()
mainloop ()

