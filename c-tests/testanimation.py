#!/usr/bin/python
import gtklib

from gtk import *
import GDK
import GTK
import sys
import os
import string
import GdkPixbuf

import _GdkPixbuf
_GdkPixbuf.set_debugging (0)

class ProgressFileStatus:
	imagefile = None
	loader = None
	rgbwin = None
	buf = None
	timeout = None
	readlen = None


DEFAULT_WIDTH  = 24
DEFAULT_HEIGHT = 24

default_image = [
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xae, 0xb3, 0xb3, 0xc6, 0xc9, 0xcd, 0xd7, 0xd4, 0xdf,
	0xec, 0xde, 0xf3, 0xe7, 0xcb, 0xe9, 0xd9, 0xb5, 0xd3, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xb1, 0xb7, 0xa5,
	0xb0, 0xb8, 0xad, 0xb3, 0xb9, 0xb6, 0xc1, 0xc6, 0xc8, 0xd5, 0xd3, 0xdc,
	0xec, 0xde, 0xf3, 0xe5, 0xca, 0xe6, 0xe0, 0xbb, 0xd7, 0xe1, 0xad, 0xc2,
	0xe3, 0xac, 0xa3, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xca, 0xc1, 0xa4, 0xc5, 0xc7, 0xac,
	0xb7, 0xbe, 0xaf, 0xad, 0xb4, 0xaf, 0xbd, 0xc2, 0xc3, 0xd1, 0xd0, 0xd8,
	0xec, 0xde, 0xf3, 0xe5, 0xc7, 0xe4, 0xe0, 0xb6, 0xd1, 0xe7, 0xa9, 0xb4,
	0xed, 0xcd, 0xb6, 0xd6, 0xcf, 0xae, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0x00, 0x00, 0x00, 0xdf, 0xa7, 0x9f, 0xdd, 0xbf, 0xaa, 0xcf, 0xc5, 0xa9,
	0xc1, 0xc4, 0xac, 0xb2, 0xba, 0xaf, 0xb6, 0xbb, 0xbb, 0xcd, 0xce, 0xd4,
	0xec, 0xde, 0xf3, 0xe4, 0xc4, 0xe1, 0xe0, 0xaf, 0xc7, 0xea, 0xbc, 0xae,
	0xe1, 0xd6, 0xb6, 0xc7, 0xcc, 0xae, 0xa2, 0xab, 0x9a, 0x00, 0x00, 0x00,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0x00, 0x00, 0x00, 0xe3, 0xab, 0xc0, 0xe6, 0xa3, 0xa7, 0xdf, 0xba, 0xa8,
	0xcf, 0xc5, 0xa9, 0xbd, 0xc2, 0xae, 0xad, 0xb4, 0xaf, 0xc6, 0xc9, 0xcd,
	0xec, 0xde, 0xf3, 0xe2, 0xbf, 0xdc, 0xe7, 0xa9, 0xb4, 0xe7, 0xd6, 0xb8,
	0xc7, 0xcc, 0xae, 0xac, 0xb6, 0xa6, 0x9d, 0xa8, 0x9f, 0x00, 0x00, 0x00,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00,
	0xd9, 0xaf, 0xcf, 0xe1, 0xb4, 0xd2, 0xe2, 0xb0, 0xcb, 0xe4, 0xa9, 0xbb,
	0xe2, 0xb2, 0xa6, 0xcf, 0xc5, 0xa9, 0x6a, 0x6a, 0x6a, 0x0d, 0x0d, 0x0d,
	0x0d, 0x0d, 0x0d, 0x6a, 0x6a, 0x6a, 0xed, 0xcd, 0xb6, 0xc7, 0xcc, 0xae,
	0xa6, 0xb1, 0xa3, 0x98, 0xa2, 0x9c, 0x8f, 0x97, 0x96, 0x7e, 0x84, 0x85,
	0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00,
	0xe8, 0xc6, 0xe7, 0xe5, 0xc2, 0xe3, 0xe3, 0xbd, 0xdd, 0xe1, 0xb6, 0xd5,
	0xe2, 0xb0, 0xcb, 0x6a, 0x6a, 0x6a, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x6a, 0x6a, 0x6a, 0x9d, 0xa8, 0x9f,
	0x8f, 0x97, 0x96, 0x8b, 0x90, 0x92, 0x97, 0x9e, 0xa2, 0xa0, 0xa7, 0xae,
	0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00,
	0xe7, 0xd3, 0xed, 0xe8, 0xd1, 0xed, 0xe8, 0xce, 0xec, 0xe9, 0xcc, 0xeb,
	0xe8, 0xc6, 0xe7, 0x0d, 0x0d, 0x0d, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x0d, 0x0d, 0x0d, 0x97, 0x9e, 0xa2,
	0xa7, 0xae, 0xb7, 0xb2, 0xb6, 0xc5, 0xba, 0xbc, 0xce, 0xbf, 0xbe, 0xd3,
	0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00,
	0xe9, 0xdf, 0xf0, 0xe9, 0xdf, 0xf0, 0xe9, 0xdf, 0xf0, 0xe9, 0xdf, 0xf0,
	0xe9, 0xdf, 0xf0, 0x0d, 0x0d, 0x0d, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x0d, 0x0d, 0x0d, 0xe1, 0xd2, 0xf7,
	0xe1, 0xd2, 0xf7, 0xe1, 0xd2, 0xf7, 0xe1, 0xd2, 0xf7, 0xe1, 0xd2, 0xf7,
	0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00,
	0xca, 0xc7, 0xd2, 0xc5, 0xc4, 0xcd, 0xbf, 0xbf, 0xc7, 0xb8, 0xb9, 0xc0,
	0xae, 0xaf, 0xb6, 0x6a, 0x6a, 0x6a, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x6a, 0x6a, 0x6a, 0xd5, 0xa8, 0xe1,
	0xd8, 0xb2, 0xe9, 0xd9, 0xb8, 0xed, 0xdb, 0xbd, 0xf0, 0xdc, 0xbf, 0xf1,
	0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00,
	0xa4, 0xa6, 0xac, 0xa8, 0xaa, 0xaf, 0xa0, 0xa6, 0xa8, 0x98, 0x9e, 0x9c,
	0xa1, 0xa8, 0x9e, 0xb1, 0xb6, 0xa1, 0x6a, 0x6a, 0x6a, 0x0d, 0x0d, 0x0d,
	0x0d, 0x0d, 0x0d, 0x6a, 0x6a, 0x6a, 0xc0, 0x8c, 0xad, 0xcc, 0x90, 0xb5,
	0xd3, 0x94, 0xca, 0xd6, 0xa2, 0xdb, 0xd5, 0xa8, 0xe1, 0xcf, 0xa7, 0xdf,
	0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0x00, 0x00, 0x00, 0x98, 0x9f, 0x9b, 0xa1, 0xa8, 0x9e, 0xac, 0xb3, 0xa0,
	0xb9, 0xb9, 0xa4, 0xd0, 0xb8, 0xa8, 0xc5, 0xb5, 0xb8, 0xb6, 0xbb, 0xad,
	0xe3, 0xd7, 0xb5, 0xdd, 0xb4, 0xa9, 0xcb, 0x89, 0xac, 0xc0, 0x8c, 0xad,
	0xc8, 0x91, 0xb5, 0xd1, 0x8d, 0xb7, 0xd3, 0x94, 0xca, 0x00, 0x00, 0x00,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0x00, 0x00, 0x00, 0xa1, 0xa7, 0x98, 0xb1, 0xb6, 0xa1, 0xbd, 0xb9, 0xa5,
	0xd0, 0xb8, 0xa8, 0xca, 0xb5, 0xb7, 0xb8, 0xb1, 0xb1, 0xc2, 0xc8, 0xb2,
	0xe3, 0xd7, 0xb5, 0xe1, 0xbf, 0xaf, 0xdb, 0x92, 0x9a, 0xbe, 0x82, 0xa6,
	0xc0, 0x8c, 0xad, 0xc8, 0x91, 0xb4, 0xc7, 0x8b, 0xb0, 0x00, 0x00, 0x00,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xbc, 0xb6, 0xa1, 0xd0, 0xb8, 0xa8,
	0xcd, 0xb6, 0xb7, 0xc0, 0xb4, 0xb5, 0xb1, 0xb1, 0xaa, 0xca, 0xd1, 0xb4,
	0xe3, 0xd7, 0xb5, 0xe2, 0xc1, 0xb0, 0xdb, 0xa8, 0xa3, 0xd2, 0x8a, 0xa9,
	0xb7, 0x7e, 0xa2, 0xbd, 0x89, 0xa9, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0xc9, 0xaf, 0xaf,
	0xc5, 0xb5, 0xb8, 0xb8, 0xb1, 0xb1, 0xb6, 0xbb, 0xad, 0xd0, 0xd6, 0xb5,
	0xe3, 0xd7, 0xb5, 0xe2, 0xbf, 0xaf, 0xdd, 0xb4, 0xa9, 0xdb, 0x92, 0x9a,
	0xc6, 0x84, 0xa7, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xac, 0xaa, 0xa6, 0xbd, 0xc3, 0xb0, 0xd2, 0xd7, 0xb5,
	0xe3, 0xd7, 0xb5, 0xe2, 0xbf, 0xae, 0xdb, 0xb6, 0xa8, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff,
	0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff
]


def expose_func (drawing_area, event):
	(event_x, event_y, event_width, event_height) = event.area
	pixbuf = drawing_area.get_data ("pixbuf")

	if pixbuf.get_has_alpha():
		drawing_area.draw_rgb_32_image ( \
				drawing_area.get_style().black_gc,
				event_x, event_y, event_width, event_height,
				GDK.RGB_DITHER_MAX,
				pixbuf.get_pixels()[ \
					event_y * pixbuf.get_rowstride() + \
					event_x * pixbuf.get_n_channels():],
				pixbuf.get_rowstride())
	else:
		drawing_area.draw_rgb_image ( \
				drawing_area.get_style().white_gc,
				event_x, event_y, event_width, event_height,
				GDK.RGB_DITHER_NORMAL,
				pixbuf.get_pixels()[ \
					event_y * pixbuf.get_rowstride() + \
					event_x * pixbuf.get_n_channels():],
				pixbuf.get_rowstride())
				

def config_func (drawing_area, event):
	pixbuf = drawing_area.get_data ("pixbuf")

def new_testrgb_window (pixbuf, title):
	w = pixbuf.get_width ()
	h = pixbuf.get_height ()

	win = GtkWindow ()
	win.set_title (title)
	win.set_policy (GTK.POLICY_ALWAYS, GTK.POLICY_NEVER, GTK.POLICY_NEVER)
	win.connect ("destroy", mainquit)

	vbox = GtkVBox ()
	if title:
		vbox.pack_start (GtkLabel(title))

	drawing_area = GtkDrawingArea ()

	temp_box = GtkHBox ()
	drawing_area.size (w, h)
	temp_box.pack_start (drawing_area, FALSE, FALSE, 0)
	vbox.pack_start (temp_box, FALSE, FALSE, 0)

	drawing_area.connect ("expose_event", expose_func)
	drawing_area.connect ("configure_event", config_func)

	drawing_area.set_data ("pixbuf", pixbuf)

	button = GtkButton ("Quit")
	vbox.pack_start (button, FALSE, FALSE, 0)
	button.connect_object ("clicked", win.destroy, win)

	win.add (vbox)
	win.show_all ()
	return win


readlen = 4096;

def main ():
	########### gdk_rgb_set_verbose (TRUE);
	push_rgb_visual ()

	try:
		tbf_readlen = os.environ["TBF_READLEN"]
	except KeyError:
		tbf_readlen = ""
	if tbf_readlen: readlen = string.atoi (tbf_readlen)

	try:
		tbf_bps = os.environ["TBF_KBPS"]
	except KeyError:
		tbf_bps = ""

	if tbf_bps:
		bps = string.atoi (tbf_bps)
		print "Simulating %d kBytes/sec" % bps
		readlen = (bps * 1024) / 10

	i = 1
	if len(sys.argv) == 1:
		print "USAGE: testanimation.py FILE1 ..."
		return 0

	for i in range(1, len(sys.argv)):
		animation = GdkPixbuf.GdkPixbufAnimationFromFile (sys.argv[i])
		j = 0
		frames = animation.get_frames ()
		for frame in frames:	
			pixbuf = frame.get_pixbuf ()
			title = "Frame %d" % j
			print "Frame %d  x:%d y:%d width:%d height:%d" % \
				(j, frame.get_x_offset(), frame.get_y_offset(),
				pixbuf.get_width(), pixbuf.get_height())
			new_testrgb_window (pixbuf, title)
			j = j + 1
		found_valid = TRUE
	
	mainloop ()
	return 0

main ()
