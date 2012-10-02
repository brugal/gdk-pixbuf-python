#!/usr/bin/python
import gtklib

from gtk import *
import GdkPixbuf
import sys

import _GdkPixbuf
_GdkPixbuf.set_debugging (1)

if len(sys.argv) != 2:
	print "usage: %s <animation>" % sys.argv[0]
	sys.exit (1)

def close (win, timeout):
	timeout_remove (timeout)
	mainquit ()

count = 0
def play ():
	global drawing_area, pixbufs, frames, count
	pixbuf = pixbufs[count]
	if pixbuf.get_has_alpha():
		dither = GDK.RGB_DITHER_MAX
	else:
		dither = GDK.RGB_DITHER_NORMAL

	if pixbuf.get_has_alpha():
		#FIXME i don't know about this stuff :(
		pixbuf.render_to_drawable_alpha (drawing_area.get_window(),
				0, 0,
				frames[count].get_x_offset(),
				frames[count].get_y_offset(),
				pixbuf.get_width(), pixbuf.get_height(),
				GDK.PIXBUF_ALPHA_FULL, 0,
				dither, 0, 0)
	else:
		pixbuf.render_to_drawable (drawing_area.get_window(),
				drawing_area.get_style().black_gc,
				0, 0,
				frames[count].get_x_offset(),
				frames[count].get_y_offset(),
				pixbuf.get_width(), pixbuf.get_height(),
				dither, 0, 0)
	count = count + 1
	if count == len(frames):
		count = 0
	return TRUE	
		

push_rgb_visual ()	

animation = GdkPixbuf.GdkPixbufAnimation (sys.argv[1])

win = GtkWindow ()

drawing_area = GtkDrawingArea ()
drawing_area.size (animation.get_width(), animation.get_height())
win.add (drawing_area)

frames = animation.get_frames ()
print frames
pixbufs = []
for frame in frames:
	p = frame.get_pixbuf ()
	pixbufs.append (p)

timeout = timeout_add (frames[0].get_delay_time() * 10, play)
win.connect ("destroy", close, timeout)
win.show_all ()
mainloop ()

