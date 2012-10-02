#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf
import GdkPixbufLoader
from Test import *

loader = None
fp = None
pixbuf = None

def area_prepared (loader):
	global pixbuf
	print "area prepared", loader
	pixbuf = loader.get_pixbuf ()
	show_pixbuf (pixbuf, "from loader")

def area_updated (loader, x, y, width, height):
	print "area updated:"
	print "\tx == %d" % x
	print "\ty == %d" % y
	print "\twidth == %d" % width
	print "\theight == %d" % height
	#global pixbuf
	pixbuf = loader.get_pixbuf ()
	show_pixbuf (pixbuf)

def frame_done (loader, frame):
	print "frame done", loader, frame

def animation_done (loader):
	print "animation done", loader

def closed (loader):
	#pixbuf = loader.get_pixbuf ()
	#show_pixbuf (pixbuf, "loader closed")
	print "closed"

def test_loader ():
	global loader, fp
	if loader == None:
		loader = GdkPixbufLoader.GdkPixbufLoader ()
		loader.connect ("area_prepared", area_prepared)
		loader.connect ("area_updated", area_updated)
		loader.connect ("frame_done", frame_done)
		loader.connect ("animation_done", animation_done)
		loader.connect ("closed", closed)
	if fp == None:
		fp = open ("pic.png", "r")
	data = fp.read (8192)
	if len(data) == 0:
		fp.close ()
		loader.close ()
		return FALSE
	loader.write (data)
	return TRUE

timeout_add (1000, test_loader)
app ()
mainloop ()

