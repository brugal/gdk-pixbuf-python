#!/usr/bin/python
import gtklib

from gtk import *
import GdkPixbuf
import GdkPixbufLoader
import sys
import urlparse
import socket
import select

def error_exit (msg):
	print "ERROR: %s" % msg
	print "\tusage: %s <image url>" % sys.argv[0]
	print "\texample: %s http://www.gimp.org/icons/gimp_in_action1.jpeg" % \
		sys.argv[0]
	sys.exit (1)

if len(sys.argv) != 2:
	error_exit ("not enough args")

def close (win):
	loader = win.get_data ("loader")
	sock = loader.get_data ("socket")
	loader.write = lambda x: x
	try:
		sock.shutdown (2)
	except socket.error:
		pass
	loader.close ()
	mainquit ()

def area_prepared (loader, drawing_area):
	print "area_prepared"
	pixbuf = loader.get_pixbuf ()
	drawing_area.set_data ("pixbuf", pixbuf)
	drawing_area.size (pixbuf.get_width(), pixbuf.get_height())
	drawing_area.connect ("expose_event", drawing_area_expose_cb)

def area_updated (loader, x, y, width, height, drawing_area):
	class event_struct:
                def __init__ (self, x, y, width, height):
                        self.area = []
                        self.area.append (x)
                        self.area.append (y) 
                        self.area.append (width)        
                        self.area.append (height)

        event = event_struct (x, y, width, height)
        drawing_area_expose_cb (drawing_area, event)

def drawing_area_expose_cb (drawing_area, event):
	pixbuf = drawing_area.get_data ("pixbuf")
	(x, y, event_width, event_height) = event.area
	if pixbuf == None          or  \
           x > pixbuf.get_width()  or  \
	   y > pixbuf.get_height():
		return

	width = min (event_width, pixbuf.get_width() - x)
	height = min (event_height, pixbuf.get_height() - y)

	#FIXME alpha
	pixbuf.render_to_drawable (
		drawing_area.get_window(),
		drawing_area.get_style().black_gc,
		x, y, x, y,
		width, height,
		GDK.RGB_DITHER_NORMAL, 0, 0)

def loader_closed (loader):
	print "image done loading"

def get_image (button, loader, site, path):
	button.set_sensitive (FALSE)

	sock = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
	loader.set_data ("socket", sock)
	print "connecting to '%s'" % site
	sock.connect (site, 80)

	print "sending request for '%s'" % path
	sock.send ("GET %s\r\n\r\n" % path)
	sock.setblocking (0)

	print "getting data..."
	while 1:
		ret = select.select ([sock], [], [], 0.15)
		if ret != ([], [], []):
			data = sock.recv (8192)
			if data == '':
				print "got all the data"
				break
			loader.write (data)
		else:
			while events_pending():
				mainiteration ()
	return FALSE


## main
if len(sys.argv) != 2:
	error_exit ("not enough args")

parsed_url = urlparse.urlparse (sys.argv[1])
site = parsed_url[1]
path = parsed_url[2]
if site == ''  or  path == '':
	error_exit ("invalid url")

push_rgb_visual ()

win = GtkWindow ()
win.connect ("destroy", close)

vbox = GtkVBox ()
win.add (vbox)

scrolled_win = GtkScrolledWindow ()
scrolled_win.set_usize (500, 500)
vbox.pack_start (scrolled_win)

drawing_area = GtkDrawingArea ()
drawing_area.set_data ("pixbuf", None)
scrolled_win.add_with_viewport (drawing_area)

loader = GdkPixbufLoader.GdkPixbufLoader ()
loader.connect ("area_prepared", area_prepared, drawing_area)
loader.connect ("area_updated", area_updated, drawing_area)
loader.connect ("closed", loader_closed)
win.set_data ("loader", loader)

button = GtkButton ("get %s" % path)
button.connect ("clicked", get_image, loader, site, path)
vbox.pack_start (button)

win.show_all ()
mainloop ()

