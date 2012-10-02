#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf
from Test import *

pixbuf = GdkPixbuf.GdkPixbufFromFile ("pic.ppm")
show_pixbuf (pixbuf, "pic.ppm")

pixbuf_scaled = pixbuf.scale_simple (100, 200, GdkPixbuf.INTERP_BILINEAR)
show_pixbuf (pixbuf_scaled, "pixbuf_scaled")

pixbuf_composited_color_simple = pixbuf.composite_color_simple (
					200, 200,
					GdkPixbuf.INTERP_NEAREST,
					0,
					40,
					10000,
					50000)
show_pixbuf (pixbuf_composited_color_simple, "pixbuf_composited_color_simple")

app()
mainloop ()

