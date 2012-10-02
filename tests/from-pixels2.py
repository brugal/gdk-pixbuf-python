#!/usr/bin/python
import gtklib
from GdkPixbuf import *
from Test import *
import sys

set_debugging (1)

if len(sys.argv) != 2:
	print "usage: %s <image file>" % sys.argv[0]
	sys.exit (1)

pixbuf = GdkPixbufFromFile (sys.argv[1])
show_pixbuf (pixbuf, "from file")

#f = open ("py.pixels", "w")
#f.write (pixbuf.get_pixels()[:])
#f.close ()

pixbuf2 = GdkPixbufFromData (pixbuf.get_pixels()[:], pixbuf.get_colorspace(),
			pixbuf.get_has_alpha(), pixbuf.get_bits_per_sample(),
			pixbuf.get_width(), pixbuf.get_height(),
			pixbuf.get_rowstride())

show_pixbuf (pixbuf2, "from pixels")

win = GtkWindow ()
win.set_usize (300, 300)
win.connect ("destroy", mainquit)
win.show_all ()
app()
mainloop ()


