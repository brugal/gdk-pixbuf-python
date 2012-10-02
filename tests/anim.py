#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf
from Test import *

def show_frame (frame):
	win = GtkWindow ()
	win.set_title (`frame`)
	vbox = GtkVBox ()
	win.add (vbox)

	pixbuf = frame.get_pixbuf ()
	pixmap = pixbuf.xmake_pixmap ()
	vbox.pack_start (pixmap)

	text =        "x_offset == %d\n" % frame.get_x_offset ()
	text = text + "y_offset == %d\n" % frame.get_y_offset ()
	text = text + "delay time == %d\n" % frame.get_delay_time ()
	action = frame.get_action ()
	if   action == 0:
		action_string = "FRAME_RETAIN"
	elif action == 1:
		action_string = "FRAME_DISPOSE"
	elif action == 2:
		action_string = "FRAME_REVERT"
	else:
		raise "BadEnumHaHa" 
		
	text = text + "action == %s" % action_string
	label = GtkLabel (text)
	vbox.pack_start (label, FALSE, FALSE)
	win.show_all ()
	
anim = GdkPixbuf.GdkPixbufAnimationFromFile ("anim.gif")
#anim = GdkPixbuf.GdkPixbufAnimationFromFile ("pic.jpg")
frames = anim.get_frames()
print "width == %d" % anim.get_width ()
print "height == %d" % anim.get_height ()
print "number of frames = %d" % anim.get_num_frames ()
print "frames == ", frames

for frame in frames:
	show_frame (frame)	

app()
mainloop ()

