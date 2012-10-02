import _GdkPixbuf
from gtk import GtkPixmap

#FIXME where do I place all these enums???
import GDK
# GdkColorspace
GDK.COLORSPACE_RGB = 0

COLORSPACE_RGB = 0

# GdkPixbufAlphaMode
GDK.PIXBUF_ALPHA_BILEVEL = 0
GDK.PIXBUF_ALPHA_FULL    = 1

ALPHA_BILEVEL = 0
ALPHA_FULL    = 1

# GdkInterpType
GDK.INTERP_NEAREST  = 0
GDK.INTERP_TILES    = 1
GDK.INTERP_BILINEAR = 2
GDK.INTERP_HYPER    = 3

INTERP_NEAREST  = 0
INTERP_TILES    = 1
INTERP_BILINEAR = 2
INTERP_HYPER    = 3


# GdkPixbufFrameAction
GDK.PIXBUF_FRAME_RETAIN  = 0
GDK.PIXBUF_FRAME_DISPOSE = 1
GDK.PIXBUF_FRAME_REVERT  = 2

FRAME_RETAIN  = 0
FRAME_DISPOSE = 1
FRAME_REVERT  = 2


class GdkPixbuf:
	def __init__ (self, colorspace=None, has_alpha=None,
		      bits_per_sample=None, width=None, height=None,
		      _obj=None):
		if _obj != None:
			self._o = _obj
		else:
			self._o = _GdkPixbuf.pixbuf_new (colorspace, has_alpha,
						bits_per_sample, width, height)
	def ref (self):
		return GdkPixbuf (_obj=_GdkPixbuf.pixbuf_ref(self._o))
	# no ###def unref (self):
	# don't use set_last_unref_handler, shouldn't really have python
	# binding, just did it for the heck of it.
	#def set_last_unref_handler (self, function, *args):
	#	_GdkPixbuf.pixbuf_set_last_unref_handler (self._o,
	#				function, args)
	# no ###def finalize (self):
	def get_colorspace (self):
		return _GdkPixbuf.pixbuf_get_colorspace (self._o)
	def get_n_channels (self):
		return _GdkPixbuf.pixbuf_get_n_channels (self._o)
	def get_has_alpha (self):
		return _GdkPixbuf.pixbuf_get_has_alpha (self._o)
	def get_bits_per_sample (self):
		return _GdkPixbuf.pixbuf_get_bits_per_sample (self._o)
	def get_pixels (self):
		return _GdkPixbuf.pixbuf_get_pixels (self._o)
	def get_width (self):
		return _GdkPixbuf.pixbuf_get_width (self._o)
	def get_height (self):
		return _GdkPixbuf.pixbuf_get_height (self._o)
	def get_rowstride (self):
		return _GdkPixbuf.pixbuf_get_rowstride (self._o)
	# no ###def new (self):
	def copy (self):
		return GdkPixbuf (_obj=_GdkPixbuf.pixbuf_copy (self._o))
	def add_alpha (self, substitute_color, r, g, b):
		obj = _GdkPixbuf.pixbuf_add_alpha (self._o, substitute_color,
						r, g, b)
		return GdkPixbuf (_obj=obj)	
	def copy_area (self, src_x, src_y, width, height, dest_pixbuf,
			dest_x, dest_y):
		_GdkPixbuf.pixbuf_copy_area (self._o, src_x, src_y, 
				width, height,
				dest_pixbuf._o, dest_x, dest_y)

	def render_threshold_alpha (self, bitmap, src_x, src_y, dest_x,
				dest_y, width, height, alpha_threshold):
			_GdkPixbuf.pixbuf_render_threshold_alpha (self._o,
					bitmap, src_x, src_y, dest_x, dest_y,
					width, height, alpha_threshold)
	# crashes if you don't push_rgb_visual() before using
	def render_to_drawable (self, drawable, gc, src_x, src_y, dest_x,
				dest_y, width, height, dither, x_dither,
				y_dither):
		_GdkPixbuf.pixbuf_render_to_drawable (self._o, drawable, 
					gc, src_x, src_y, 
					dest_x, dest_y, width, height,
					dither, x_dither, y_dither)
	def render_to_drawable_alpha (self, drawable, src_x, src_y, dest_x,
				dest_y, width, height, alpha_mode,
				alpha_threshold, dither, x_dither, y_dither):
		_GdkPixbuf.pixbuf_render_to_drawable_alpha (self._o,
			drawable, src_x, src_y, dest_x, dest_y, width,
			height, alpha_mode, alpha_threshold, dither,
			x_dither, y_dither)
	def render_pixmap_and_mask (self, alpha_threshold=0):
		(gdkpixmap, mask) = _GdkPixbuf.pixbuf_render_pixmap_and_mask (
							self._o,
							alpha_threshold)
		return (gdkpixmap, mask)	#FIXME this right????
	# EXTRA FUNCTION
	def xmake_pixmap (self, alpha_threshold=0):		# EXTRA FUNC 
		return GtkPixmap(_obj=_GdkPixbuf.extra_pixbuf_make_gtk_pixmap(
						self._o, alpha_threshold))
	# no ###def get_from_drawable (self):
	def scale (self, pixbuf_dest, dest_x, dest_y, dest_width,
			dest_height, offset_x, offset_y, scale_x, scale_y,
			interp_type):
		#FIXME haven't tested this yet
		_GdkPixbuf.pixbuf_scale (self._o, pixbuf_dest._o, 
				dest_x, dest_y,
				dest_width, dest_height, offset_x, offset_y,
				scale_x, scale_y, interp_type)
	# no ##def composite (self):
	# no ##def composite_color (
	def scale_simple (self, dest_width, dest_height, interp_type):
		#FIXME interp_type=SomeDefault  .. work out enum_types in
		#	_GdkPixbuf.c
		obj = _GdkPixbuf.pixbuf_scale_simple (self._o,
				dest_width, dest_height, interp_type)	
		return GdkPixbuf (_obj=obj)	
	def composite_color_simple (self, dest_width, dest_height,
				interp_type, overall_alpha, check_size,
				color1, color2):
		obj = _GdkPixbuf.pixbuf_composite_color_simple (self._o, 
						dest_width,
						dest_height, interp_type,
						overall_alpha, check_size,
						color1, color2)
		return GdkPixbuf (_obj=obj)


		
def GdkPixbufFromFile (filename):
	#obj = _GdkPixbuf.pixbuf_new_from_file (filename)
	obj = _GdkPixbuf.extra_BUGFIX_pixbuf_new_from_file (filename)
	return GdkPixbuf (_obj=obj)

# EXTRA FUNCTION
# Fixes a bug in gtk 0.8.0, library hangs if ppm file is too short
def GdkPixbuf_bugfix_from_file (filename):
	obj = _GdkPixbuf.extra_BUGFIX_pixbuf_new_from_file (filename)
	return GdkPixbuf (_obj=obj)

def GdkPixbufFromDrawable (dest_pixbuf, drawable_src, cmap, src_x, src_y,
			   dest_x, dest_y, width, height):
	if dest_pixbuf != None:
		dest_pixbuf = dest_pixbuf._o
	obj = _GdkPixbuf.pixbuf_get_from_drawable (
			dest_pixbuf, drawable_src, cmap, src_x, src_y,
			dest_x, dest_y, width, height)
	return GdkPixbuf (_obj=obj)

def GdkPixbufFromData (data, colorspace, has_alpha, bits_per_sample, width,
		       height, rowstride):
	obj = _GdkPixbuf.pixbuf_new_from_data (data, colorspace, has_alpha,
				bits_per_sample, width, height, rowstride)
	return GdkPixbuf (_obj=obj)

def GdkPixbufFromXpmData (data):
	"""data is a list of strings"""
	obj = _GdkPixbuf.pixbuf_new_from_xpm_data (data)
	return GdkPixbuf (_obj=obj)


def pixbuf_get_from_drawable (pixbuf_dest, drawable_src, cmap, src_x, src_y,
				dest_x, dest_y, width, height):
	obj = _GdkPixbuf.pixbuf_get_from_drawable (pixbuf_dest._o, 
					drawable_src._o,
					cmap, src_x, src_y, dest_x, dest_y,
					width, height)
	return GdkPixbuf (_obj=obj)

def pixbuf_composite (pixbuf_src, pixbuf_dest, dest_x, dest_y, dest_width,
			dest_height, offset_x, offset_y, scale_x, scale_y,
			interp_type, overall_alpha):
	_GdkPixbuf.pixbuf_composite (pixbuf_src._o, pixbuf_dest._o, dest_x,
				dest_y, dest_width, dest_height, offset_x,
				offset_y, scale_x, scale_y, interp_type,
				overall_alpha)

def pixbuf_composite_color (pixbuf_src, pixbuf_dest, dest_x, dest_y,
			dest_width, dest_height, offset_x, offset_y,
			scale_x, scale_y, interp_type, overall_alpha,
			check_x, check_y, check_size, color1, color2):
	_GdkPixbuf.pixbuf_composite_color (pixbuf_src._o, pixbuf_dest._o,
				dest_x, dest_y, dest_width, dest_height,
				offset_x, offset_y, scale_x, scale_y,
				interp_type, overall_alpha, check_x, check_y,
				check_size, color1, color2)

def pixbuf_composite_color_simple (pixbuf_src, dest_width, dest_height,
			interp_type, overall_alpha, check_size,
			color1, color2):
	obj = _GdkPixbuf.pixbuf_composite_color_simple (pixbuf_src._o,
					dest_width, dest_height, interp_type,
					overall_alpha, check_size,
					color1, color2)
	return GdkPixbuf (_obj=obj)

class GdkPixbufFrame:
	def __init__ (self, _obj):
		self._o = _obj
	def get_pixbuf (self):
		#FIXME how to handle referencing??
		obj = _GdkPixbuf.frame_get_pixbuf (self._o)
		#pixbuf_obj = _GdkPixbuf._pixbuf_ref (obj)
		#return GdkPixbufKlass (pixbuf_obj)
		return GdkPixbuf (_obj=obj)
	def get_x_offset (self):
		return _GdkPixbuf.frame_get_x_offset (self._o)
	def get_y_offset (self):
		return _GdkPixbuf.frame_get_y_offset (self._o)
	def get_delay_time (self):
		return _GdkPixbuf.frame_get_delay_time (self._o)
	def get_action (self):
		return _GdkPixbuf.frame_get_action (self._o)

class GdkPixbufAnimation:
	def __init__ (self, filename=None, _obj=None):
		if _obj != None:
			self._o = _obj
		else:
			self._o = _GdkPixbuf.animation_new_from_file (filename)
	def ref (self):
		obj = _GdkPixbuf.animation_ref (self._o)	
		return GdkPixbufAnimation (_obj=obj)
	###def unref
	def get_width (self):
		return _GdkPixbuf.animation_get_width (self._o)
	def get_height (self):
		return _GdkPixbuf.animation_get_height (self._o)
	def get_frames (self):
		# ugly
		frames_obj_list = _GdkPixbuf.animation_get_frames (self._o)
		frames = []
		for obj in frames_obj_list:
			frames.append (GdkPixbufFrame(_obj=obj))
		return frames
	def get_num_frames (self):
		return _GdkPixbuf.animation_get_num_frames (self._o)

def GdkPixbufAnimationFromFile (filename):
	obj = _GdkPixbuf.animation_new_from_file (filename)
	return GdkPixbufAnimation (_obj=obj)

# these are currently empty
def preinit (*args):
	pass
def postinit (*args):
	pass

# EXTRA FUNCTIONS needed by some routines, not available in pygtk ######
#FIXME forgot why I added these...
def xgtk_pixmap_set (gtkpixmap, gdkpixmap, mask):
	_GdkPixbuf.extra_gtk_pixmap_set (gtkpixmap._o, gdkpixmap, mask)
def xgdk_pixmap_unref (gdkpixmap):
	_GdkPixbuf.extra_gdk_pixmap_unref (gdkpixmap)
def xgdk_bitmap_unref (gdkbitmap):
	_GdkPixbuf.extra_gdk_bitmap_unref (gdkbitmap)

### garbage, can't decide on naming convention
GdkPixbufBlank = GdkPixbuf
GdkPixbuf_Blank = GdkPixbufBlank
GdkPixbuf_from_file = GdkPixbufFromFile
GdkPixbuf_from_drawable = GdkPixbufFromDrawable
GdkPixbuf_from_data = GdkPixbufFromData
GdkPixbuf_from_xpm_data = GdkPixbufFromXpmData
GdkPixbufAnimation_from_file = GdkPixbufAnimationFromFile

GdkPixbuf_FromFile = GdkPixbufFromFile
GdkPixbuf_FromDrawable = GdkPixbufFromDrawable
GdkPixbuf_FromData = GdkPixbufFromData
GdkPixbuf_FromXpmData = GdkPixbufFromXpmData
GdkPixbufAnimation_FromFile = GdkPixbufAnimationFromFile

