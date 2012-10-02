#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf
from Test import *

push_rgb_visual ()

def render_to_drawable (button, pixbuf, drawable):
	pixbuf.render_to_drawable (drawable.get_window(), 
			drawable.get_style().black_gc,
			45, 20, 
			10, 30, 
			100, 100, 
			dither=0, x_dither=0, y_dither=0)

def render_to_drawable_alpha (button, pixbuf, drawable):
	pixbuf.render_to_drawable_alpha (drawable.get_window(), 
			drawable.get_style().black_gc,
			45, 20, 
			10, 30, 
			100, 100,
			alpha_mode=GdkPixbuf.ALPHA_FULL,
			alpha_threshold=20000, 
			dither=0, x_dither=0, y_dither=0)

#pixbuf = GdkPixbuf.GdkPixbufFromFile ("pic.gif")
pixbuf = GdkPixbuf.GdkPixbufFromFile ("xxx5.ppm")

win = GtkWindow ()
win.set_usize (400, 400)
win.connect ("destroy", mainquit)

vbox = GtkVBox ()
win.add (vbox)

drawing_area = GtkDrawingArea ()
vbox.pack_start (drawing_area)

button = GtkButton ("render to drawable")
button.connect ("clicked", render_to_drawable, pixbuf, drawing_area)
vbox.pack_start (button, FALSE)

button = GtkButton ("render to drawable alpha")
button.connect ("clicked", render_to_drawable, pixbuf, drawing_area)
vbox.pack_start (button, FALSE)

win.show_all ()
mainloop ()

