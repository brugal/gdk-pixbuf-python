#!/usr/bin/python
import gtklib
from GdkPixbuf import *
from Test import *

set_debugging (1)

pixbuf = GdkPixbufFromFile ("pic.ppm")
show_pixbuf (pixbuf, "original pixbuf")

pixbuf2 = GdkPixbufFromData (pixbuf.get_pixels()[:], pixbuf.get_colorspace(),
			pixbuf.get_has_alpha(), pixbuf.get_bits_per_sample(),
			pixbuf.get_width(), pixbuf.get_height(),
			pixbuf.get_rowstride())

show_pixbuf (pixbuf2, "pixbuf from 'original pixbuf'.get_pixels()")

app()
mainloop ()


