#!/usr/bin/python
import gtklib

from gtk import *
import GDK
import GdkPixbuf
import sys

interp_type = GdkPixbuf.INTERP_BILINEAR
overall_alpha = 255
pixbuf = None
darea = None

def set_interp_type (widget, data):
	global interp_type, darea
	interp_type = data
	darea.queue_draw ()

def overall_changed_cb (adjustment):
	global overall_alpha, darea
	if adjustment.value != overall_alpha:
		overall_alpha = adjustment.value
		darea.queue_draw ()

def expose_cb (widget, event):
	global pixbuf, interp_type, overall_alpha
	# gdk_window_set_back_pixmap (widget->window, NULL, FALSE);
	event_x, event_y, event_width, event_height = event.area
	widget_alloc         = widget.get_allocation()
	widget_alloc_width   = widget_alloc[2]
	widget_alloc_height  = widget_alloc[3]

	dest = GdkPixbuf.GdkPixbufBlank (GdkPixbuf.COLORSPACE_RGB, FALSE, 8,
					event_width, event_height)
	
	GdkPixbuf.pixbuf_composite_color (pixbuf, dest, 0, 0,
				event_width, event_height,
				-event_x, -event_y,
				widget_alloc_width / pixbuf.get_width() + 0.0,
				widget_alloc_height / pixbuf.get_height() + 0.0,
				interp_type, overall_alpha,
				event_x, event_y, 16,
				0xaaaaaa, 0x555555)

	dest.render_to_drawable (widget.get_window(),
			widget.get_style().fg_gc[STATE_NORMAL],
			0, 0, event_x, event_y,
			event_width, event_height,
			GDK.RGB_DITHER_NORMAL, event_x, event_y)
	del dest

	return TRUE
				

## MAIN ##
if len(sys.argv) != 2:
	print "Usage: testpixbuf-scale FILE"
	sys.exit (1)

push_rgb_visual ()

pixbuf = GdkPixbuf.GdkPixbufFromFile (sys.argv[1])

window = GtkWindow ()
window.connect ("destroy", mainquit)

vbox = GtkVBox ()
window.add (vbox)

menu = GtkMenu ()

menuitem = GtkMenuItem ("NEAREST")
menuitem.connect ("activate", set_interp_type, GdkPixbuf.INTERP_NEAREST)
menu.show ()
menu.add (menuitem)

menuitem = GtkMenuItem ("BILINEAR")
menuitem.connect ("activate", set_interp_type, GdkPixbuf.INTERP_BILINEAR)
menu.show ()
menu.add (menuitem)

menuitem = GtkMenuItem ("TILES")
menuitem.connect ("activate", set_interp_type, GdkPixbuf.INTERP_TILES)
menu.add (menuitem)

menuitem = GtkMenuItem ("HYPER")
menuitem.connect ("activate", set_interp_type, GdkPixbuf.INTERP_HYPER)
menu.add (menuitem)

optionmenu = GtkOptionMenu ()
optionmenu.set_menu (menu)
optionmenu.set_history (1)

alignment = GtkAlignment (0.0, 0.0, 0.0, 0.5)
vbox.pack_start (alignment, FALSE, FALSE, 0)

hbox = GtkHBox (FALSE, 4)
vbox.pack_start (hbox, FALSE, FALSE, 0)

label = GtkLabel ("Overall Alpha:")
hbox.pack_start (label, FALSE, FALSE, 0)

adjustment = GtkAdjustment (overall_alpha, 0, 255, 1, 10, 0)
adjustment.connect ("value_changed", overall_changed_cb)

hscale = GtkHScale (adjustment)
hscale.set_digits (0)
hbox.pack_start (hscale)

alignment.add (optionmenu)
vbox.show_all ()

# Compute the size without the drawing area, so we know how big to make the
# default size
(scratch_requisition_width, scratch_requisition_height) = vbox.size_request ()

darea = GtkDrawingArea ()
vbox.pack_start (darea)

darea.connect ("expose_event", expose_cb)

window.set_default_size (pixbuf.get_width(),
			scratch_requisition_height + pixbuf.get_height())

window.show_all ()
mainloop ()

