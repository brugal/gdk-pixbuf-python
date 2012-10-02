#!/usr/bin/python
import gtklib
from gtk import *
import GdkPixbuf
import _GdkPixbuf

_GdkPixbuf.set_debugging (0)

EXIT_SUCCESS = 0
EXIT_FAILURE = 1

def store_pixel (pixels, beg_index, pixel, alpha):
	if alpha:
		pixels[beg_index + 0] = pixel >> 24
		pixels[beg_index + 1] = pixel >> 16
		pixels[beg_index + 2] = pixel >> 8
		pixels[beg_index + 3] = pixel
	else:
		pixels[beg_index + 0] = pixel >> 16
		pixels[beg_index + 1] = pixel >> 8
		pixels[beg_index + 2] = pixel

def fill_with_pixel (pixbuf, pixel):
	for x in range(pixbuf.get_width()):
		for y in range(pixbuf.get_height()):
			store_pixel (pixbuf.get_pixels(),
				y * pixbuf.get_rowstride() + \
				x * pixbuf.get_n_channels(),
				pixel,
				pixbuf.get_has_alpha())
	

def load_pixel (pixels, beg_index, alpha):
	if alpha:
		return (((((ord(pixels[beg_index + 0]) << 8) | ord(pixels[beg_index + 1])) << 8) | ord(pixels[beg_index + 2])) << 8
) | ord(pixels[beg_index + 3])
	else:
		return (((ord(pixels[beg_index + 0]) << 8) | ord(pixels[beg_index + 1])) << 8) | ord(pixels[beg_index + 2])


def simple_composite_test_one (interp_type, source_pixel, source_alpha, 
			destination_pixel, destination_alpha, expected_result):
	print "simple_composite_test_one (%s, %s, %s, %s, %s, %s)" % \
		(interp_type, source_pixel, source_alpha, destination_pixel,
		destination_alpha, expected_result)

	source_pixbuf = GdkPixbuf.GdkPixbufBlank (GdkPixbuf.COLORSPACE_RGB,
						source_alpha, 8, 32, 32)
	destination_pixbuf = GdkPixbuf.GdkPixbufBlank (GdkPixbuf.COLORSPACE_RGB,
						destination_alpha, 8, 32, 32)
	fill_with_pixel (source_pixbuf, source_pixel)
	fill_with_pixel (destination_pixbuf, destination_pixel)

	GdkPixbuf.pixbuf_composite (source_pixbuf, destination_pixbuf,
				0, 0, 32, 32, 0, 0, 1, 1, interp_type, 0xFF)

	result_pixel = load_pixel (destination_pixbuf.get_pixels(),
				16 * destination_pixbuf.get_rowstride() + \
				16 * destination_pixbuf.get_n_channels(),
				destination_alpha)

	if result_pixel != expected_result:
		if type == GdkPixbuf.INTERP_NEAREST:
			interpolation_type = "GdkPixbuf.INTERP_NEAREST"
		elif type == GdkPixbuf.INTERP_TILES:
			interpolation_type = "GdkPixbuf.INTERP_TILES"
		elif type == GdkPixbuf.INTERP_BILINEAR:
			interpolation_type = "GdkPixbuf.INTERP_BILINEAR"
		elif type == GdkPixbuf.INTERP_HYPER:
			interpolation_type = "GdkPixbuf.INTERP_HYPER"
		else:
			interpolation_type = "???"

		if source_alpha:
			source_string = "0x%08X" % source_pixel
		else:
			source_string = "0x%06X" % source_pixel

		if destination_alpha:
			destination_string = "0x%08X" % destination_pixel
			result_string = "0x%08X" % result_pixel
			expected_string = "0x%08X" % expected_result
		else:
			destination_string = "0x%06X" % destination_pixel
			result_string = "0x%06X" % result_pixel
			expected_string = "0x%06X" % expected_result
		print "ERROR **"
		return FALSE
	
	return TRUE

def simple_composite_test_one_type (type):
	print "\n**\t\tsimple_composite_test_one_type (%s)\t**" % type
	success = TRUE
	# There are only a few trivial cases in here.
	# But these were enough to expose the problems in the old composite
	# code.

	# Non-alpha into non-alpha.
	success = success & simple_composite_test_one (type, 0x000000, FALSE, 0x000000, FALSE, 0x000000)
        success = success & simple_composite_test_one (type, 0x000000, FALSE, 0xFFFFFF, FALSE, 0x000000)
        success = success & simple_composite_test_one (type, 0xFF0000, FALSE, 0x000000, FALSE, 0xFF0000)
        success = success & simple_composite_test_one (type, 0x00FF00, FALSE, 0x000000, FALSE, 0x00FF00)
        success = success & simple_composite_test_one (type, 0x0000FF, FALSE, 0x000000, FALSE, 0x0000FF)
        success = success & simple_composite_test_one (type, 0x000000, FALSE, 0xFF0000, FALSE, 0x000000)
        success = success & simple_composite_test_one (type, 0x000000, FALSE, 0x00FF00, FALSE, 0x000000)
        success = success & simple_composite_test_one (type, 0x000000, FALSE, 0x0000FF, FALSE, 0x000000)
        success = success & simple_composite_test_one (type, 0x00FF00, FALSE, 0xFFFFFF, FALSE, 0x00FF00)
        success = success & simple_composite_test_one (type, 0xFFFFFF, FALSE, 0xFFFFFF, FALSE, 0xFFFFFF)

        # Alpha into non-alpha. 
        success = success & simple_composite_test_one (type, 0x00000000, TRUE, 0x000000, FALSE, 0x000000)
        success = success & simple_composite_test_one (type, 0x00000000, TRUE, 0xFFFFFF, FALSE, 0xFFFFFF)
        success = success & simple_composite_test_one (type, 0x0000007F, TRUE, 0xFFFFFF, FALSE, 0x808080)
        success = success & simple_composite_test_one (type, 0x00000080, TRUE, 0xFFFFFF, FALSE, 0x7F7F7F)
        success = success & simple_composite_test_one (type, 0x000000FF, TRUE, 0xFFFFFF, FALSE, 0x000000)
        success = success & simple_composite_test_one (type, 0x000000FF, TRUE, 0xFFFFFF, FALSE, 0x000000)
        success = success & simple_composite_test_one (type, 0xFF0000FF, TRUE, 0x000000, FALSE, 0xFF0000)
        success = success & simple_composite_test_one (type, 0x00FF00FF, TRUE, 0x000000, FALSE, 0x00FF00)
        success = success & simple_composite_test_one (type, 0x0000FFFF, TRUE, 0x000000, FALSE, 0x0000FF)
        success = success & simple_composite_test_one (type, 0x00000000, TRUE, 0xFF0000, FALSE, 0xFF0000)
        success = success & simple_composite_test_one (type, 0x00000000, TRUE, 0x00FF00, FALSE, 0x00FF00)
        success = success & simple_composite_test_one (type, 0x00000000, TRUE, 0x0000FF, FALSE, 0x0000FF)
        success = success & simple_composite_test_one (type, 0x00FF0080, TRUE, 0xFFFFFF, FALSE, 0x7FFF7F)
        success = success & simple_composite_test_one (type, 0xFFFFFFFF, TRUE, 0xFFFFFF, FALSE, 0xFFFFFF)

        # Non-alpha into alpha.
        success = success & simple_composite_test_one (type, 0x000000, FALSE, 0x00000000, TRUE, 0x000000FF)
        success = success & simple_composite_test_one (type, 0x000000, FALSE, 0xFFFFFFFF, TRUE, 0x000000FF)
        success = success & simple_composite_test_one (type, 0xFF0000, FALSE, 0x00000000, TRUE, 0xFF0000FF)
        success = success & simple_composite_test_one (type, 0x00FF00, FALSE, 0x00000000, TRUE, 0x00FF00FF)
        success = success & simple_composite_test_one (type, 0x0000FF, FALSE, 0x00000000, TRUE, 0x0000FFFF)
        success = success & simple_composite_test_one (type, 0x000000, FALSE, 0xFF0000FF, TRUE, 0x000000FF)
        success = success & simple_composite_test_one (type, 0x000000, FALSE, 0x00FF00FF, TRUE, 0x000000FF)
        success = success & simple_composite_test_one (type, 0x000000, FALSE, 0x0000FFFF, TRUE, 0x000000FF)
        success = success & simple_composite_test_one (type, 0x00FF00, FALSE, 0xFFFFFF00, TRUE, 0x00FF00FF)
        success = success & simple_composite_test_one (type, 0xFFFFFF, FALSE, 0xFFFFFFFF, TRUE, 0xFFFFFFFF)

        # Alpha into alpha. 
        success = success & simple_composite_test_one (type, 0x00000000, TRUE, 0x00000000, TRUE, 0x00000000)
        success = success & simple_composite_test_one (type, 0x00000000, TRUE, 0xFFFFFFFF, TRUE, 0xFFFFFFFF)
        success = success & simple_composite_test_one (type, 0x0000007F, TRUE, 0xFFFFFFFF, TRUE, 0x808080FF)
        success = success & simple_composite_test_one (type, 0x00000080, TRUE, 0xFFFFFFFF, TRUE, 0x7F7F7FFF)
        success = success & simple_composite_test_one (type, 0x000000FF, TRUE, 0xFFFFFFFF, TRUE, 0x000000FF)
        success = success & simple_composite_test_one (type, 0xFF0000FF, TRUE, 0x00000000, TRUE, 0xFF0000FF)
        success = success & simple_composite_test_one (type, 0x00FF00FF, TRUE, 0x00000000, TRUE, 0x00FF00FF)
        success = success & simple_composite_test_one (type, 0x0000FFFF, TRUE, 0x00000000, TRUE, 0x0000FFFF)
        success = success & simple_composite_test_one (type, 0x00000000, TRUE, 0xFF0000FF, TRUE, 0xFF0000FF)
        success = success & simple_composite_test_one (type, 0x00000000, TRUE, 0x00FF00FF, TRUE, 0x00FF00FF)
        success = success & simple_composite_test_one (type, 0x00000000, TRUE, 0x0000FFFF, TRUE, 0x0000FFFF)
        success = success & simple_composite_test_one (type, 0x00FF0080, TRUE, 0xFFFFFF00, TRUE, 0x00FF0080)
        success = success & simple_composite_test_one (type, 0xFF000080, TRUE, 0x00FF0040, TRUE, 0xCC32009F)
        success = success & simple_composite_test_one (type, 0xFFFFFFFF, TRUE, 0xFFFFFFFF, TRUE, 0xFFFFFFFF)

        return success;

def simple_composite_test ():
	success = TRUE

        success = success & simple_composite_test_one_type (GdkPixbuf.INTERP_NEAREST)
        success = success & simple_composite_test_one_type (GdkPixbuf.INTERP_TILES)
        success = success & simple_composite_test_one_type (GdkPixbuf.INTERP_BILINEAR)
        success = success & simple_composite_test_one_type (GdkPixbuf.INTERP_HYPER)

        return success;

# main
result = EXIT_SUCCESS

# Run some tests.
if not simple_composite_test():
	result = EXIT_FAILURE

if result == EXIT_SUCCESS:
	print "SUCCESS\tresult == %d" % result
else:
	print "FAILURE\tresult == %d" % result

