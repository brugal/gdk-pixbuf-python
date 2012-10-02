#!/usr/bin/python
import gtklib

from gtk import *
import gtk
import GDK
import GTK
import GdkPixbuf

from Test import *
import _GdkPixbuf
_GdkPixbuf.set_debugging (0)


def expose_cb (drawing_area, evt):
	(evt_x, evt_y, evt_width, evt_height) = evt.area
	pixbuf = drawing_area.get_data ("pixbuf")

	if pixbuf.get_has_alpha():
		drawing_area.draw_rgb_32_image ( \
				drawing_area.get_style().black_gc,
				evt_x, evt_y,
				evt_width, evt_height,
				GDK.RGB_DITHER_MAX,
				pixbuf.get_pixels()[ \
					evt_y * pixbuf.get_rowstride() + \
					evt_x * pixbuf.get_n_channels():],
				pixbuf.get_rowstride())
	else:
		drawing_area.draw_rgb_image ( \
                                drawing_area.get_style().black_gc,
                                evt_x, evt_y,
                                evt_width, evt_height,
                                GDK.RGB_DITHER_NORMAL,
                                pixbuf.get_pixels()[ \
                                        evt_y * pixbuf.get_rowstride() + \
                                        evt_x * pixbuf.get_n_channels():],
                                pixbuf.get_rowstride())

	return FALSE;


def configure_cb (drawing_area, evt):
	pixbuf = drawing_area.get_data ("pixbuf")

	print "X:%d Y:%d" % (evt.width, evt.height)
	if evt.width  != pixbuf.get_width() or \
	   evt.height != pixbuf.get_height():
		root = gtk._root_window ()
		new_pixbuf = GdkPixbuf.GdkPixbufFromDrawable ( \
						None, root, None,
						0, 0, 0, 0,
						evt.width, evt.height)
		drawing_area.set_data ("pixbuf", new_pixbuf)
		del pixbuf
	
	return FALSE

def main ():
	push_rgb_visual ()
	
	root = gtk._root_window ()
	pixbuf = GdkPixbuf.GdkPixbufFromDrawable (None, root, None,
					0, 0, 0, 0, 150, 160)
	win = GtkWindow ()
	win.connect ("delete_event", mainquit)
	win.connect ("destroy", mainquit)
	
	vbox = GtkVBox ()
	win.add (vbox)

	drawing_area = GtkDrawingArea ()
	drawing_area.size (pixbuf.get_width(), pixbuf.get_height())
	drawing_area.connect ("expose_event", expose_cb)
	drawing_area.connect ("configure_event", configure_cb)
	drawing_area.set_data ("pixbuf", pixbuf)
	vbox.pack_start (drawing_area)

	win.show_all ()
	mainloop ()


main ()
