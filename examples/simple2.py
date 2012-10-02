#!/usr/bin/python
import gtklib, sys
from gtk import *
from GdkPixbuf import *
w = GtkWindow ()
w.add (GdkPixbufFromFile(sys.argv[1]).xmake_pixmap())
w.show_all ()
mainloop ()
