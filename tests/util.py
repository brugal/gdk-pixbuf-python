#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf
from Test import *

pixbuf = GdkPixbuf.GdkPixbufFromFile ("pic.jpg")
show_pixbuf (pixbuf, "pic.jpg")

pixbuf_with_alpha = pixbuf.add_alpha (TRUE, 23333, 22222, 23333)
show_pixbuf (pixbuf_with_alpha, "with alpha")

pixbuf_to_copy_into = GdkPixbuf.GdkPixbufFromFile ("pic.gif")
pixbuf.copy_area (20, 20, 100, 100, pixbuf_to_copy_into, 0, 0)
show_pixbuf (pixbuf_to_copy_into, "copied into")

app()
mainloop ()

