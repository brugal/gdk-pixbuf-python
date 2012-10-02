#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf
import GdkPixbufLoader
import GDK
from Test import *
import _GdkPixbufLoader

import _GdkPixbuf
_GdkPixbuf.set_debugging (0)
_GdkPixbufLoader.set_debugging (1)

import os
del os.environ["PYGTK_FATAL_EXCEPTIONS"] 

def feed_loader ():
	global fp, loader
	data = fp.read (64 * 1)
	if len(data) == 0:
		fp.close ()
		loader.close ()
		return FALSE
	loader.write (data)	
	return TRUE

#def area_prepared (loader, x, y):
def area_prepared (loader, x=None):
	print "area_prepared(): ", x

def area_updated (loader, x, y, width, height, *args):
	print "area_updated(): ", x, y, width, height
	#print z

def closed (loader):
	print "loader closed(): "
	loader.destroy ()

i = 1
def frame_done (loader, frame):
	print "frame_done(): ", i, loader, frame 
	global i
	#f = GdkPixbuf._GdkPixbufFrameKlass (frame)
	#import _GdkPixbufLoader
	#fobj = _GdkPixbufLoader.frame_to_pyobject (frame)
	#print "got fobj"
	#print fobj
	#f = GdkPixbuf._GdkPixbufFrameKlass (fobj)
	#print f, loader
	print frame.get_delay_time()
	pixbuf = frame.get_pixbuf ()
	show_pixbuf (pixbuf, "frame %d" % i)
	i = i + 1
	# testing exceptions, 'z' doesn't exist
	#print z

def animation_done (loader):
	print "animation_done(): "

def destroyed (loader):
	print "destroyed(): "

#####	main 	########

import sys
if len(sys.argv) > 1:
	filename = sys.argv[1]
else:
	filename = "anim.gif"

fp = open (filename, "r")

win = GtkWindow ()
win.connect ("destroy", destroyed)
win.connect ("destroy", mainquit)
win.set_usize (100, 100)

#pixbuf = GdkPixbuf.GdkPixbufFromFile ("pic.png")

loader = GdkPixbufLoader.GdkPixbufLoader ()
loader.connect ("area_prepared", area_prepared, 777)
loader.connect ("area_updated", area_updated, 666, win)
loader.connect ("frame_done", frame_done)
loader.connect ("animation_done", animation_done)
loader.connect ("closed", closed)
loader.connect ("destroy", destroyed)

timeout_add (500, feed_loader)
win.show_all ()
mainloop ()

