#!/usr/bin/python
import gtklib

# GdkPixbuf version of the view.py example that comes with pygtk
from gtk import *
import GdkPixbuf

def close (win, _event=None):
	win.hide ()
	win.destroy ()

def resize (win, event):
	im = win.get_data ("user_data")
	pix = win.children()[0]
	win.remove (pix)
	pix = im.xmake_pixmap ()
	pix.show ()
	win.add (pix)

def open_img (_b):
	file = fs.get_filename ()
	try:
		im = GdkPixbuf.GdkPixbufFromFile (file)
	except Exception: # RuntimError like pyimlib??
		return
	win = GtkWindow ()
	win.connect ("destroy", close)
	win.connect ("delete_event", close)
	win.connect ("configure_event", resize)
	win.set_title (file)
	win.set_data ("user_data", im)
	pix = im.xmake_pixmap ()
	pix.show ()
	win.add (pix)
	win.show ()

fs = GtkFileSelection ()
fs.set_title ("Image Viewer (GdkPixbuf)")
fs.connect ("destroy", mainquit)
fs.connect ("delete_event", mainquit)

label = fs.ok_button.children()[0]
label.set_text ("View")
fs.ok_button.connect ("clicked", open_img)

label = fs.cancel_button.children()[0]
label.set_text ("Quit")
fs.cancel_button.connect ("clicked", mainquit)

fs.show ()

mainloop ()

