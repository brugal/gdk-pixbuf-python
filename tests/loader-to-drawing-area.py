#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf
import GdkPixbufLoader
import GDK

def feed_loader ():
	global fp, loader
	data = fp.read (64 * 4)
	if len(data) == 0:
		fp.close ()
		loader.close ()
		return FALSE
	loader.write (data)	
	return TRUE

def area_prepared (loader, drawing_area, win):
	global pixbuf, pix_width, pix_height	
	pixbuf = loader.get_pixbuf ()
	pix_width = pixbuf.get_width ()
	pix_height = pixbuf.get_height ()
	print "area_prepared(): width == %d\theight == %d" % \
	      (pix_width, pix_height)
	drawing_area.size (pix_width, pix_height)
	win.show_all ()

def area_updated (loader, x, y, width, height, drawing_area):
	global pixbuf
	class event_struct:
		def __init__ (self, x, y, width, height):
			self.area = []
			self.area.append (x)
			self.area.append (y) 
			self.area.append (width) 	
			self.area.append (height)

	event = event_struct (x, y, width, height)
	print event.area
	print "area_updated(): ", x, y, width, height
	drawing_area_expose_cb (drawing_area, event)

def closed (loader):
	print "image done loading"

def drawing_area_expose_cb (drawing_area, event):
	global pixbuf, pix_width, pix_height
	print "drawing_area_exposed_cb: ", event.area
	(x, y, event_width, event_height) = event.area
	if x > pix_width  or  y > pix_height:
		return

	width = min (event_width, pix_width - x)
	height = min (event_height, pix_height - y)

	pixbuf.render_to_drawable (
	    drawing_area.get_window(),
	    drawing_area.get_style().black_gc,
	    x, y, x, y, 
	    width, height,
	    GDK.RGB_DITHER_NORMAL, 0, 0 
	)

#####	main 	########
import _GdkPixbuf
_GdkPixbuf.set_debugging (FALSE)
push_rgb_visual ()

import sys
if len(sys.argv) > 1:
	filename = sys.argv[1]
else:
	filename = "pic.png"

fp = open (filename, "r")

win = GtkWindow ()
win.connect ("destroy", mainquit)
win.set_usize (400, 400)

scrolled_window = GtkScrolledWindow ()
win.add (scrolled_window)

drawing_area = GtkDrawingArea ()
drawing_area.connect ("expose_event", drawing_area_expose_cb)
scrolled_window.add_with_viewport (drawing_area)

pixbuf = None
pix_width = None
pix_height = None
loader = GdkPixbufLoader.GdkPixbufLoader ()
loader.connect ("area_prepared", area_prepared, drawing_area, win)
loader.connect ("area_updated", area_updated, drawing_area)
loader.connect ("closed", closed)

timeout_add (500, feed_loader)
mainloop ()

