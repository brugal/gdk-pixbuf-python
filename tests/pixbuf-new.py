#!/usr/bin/python
import gtklib
import GdkPixbuf
from Test import *

import _GdkPixbuf
_GdkPixbuf.set_debugging (1)

win = GtkWindow ()
win.connect ("destroy", mainquit)
win.set_usize (200, 200)
button = GtkButton ("quit")
button.connect ("clicked", mainquit)
win.add (button)
win.show_all ()

files = ["pic.jpg", "pic.gif", "pic.xpm", "pic.ppm", "pic.png"]
for file in files:
	pixbuf = GdkPixbuf.GdkPixbufFromFile (file)
	show_pixbuf (pixbuf, file)

pixbuf_copy = pixbuf.copy ()
show_pixbuf (pixbuf_copy, "this is a copy()")

pixbuf = GdkPixbuf.GdkPixbufBlank (colorspace=GdkPixbuf.COLORSPACE_RGB,
				has_alpha=TRUE, bits_per_sample=8,
				width=50, height=50)
show_pixbuf (pixbuf, "new with alpha=TRUE")

pixbuf = GdkPixbuf.GdkPixbufBlank (colorspace=GdkPixbuf.COLORSPACE_RGB,
                                has_alpha=FALSE, bits_per_sample=8,
                                width=50, height=50)
show_pixbuf (pixbuf, "new with alpha=FALSE")

f = open ("pic.ppm", "r")
magic_number = f.readline ()
line = f.readline ()
import string
width, height = string.split (line)
width = string.atoi (width)
height = string.atoi (height)
data = f.read ()
f.close ()

pixbuf = GdkPixbuf.GdkPixbufFromData (data=data, 
		colorspace=GdkPixbuf.COLORSPACE_RGB, has_alpha=FALSE,
		bits_per_sample=8, width=width, height=height,
		rowstride=width * 3) #, destroy_fn=None, destroy_fn_data=None)
show_pixbuf (pixbuf, "new from data")

xpm_data = [
"32 32 9 1",
"       s None  c None",
"o      c #999999",
"O      c black",
"+      c #333333",
"@      c #111111",
"#      c #FF6666",
"$      c #FEFE00",
"%      c #DDDDDD",
"&      c #BBBBBB",
"                                ",
"                                ",
"                                ",
"                                ",
"                                ",
"                                ",
"                                ",
"                                ",
"           oOoOo                ",
"          O     Oo              ",
"         o        O             ",
"         O        o             ",
"       +++++       O            ",
"       +@@@+       o            ",
"      +@@O@@+       O           ",
"    ++@OOO@O@++     o  #       $",
"   +@@OOOOOOO@@+    O      $  # ",
"  +@OOOOOOOOOOO@+    o  $       ",
"  +@OOOOOO%&oOO@+    O   #  $   ",
" +@OOOOOOOO%&oOO@+    o         ",
" +@OOOOOOOOOOOOO@+     OoO # $ #",
" +@OOOOOOOOO%&oO@+              ",
" +@OOOOOOOOO%&oO@+      $   $   ",
" +@OOOOOOOOO%&oO@+        #  #  ",
" +@OOOOOOOO%&oOO@+     #        ",
" +@OOOOOOOO%&oOO@+    $   $    $",
"  +@OOOOOO%&oOO@+               ",
"  +@OOOOOOOOOOO@+         #     ",
"   +@@OOOOOOO@@+                ",
"    ++@@@@@@@++                 ",
"      +++++++                   ",
"                                "
]

pixbuf = GdkPixbuf.GdkPixbufFromXpmData (xpm_data)
show_pixbuf (pixbuf, "from xpm data")

mainloop ()


