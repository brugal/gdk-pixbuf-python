#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf
from Test import *

pixbuf = GdkPixbuf.GdkPixbufFromFile ("pic.xpm")
gdkpixmap, mask = pixbuf.render_pixmap_and_mask ()

#pixmap = GtkPixmap (gdkpixmap, mask)
#pixmap = GtkPixmap ()
# pixmap.set() from pygtk is broken. It will not accept None as a mask
#pixmap.set (gdkpixmap, mask)
#GdkPixbuf.xgtk_pixmap_set (pixmap, gdkpixmap, mask)

win = GtkWindow ()
win.realize ()
pixmap = GtkPixmap (win.get_window(), mask)
win.add (pixmap)
win.show_all ()

pixmap.set (gdkpixmap, mask)

app()
mainloop ()

