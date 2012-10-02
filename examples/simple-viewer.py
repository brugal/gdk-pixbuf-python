#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf, sys

if len(sys.argv) < 2:
	print "give me an image..."
	sys.exit (1)

win = GtkWindow ()
win.connect ("destroy", mainquit)
pixbuf = GdkPixbuf.GdkPixbufFromFile (sys.argv[1])
pixmap = pixbuf.xmake_pixmap ()
win.add (pixmap)
win.show_all ()
mainloop ()
