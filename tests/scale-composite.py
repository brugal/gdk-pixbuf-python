#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf
from Test import *

pixbuf = GdkPixbuf.GdkPixbufFromFile ("pic.png")
show_pixbuf (pixbuf, "pic.png")

#pixbuf_scaled = pixbuf.scale (20, 30, 70, 80, 
#			0, 0, 0, 0, GdkPixbuf.INTERP_NEAREST)
pixbuf_scaled = GdkPixbuf.GdkPixbufBlank (0, TRUE, 8, 150, 150)

pixbuf.scale (pixbuf_scaled, 20, 30, 70, 80, 
	0, 0, 0.5, 0.5, GdkPixbuf.INTERP_NEAREST)
show_pixbuf (pixbuf_scaled, "scaled pic.png")

pixbuf_composited = GdkPixbuf.GdkPixbufBlank (0, TRUE, 8, 150, 150)
GdkPixbuf.pixbuf_composite (pixbuf, pixbuf_composited, 20, 20, 100, 80,
			0, 0, 1.0, 1.0, GdkPixbuf.INTERP_NEAREST, 200)
show_pixbuf (pixbuf_composited, "pixbuf_composited")

pixbuf_composited_color = GdkPixbuf.GdkPixbufBlank (0, TRUE, 8, 150, 150)
GdkPixbuf.pixbuf_composite_color (pixbuf, pixbuf_composited_color,
			30, 15,
			100, 90,
			10, 18,
			0.7, 0.7,
			GdkPixbuf.INTERP_HYPER,
			0,
			2, 5,
			16,
			20000,
			40000)
show_pixbuf (pixbuf_composited_color, "pixubf_composited_color")

app()
mainloop ()

