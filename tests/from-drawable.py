#!/usr/bin/python
import gtklib
import GdkPixbuf
import _GdkPixbuf
from Test import *

def get_drawable (button, win):
	pixbuf = GdkPixbuf.GdkPixbufFromDrawable (None, win.get_window(),
			win.get_colormap(), 0, 0, 0, 0,
			100, 100)
	show_pixbuf (pixbuf)

def draw_line (button, drawing_area):
	drawing_area.draw_line (drawing_area.get_style().black_gc,
				0, 0, 50, 50)

win = GtkWindow ()
win.connect ("destroy", mainquit)
win.set_usize (200, 200)

vbox = GtkVBox ()
win.add (vbox)

drawing_area = GtkDrawingArea ()
drawing_area.set_usize (100, 100)
vbox.pack_start (drawing_area)

button = GtkButton ("get from drawable")
button.connect ("clicked", get_drawable, drawing_area)
vbox.pack_start (button)

button = GtkButton ("draw line")
button.connect ("clicked", draw_line, drawing_area)
vbox.pack_start (button)

win.show_all ()
mainloop ()

