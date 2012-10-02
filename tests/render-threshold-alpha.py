#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf
from Test import *

pixbuf = GdkPixbuf.GdkPixbufFromFile ("pic.jpg")
show_pixbuf (pixbuf, "pic.jpg")

pixbuf2 = GdkPixbuf.GdkPixbufFromFile ("pic.xpm")
show_pixbuf (pixbuf2, "pic.xpm")
(gdkpixmap, gdkmask) = pixbuf2.render_pixmap_and_mask ()

pixbuf.render_threshold_alpha (gdkmask, 0, 0, 0, 0, 100, 100, 0)
show_pixbuf (pixbuf, "render_threshold_alpha()")

app()
mainloop ()

