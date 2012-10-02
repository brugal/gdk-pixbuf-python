import gtklib
from gtk import *
import GdkPixbuf
import _GdkPixbuf
import sys

def set_debugging (val):
	_GdkPixbuf.set_debugging (val)

def _catch_signals ():
	# catching keyboard interrupt and exiting
	# only works if os.eniron["PYGTK_FATAL_EXCEPTIONS"] == "TRUE"
	return TRUE

timeout_add (100, _catch_signals)

def loop ():
	while events_pending():
		mainiteration()

def app ():
	win = GtkWindow ()
	win.set_title (sys.argv[0])
	win.connect ("destroy", mainquit)
	win.set_usize (200, 200)
	button = GtkButton ("quit %s" % sys.argv[0])
	button.connect ("clicked", mainquit)
	win.add (button)
	win.show_all ()

def show_pixbuf (pixbuf, title=""):
        win = GtkWindow ()
        win.set_title (title)
        win.set_usize (400, 400)

        sw = GtkScrolledWindow ()
        win.add (sw)

        vbox = GtkVBox ()
        sw.add_with_viewport (vbox)
        
        pixmap = pixbuf.xmake_pixmap ()
        vbox.pack_start (pixmap)

        info = PixbufInfo (pixbuf)
        label = GtkLabel (info.get_info())
        vbox.pack_start (label)

        win.show_all ()


class PixbufInfo:
	def __init__ (self, pixbuf):
		self.pixbuf = pixbuf

	def get_info (self):
		self.colorspace = self.pixbuf.get_colorspace ()
		self.n_channels = self.pixbuf.get_n_channels ()
		self.has_alpha = self.pixbuf.get_has_alpha ()
		self.bits_per_sample = self.pixbuf.get_bits_per_sample ()
		self.pixels = self.pixbuf.get_pixels()
		self.width = self.pixbuf.get_width ()
		self.height = self.pixbuf.get_height ()
		self.rowstride = self.pixbuf.get_rowstride ()

		info = ""	
		if self.colorspace != 0:
			info = "*ERROR colorspace != GdkPixbuf.COLORSPACE_RGB\n"
		else:
			info = "colorspace == GdkPixbuf.COLORSPACE_RGB\n"
		info = info + "n_channels == %d\n" % self.n_channels
		if self.has_alpha == TRUE:
			info = info + "has_alpha == TRUE\n"
		else:
			info = info + "has_alpha == FALSE\n"
		info = info + "bits_per_sample == %d\n" % self.bits_per_sample
		info = info + "pixels == " + `(self.pixels[:10],)` + " ...\n"
		print info
		info = info + "width == %d\n" % self.width
		info = info + "height == %d\n" % self.height
		info = info + "rowstride == %d" % self.rowstride
	
		self.info = info	
		return info

