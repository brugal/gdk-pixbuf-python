/* _GdkPixbuf.c */

/*FIXME enum types */

#include <stdio.h>
#include "pygtk.h"
#define _INSIDE_PYGDKPIXBUF_
#include "pygdkpixbuf.h"

/*************/
#ifdef DEBUG__PYGDKPIXBUF
	#include <gdk/gdkprivate.h>
	static int debugging = FALSE;
	static void dprint_ref_count (void *ptr);
	#define dbg()	\
		if (debugging) { \
			g_print ("%s():\n", __FUNCTION__); \
		}
	#define dprint(format, varargs...) \
		if (debugging) { \
			g_print ("%s(): ", __FUNCTION__); \
			g_print (format, ## varargs); \
		}
#else
	#define dbg()	
	#define dprint(format, varargs...)
	#define dprint_ref_count(x)
#endif /* DEBUG__PYGDKPIXBUF */
/************/

#define PFUNC(x) \
		static PyObject *x (PyObject *self, PyObject *args)
#define GET_ARGS(format, xxx...) \
	dbg(); \
	if (!PyArg_ParseTuple (args, format ":" __FUNCTION__, ## xxx))  \
		return NULL;


PFUNC (_set_debugging)
{
#ifdef DEBUG__PYGDKPIXBUF
	GET_ARGS ("i", &debugging);
#endif
	Py_INCREF (Py_None);
	return Py_None;
}

/**	PyGdkPixbuf_PixbufObject stuff **/

static PyObject *PyGdkPixbuf_PixbufNew (GdkPixbuf *obj)
{
	PyGdkPixbuf_PixbufObject *self;

	dbg();
	if (obj == NULL)
	{	//FIXME raise new Exception ??
		PyErr_SetString (PyExc_Exception, "couldn't create "
				"GdkPixbuf_Pixbuf");
		return NULL;
	}

	self = (PyGdkPixbuf_PixbufObject *) PyObject_NEW (
						PyGdkPixbuf_PixbufObject,
						&PyGdkPixbuf_PixbufType);
	if (self == NULL)
		return NULL;
	self->obj = obj;

	return (PyObject *)self;
}

static void PyGdkPixbuf_PixbufDealloc (PyGdkPixbuf_PixbufObject *self)
{
	dbg();
	gdk_pixbuf_unref (PyGdkPixbuf_PixbufGet(self) );
	PyMem_DEL (self);
}

static int PyGdkPixbuf_PixbufCompare (PyGdkPixbuf_PixbufObject *one, 
			              PyGdkPixbuf_PixbufObject *two)
{
	dbg();
	if (one->obj == two->obj)
		return 0;
	if (one->obj > two->obj)
		return -1;
	return 1;
}

static PyTypeObject PyGdkPixbuf_PixbufType = {
	PyObject_HEAD_INIT (&PyType_Type)
	0,
	"GdkPixbuf_PixbufObject",
	sizeof (PyGdkPixbuf_PixbufObject),
	0,
	(destructor) PyGdkPixbuf_PixbufDealloc,
	(printfunc) 0,
	(getattrfunc) 0,
	(setattrfunc) 0,
	(cmpfunc) PyGdkPixbuf_PixbufCompare,
	(reprfunc) 0,
	0,
	0,
	0,
	(hashfunc) 0,
	(ternaryfunc) 0,
	(reprfunc) 0,
	0L, 0L, 0L, 0L,
	NULL
};

/**	Pixels stuff			**/

static PyObject *Pixels_New (GdkPixbuf *pixbuf);
#include "PixelsObject.c"

	
/** 	PyGdkPixbuf_Animation stuff 	**/

static PyObject *PyGdkPixbuf_AnimationNew (GdkPixbufAnimation *obj)
{
	PyGdkPixbuf_AnimationObject *self;

	dbg();
	if (obj == NULL)
	{	//FIXME raise new Exception ??
		PyErr_SetString (PyExc_Exception, "couldn't create "
				"GdkPixbuf_Animation");
		return NULL;
	}

	self = (PyGdkPixbuf_AnimationObject *) PyObject_NEW (
						PyGdkPixbuf_AnimationObject,
						&PyGdkPixbuf_AnimationType);
	if (self == NULL)
		return NULL;
	self->obj = obj;
	return (PyObject *)self;
}

static void PyGdkPixbuf_AnimationDealloc (PyGdkPixbuf_AnimationObject *self)
{
	dbg();
	gdk_pixbuf_animation_unref (PyGdkPixbuf_AnimationGet(self) );
	PyMem_DEL (self);
}


static int PyGdkPixbuf_AnimationCompare (PyGdkPixbuf_AnimationObject *one, 
			                 PyGdkPixbuf_AnimationObject *two)
{
	dbg();
	if (one->obj == two->obj)
		return 0;
	if (one->obj > two->obj)
		return -1;
	return 1;
}

static PyTypeObject PyGdkPixbuf_AnimationType = {
	PyObject_HEAD_INIT (&PyType_Type)
	0,
	"GdkPixbuf_PixbufObject",
	sizeof (PyGdkPixbuf_AnimationObject),
	0,
	(destructor) PyGdkPixbuf_AnimationDealloc,
	(printfunc) 0,
	(getattrfunc) 0,
	(setattrfunc) 0,
	(cmpfunc) PyGdkPixbuf_AnimationCompare,
	(reprfunc) 0,
	0,
	0,
	0,
	(hashfunc) 0,
	(ternaryfunc) 0,
	(reprfunc) 0,
	0L, 0L, 0L, 0L,
	NULL
};


/**	 PyGdkPixbuf_Frame stuff 	**/

static PyObject *PyGdkPixbuf_FrameNew (GdkPixbufFrame *obj)
{
	PyGdkPixbuf_FrameObject *self;

	dbg();
	if (obj == NULL)
	{	//FIXME raise new Exception ??
		PyErr_SetString (PyExc_Exception, "couldn't create "
				"GdkPixbuf_Frame");
		return NULL;
	}

	self = (PyGdkPixbuf_FrameObject *) PyObject_NEW (
						PyGdkPixbuf_FrameObject,
						&PyGdkPixbuf_FrameType);
	if (self == NULL)
		return NULL;
	self->obj = obj;
	return (PyObject *)self;
}

static void PyGdkPixbuf_FrameDealloc (PyGdkPixbuf_PixbufObject *self)
{
	dbg();
	/* nothing, i guess */
	PyMem_DEL (self);
}


static int PyGdkPixbuf_FrameCompare (PyGdkPixbuf_FrameObject *one, 
			             PyGdkPixbuf_FrameObject *two)
{
	dbg();
	if (one->obj == two->obj)
		return 0;
	if (one->obj > two->obj)
		return -1;
	return 1;
}

static PyTypeObject PyGdkPixbuf_FrameType = {
	PyObject_HEAD_INIT (&PyType_Type)
	0,
	"GdkPixbuf_FrameObject",
	sizeof (PyGdkPixbuf_FrameObject),
	0,
	(destructor) PyGdkPixbuf_FrameDealloc,
	(printfunc) 0,
	(getattrfunc) 0,
	(setattrfunc) 0,
	(cmpfunc) PyGdkPixbuf_FrameCompare,
	(reprfunc) 0,
	0,
	0,
	0,
	(hashfunc) 0,
	(ternaryfunc) 0,
	(reprfunc) 0,
	0L, 0L, 0L, 0L,
	NULL
};


/*FIXME why did I add this? */
PFUNC (_pixbuf_ref)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf;
	GdkPixbuf *ref;

	GET_ARGS ("O!", &PyGdkPixbuf_PixbufType, &python_pixbuf);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);
	
	ref = gdk_pixbuf_ref (pixbuf);

	return PyGdkPixbuf_PixbufNew (ref);
}


/* GdkPixbuf accessors */

PFUNC (_pixbuf_get_colorspace)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf;

	GET_ARGS ("O!:_pixbuf_get_colorspace", &PyGdkPixbuf_PixbufType, 
		&python_pixbuf);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	return Py_BuildValue ("i", (int) gdk_pixbuf_get_colorspace (pixbuf));
}


PFUNC (_pixbuf_get_n_channels)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf;
	int n_channels;

	GET_ARGS ("O!:_pixbuf_get_n_channels", &PyGdkPixbuf_PixbufType, 
		&python_pixbuf);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	n_channels = gdk_pixbuf_get_n_channels (pixbuf);

	return Py_BuildValue ("i", n_channels);
}

PFUNC (_pixbuf_get_has_alpha)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf;
	gboolean has_alpha;

	GET_ARGS ("O!:_pixbuf_get_has_alpha", &PyGdkPixbuf_PixbufType, 
		&python_pixbuf);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	has_alpha = gdk_pixbuf_get_has_alpha (pixbuf);

	return Py_BuildValue ("i", (int) has_alpha);
}

PFUNC (_pixbuf_get_bits_per_sample)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf;
	
	GET_ARGS ("O!:_pixbuf_get_bits_per_sample", &PyGdkPixbuf_PixbufType,
		&python_pixbuf);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	return Py_BuildValue ("i", gdk_pixbuf_get_bits_per_sample (pixbuf));
}
	

PFUNC (_pixbuf_get_pixels)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf;
	//const guchar *pixels;
	//int height, rowstride;
	//PyObject *ret;

	GET_ARGS ("O!:_pixbuf_get_pixels", &PyGdkPixbuf_PixbufType, 
		&python_pixbuf);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	//pixels = gdk_pixbuf_get_pixels (pixbuf);
	//height = gdk_pixbuf_get_height (pixbuf);
	//rowstride = gdk_pixbuf_get_rowstride (pixbuf);

	//ret = Py_BuildValue ("s#", pixels, height * rowstride);
	return Pixels_New(pixbuf);

	//return ret;
}

PFUNC (_pixbuf_get_width)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf;
	int width;

	GET_ARGS ("O!:_pixbuf_get_width", &PyGdkPixbuf_PixbufType, 
		&python_pixbuf);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	width = gdk_pixbuf_get_width (pixbuf);

	return Py_BuildValue ("i", width);
}
	
PFUNC (_pixbuf_get_height)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf;
	int height;

	GET_ARGS ("O!:_pixbuf_get_height", &PyGdkPixbuf_PixbufType, 
		&python_pixbuf);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	height = gdk_pixbuf_get_height (pixbuf);

	return Py_BuildValue ("i", height);
}

PFUNC (_pixbuf_get_rowstride)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf;
	int rowstride;

	GET_ARGS ("O!:_pixbuf_get_rowstride", &PyGdkPixbuf_PixbufType, 
		&python_pixbuf);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	rowstride = gdk_pixbuf_get_rowstride (pixbuf);

	return Py_BuildValue ("i", rowstride);
}

/* Create a blank pixbuf with an optimal rowstride and a new buffer */
PFUNC (_pixbuf_new)
{
	int colorspace, has_alpha, bits_per_sample, width, height;
	GdkPixbuf *pixbuf;

	GET_ARGS ("iiiii:_new", &colorspace, &has_alpha, &bits_per_sample,
		&width, &height);

	pixbuf = gdk_pixbuf_new (colorspace, has_alpha, bits_per_sample,
				width, height);
	
	return PyGdkPixbuf_PixbufNew (pixbuf);
}

/* Copy a pixbuf */
PFUNC (_pixbuf_copy)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf, *new_pixbuf;

	GET_ARGS ("O!:_copy", &PyGdkPixbuf_PixbufType, &python_pixbuf);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	new_pixbuf = gdk_pixbuf_copy (pixbuf);

	return PyGdkPixbuf_PixbufNew (new_pixbuf);
}


/* Simple loading */

PFUNC (_pixbuf_new_from_file)
{
	GdkPixbuf *pixbuf;
	char *filename;

	GET_ARGS ("s:_new_from_file", &filename);

	pixbuf = gdk_pixbuf_new_from_file (filename);

	return PyGdkPixbuf_PixbufNew (pixbuf);
}

/* EXTRA function.  gdk-pixbuf 0,8.0 has a bug loading ppm files.
   it hangs on truncated pnm files. 
*/
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

static int skip_comments_and_whitespace (FILE *fp)
{
	/*FIXME with buffer instead of one char at a time */
	char c;
     	int check_for_end_of_comments = FALSE;
        int nbytes;
        int ret;

        while (1)
        {       nbytes = fread (&c, 1, 1, fp);
                if (nbytes < 1)		/* eof is an error */
                        return -1;
                if (check_for_end_of_comments)
                {       if (c != '#')
                          {	ret = fseek (fp, -1, SEEK_CUR);
                                if (ret != 0)
                                        return -1;
                                return 0;
                          }
                        else
                                check_for_end_of_comments = FALSE;
                }
                if (c == '\n')
                        check_for_end_of_comments = TRUE;
	}
}

static void free_rgb_data (guchar *pixels, gpointer data)
{
	dbg();
	dprint ("\tpixels %p\n", pixels);
	g_free (pixels);
}

PFUNC (_extra_BUGFIX_pixbuf_new_from_file)
{
	char *filename;
	FILE *fp;
	char header[2];
	size_t nbytes;
	GdkPixbuf *pixbuf;

	GET_ARGS ("s:_extra_BUGFIX_new_from_file", &filename);

#define IOERROR(string) \
		{	PyErr_SetString (PyExc_IOError, string); \
			fclose (fp); \
			return NULL; \
		}	

	fp = fopen (filename, "r");
	if (fp == NULL)
	{	PyErr_SetString (PyExc_IOError, "couldn't open file");
		return NULL;
	}
	
	nbytes = fread (header, sizeof (char), 2, fp);
	if (nbytes < 2)
		IOERROR ("couldn't get file type");

	if (header[0] == 'P'  ||  header[0] == 'p') 
	  if (	header[1] == '1'  ||  header[1] == '2'  ||
	 	header[1] == '3'  ||  header[1] == '4'  ||
		header[1] == '5'  ||  header[1] == '6')
	{	/* It's a ppm file */
		guchar *data;
		int width, height, colors;
		int ret_code;

		ret_code = skip_comments_and_whitespace (fp);
		if (ret_code < 0)
			IOERROR ("header info incomplete, EOF");
		ret_code = fscanf (fp, "%d %d", &width, &height);
		if (ret_code < 2)
			IOERROR ("couldn't get width and height");
		ret_code = skip_comments_and_whitespace (fp);
		if (ret_code < 0)
			IOERROR ("header info incomplete, EOF");
		ret_code = fscanf (fp, "%d", &colors);
		if (ret_code < 1)
			IOERROR ("couldn't get number of colors");
		ret_code = skip_comments_and_whitespace (fp);
		if (ret_code < 0)
			IOERROR ("doesn't contain any rgb data");

		dprint ("\twidth == %d\n\theight == %d\n\tcolors == %d\n",
			width, height, colors);
		data = (guchar *) g_malloc (height * width * 3);
		if (data == NULL)
		{	PyErr_SetString (PyExc_MemoryError, "couldn't allocate "
					"memory for rgb data");
			return NULL;
		}

		ret_code = fread (data, sizeof(char), height * width * 3, fp);
		if (ret_code < 0)
		{	g_free (data);
			IOERROR ("error reading rgb data");
		}
		fclose (fp);

		/*FIXME ack, fix has_alpha, colorspace... */
		pixbuf = gdk_pixbuf_new_from_data (data, 
						GDK_COLORSPACE_RGB,
						FALSE, 	/* has alpha */
						8,	/* bits per sample */
						width, height,
						width * 3, /* rowstride */
						free_rgb_data, NULL);
		return PyGdkPixbuf_PixbufNew (pixbuf);
	}

	/* else, file isn't a ppm file */
	fclose (fp);

	pixbuf = gdk_pixbuf_new_from_file (filename);
	if (pixbuf == NULL)
	{	PyErr_SetString (PyExc_IOError, "couldn't get GdkPixbuf from "
						"file");
		return NULL;
	}

	return PyGdkPixbuf_PixbufNew (pixbuf);
#undef IOERROR
}


PFUNC (_pixbuf_new_from_data)
{
	unsigned char *python_data;
	gchar *data;
	int data_length;
	int colorspace, has_alpha, bits_per_sample, width, height, rowstride;
	GdkPixbuf *pixbuf;

	GET_ARGS ("s#iiiiii", &python_data, &data_length, &colorspace, 
		&has_alpha,
		&bits_per_sample, &width, &height, &rowstride);

	/* mother fucker
	data = g_strndup ((gchar *) python_data, data_length);
	*/
	data = g_memdup ((gpointer) python_data, data_length);

#if 0
//FIXME erase this
{
#include <stdio.h>
	FILE *fp;

	fp = fopen ("gdkpixbuf.pixels", "w");
	fwrite (data, sizeof(gchar), data_length, fp);
	fclose (fp);

	fp = fopen ("gdkpixbuf-python.pixels", "w");
	fwrite (python_data, sizeof(gchar), data_length, fp);
	fclose (fp);
}
//
#endif

	pixbuf = gdk_pixbuf_new_from_data ((guchar *) data,
				(GdkColorspace) colorspace,
				(gboolean) has_alpha,
				bits_per_sample, width, height,
				rowstride,
				free_rgb_data,	/* GdkPixbufDestroyNotify */
				NULL);		/* destroy_fn_data */

	return PyGdkPixbuf_PixbufNew (pixbuf);
}	


typedef struct {
	char **data;
	int num_rows;
} PyGdkPixbuf_XpmData;

/*FIXME why? */
static void free_xpm_object (GdkPixbuf *pixbuf, gpointer xpm_object_ptr)
{
	/*FIXME what about the rows with gchars* 's ?? */
	PyGdkPixbuf_XpmData *xpm_object = 
				(PyGdkPixbuf_XpmData *) xpm_object_ptr;
	guint i;
	
	dbg();
	for (i = 0;  i < xpm_object->num_rows;  i++)
		g_free (xpm_object->data[i]);

	g_free (xpm_object);
	gdk_pixbuf_finalize (pixbuf);
}
			
PFUNC (_pixbuf_new_from_xpm_data)
{
	GdkPixbuf *pixbuf;
	PyObject *list_of_strings;
	PyObject *list_element;
	int list_length;
	PyGdkPixbuf_XpmData *xpm_object;
	gchar *row;
	guint i;

	GET_ARGS ("O!", &PyList_Type, &list_of_strings);

	list_length = PyList_Size (list_of_strings);
	xpm_object = (PyGdkPixbuf_XpmData *) 
			g_malloc (sizeof (PyGdkPixbuf_XpmData));
	if (xpm_object == NULL)
	{	PyErr_SetString (PyExc_MemoryError,
				"error allocating memory for xpm data");
		return NULL;
	}

	xpm_object->num_rows = list_length;
	xpm_object->data = (char **) g_malloc (list_length * sizeof (char *));
	if (xpm_object->data == NULL)
	{	PyErr_SetString (PyExc_MemoryError, 
				"error allocation memory for xpm_data");
		g_free (xpm_object);
		return NULL;
	}

#define CLEAN_UP()  { \
	{	guint j; \
		for (j = i - 1;  j >= 0;  j--) \
			g_free (xpm_object->data[j]); \
	} \
	g_free (xpm_object->data); \
	g_free (xpm_object); \
	return NULL; \
}

	for (i = 0;  i < list_length;  i++)
	{	
		list_element = PyList_GetItem (list_of_strings, i);
		if (list_element == NULL)
			CLEAN_UP ();

		if (PyString_Check (list_element) == 0)
		{	PyErr_SetString (PyExc_TypeError,
					"list element is not a string");
			CLEAN_UP ();
		}
	
		row = PyString_AsString (list_element);
		if (row == NULL)
			CLEAN_UP ();

		xpm_object->data[i] = (char *) g_strdup (row);
		if (xpm_object->data[i] == NULL)
		{	PyErr_SetString (PyExc_MemoryError,
					"error allocating memory for xpm_data");
			CLEAN_UP ();
		}
	}

	/*FIXME why is xpm_object->data giving me problems? */
	/* 7/21/00:  huh? */
	pixbuf = gdk_pixbuf_new_from_xpm_data (
				(const char **) xpm_object->data);
	gdk_pixbuf_set_last_unref_handler (pixbuf, free_xpm_object, xpm_object);

	return PyGdkPixbuf_PixbufNew (pixbuf);
#undef CLEAN_UP
}
		
		

/* Adding an alpha channel */
PFUNC (_pixbuf_add_alpha)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf, *new_pixbuf;
	int substitute_color;
	int r, g, b;

	GET_ARGS ("O!iiii", &PyGdkPixbuf_PixbufType, &python_pixbuf,
		&substitute_color, &r, &g, &b);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	new_pixbuf = gdk_pixbuf_add_alpha (pixbuf, (gboolean) substitute_color,
					(guchar) r, (guchar) g, (guchar) b);

	return PyGdkPixbuf_PixbufNew (new_pixbuf);
}

/* Copy an area of a pixbuf onto another one */
PFUNC (_pixbuf_copy_area)
{
	PyObject *src_python_pixbuf, *dest_python_pixbuf;
	GdkPixbuf *src_pixbuf, *dest_pixbuf;
	int src_x, src_y, width, height, dest_x, dest_y;

	GET_ARGS ("O!iiiiO!ii", &PyGdkPixbuf_PixbufType, &src_python_pixbuf,
		&src_x, &src_y, &width, &height,
		&PyGdkPixbuf_PixbufType, &dest_python_pixbuf,
		&dest_x, &dest_y);

	src_pixbuf = PyGdkPixbuf_PixbufGet (src_python_pixbuf);
	dest_pixbuf = PyGdkPixbuf_PixbufGet (dest_python_pixbuf);

	gdk_pixbuf_copy_area (src_pixbuf, src_x, src_y, width, height,
			dest_pixbuf, dest_x, dest_y);
	
	Py_INCREF (Py_None);
	return Py_None;
}

/* Rendering to a drawbable */

PFUNC (_pixbuf_render_threshold_alpha)
{
	PyObject *python_pixbuf, *python_bitmap;
	GdkPixbuf *pixbuf;
	GdkBitmap *bitmap;
	int src_x, src_y, dest_x, dest_y, width, height, alpha_threshold;

	GET_ARGS ("O!O!iiiiiii", &PyGdkPixbuf_PixbufType, &python_pixbuf,
		&PyGdkWindow_Type, &python_bitmap,
		&src_x, &src_y,
		&dest_x, &dest_y,
		&width, &height,
		&alpha_threshold);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);
	bitmap = PyGdkWindow_Get (python_bitmap);

	gdk_pixbuf_render_threshold_alpha (pixbuf, bitmap, src_x, src_y,
					dest_x, dest_y, width, height,
					alpha_threshold);

	Py_INCREF (Py_None);
	return Py_None;
}


PFUNC (_pixbuf_render_to_drawable)
{
	PyObject *python_pixbuf;
	PyObject *python_drawable, *python_gc, *python_dither;
	int src_x, src_y, dest_x, dest_y, width, height, x_dither, y_dither;
	GdkRgbDither dith;

	GET_ARGS ("O!O!O!iiiiiiOii:_render_to_drawable", 
		&PyGdkPixbuf_PixbufType, &python_pixbuf, 
		&PyGdkWindow_Type, &python_drawable,
		&PyGdkGC_Type, &python_gc, &src_x, &src_y, &dest_x, &dest_y,
		&width, &height, &python_dither, &x_dither, &y_dither);
	
	if (PyGtkEnum_get_value (GTK_TYPE_GDK_RGB_DITHER, python_dither,
				(gint *)&dith))
	{	PyErr_SetString (PyExc_IOError, "arg 10 not a "
                                        "valid GDK_RGB_DITHER value");
		return NULL;
	}	

	gdk_pixbuf_render_to_drawable (
			PyGdkPixbuf_PixbufGet (python_pixbuf),
			PyGdkWindow_Get (python_drawable),
			PyGdkGC_Get (python_gc),
			src_x, src_y,
			dest_x, dest_y,
			width, height,
			dith, x_dither, y_dither);

	Py_INCREF (Py_None);
	return Py_None;
}

PFUNC (_pixbuf_render_to_drawable_alpha)
{
	PyObject *python_pixbuf, *python_drawable;
	GdkPixbuf *pixbuf;
	GdkDrawable *drawable;
	int src_x, src_y, dest_x, dest_y, width, height, alpha_mode, 
	    alpha_threshold, dither, x_dither, y_dither;

	GET_ARGS ("O!O!iiiiiiiiiii", &PyGdkPixbuf_PixbufType, &python_pixbuf,
		&PyGdkWindow_Type, &python_drawable,
		&src_x, &src_y, &dest_x, &dest_y, &width, &height, 
		&alpha_mode, &alpha_threshold, &dither, &x_dither, &y_dither);
	dprint ("got args\n");

	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);
	drawable = PyGdkWindow_Get (python_drawable);

	gdk_pixbuf_render_to_drawable_alpha (pixbuf, drawable,
				src_x, src_y,
				dest_x, dest_y,
				width, height,
				(GdkPixbufAlphaMode) alpha_mode,
				alpha_threshold,
				(GdkRgbDither) dither,
				x_dither, y_dither);

	Py_INCREF (Py_None);
	return Py_None;
}

/*FIXME this is fucked up */
PFUNC (_pixbuf_render_pixmap_and_mask)
{
	PyObject *python_pixbuf;
	PyObject *tuple;
	GdkPixbuf *pixbuf;
	GdkPixmap *gdkpixmap;
	GdkBitmap *mask;
	int alpha_threshold;
	int ret;

	GET_ARGS ("O!i:_render_pixmap_and_mask", &PyGdkPixbuf_PixbufType, 
		&python_pixbuf, &alpha_threshold);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	gdk_pixbuf_render_pixmap_and_mask (pixbuf, &gdkpixmap, &mask,
					alpha_threshold);	

	tuple = PyTuple_New (2);
	if (tuple == NULL)
		return NULL;

	ret = PyTuple_SetItem (tuple, 0, PyGdkWindow_New (gdkpixmap));
	if (ret != 0)
		goto error;

	if (mask)
	  {	ret = PyTuple_SetItem (tuple, 1, PyGdkWindow_New (mask));
		if (ret != 0)
			goto error;
	  }
	else
	  {	Py_INCREF (Py_None);
		ret = PyTuple_SetItem (tuple, 1, Py_None);
		if (ret != 0)
			goto error;
	  }

	return tuple;

error:
	Py_DECREF (tuple);
	return NULL;
}

#ifdef DEBUG__PYGDKPIXBUF
static void dprint_ref_count (void *ptr)
{
	GdkPixmap *p = (GdkPixmap *) ptr;
        GdkWindowPrivate *gdkpixmap;

        gdkpixmap = (GdkWindowPrivate *) (p);
	if (debugging)
        {	g_print ("\tref_count(): pixmap->ref_count == %u\n", 
			gdkpixmap->ref_count);
	}
}
#endif /* end   DEBUG__PYGDKPIXBUF */

/***	Extra function for pygdkpixbuf  ***/
PFUNC (_extra_pixbuf_make_gtk_pixmap)
{
	PyObject  *python_pixbuf;
	GdkPixbuf *pixbuf;
	GdkPixmap *gdkpixmap;
	GdkBitmap *bitmap;
	GtkWidget *gtkpixmap;
	int alpha_threshold;

	GET_ARGS ("O!i:_extra_make_pixmap", &PyGdkPixbuf_PixbufType, 
			&python_pixbuf, &alpha_threshold);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	/*FIXME what to put for last arg (alpha_threshold) */
	gdk_pixbuf_render_pixmap_and_mask (pixbuf, &gdkpixmap, &bitmap, 
					alpha_threshold);

	gtkpixmap = gtk_pixmap_new (gdkpixmap, bitmap);
	
	if (gdkpixmap != NULL)
		gdk_pixmap_unref (gdkpixmap);
	if (bitmap != NULL)
		gdk_bitmap_unref (bitmap);
	
	return PyGtk_New ((GtkObject *)gtkpixmap);
}

PFUNC (_pixbuf_get_from_drawable)
{
	PyObject *python_pixbuf, *python_drawable, *python_cmap;
	GdkPixbuf *pixbuf, *new_pixbuf;
	GdkDrawable *drawable;
	GdkColormap *cmap;
	int src_x, src_y, dest_x, dest_y, width, height;

	GET_ARGS ("OOOiiiiii", &python_pixbuf, &python_drawable, &python_cmap,
		&src_x, &src_y, &dest_x, &dest_y, &width, &height);

	if (python_pixbuf == Py_None)
		pixbuf = NULL;
	else
	  {	if (PyGdkPixbuf_PixbufCheck (python_pixbuf))
			pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);
		else
		  {	PyErr_SetString (PyExc_TypeError,
				"Argument 1 should be a GdkPixbuf or None");
			return NULL;
		  }
	  }	

	if (python_drawable == Py_None)
		drawable = NULL;
	else
	  {	if (PyGdkWindow_Check (python_drawable))
			drawable = PyGdkWindow_Get (python_drawable);
		else
		  {	PyErr_SetString (PyExc_TypeError,
				"Argument 2 should be a GdkDrawable or None");
			return NULL;
		  }
	  }	

	if (python_cmap == Py_None)
		cmap = NULL;
	else
	  {	if (PyGdkColormap_Check (python_cmap))
			cmap = PyGdkColormap_Get (python_cmap);
		else
		  {	PyErr_SetString (PyExc_TypeError,
				"Argument 3 should be a GdkColormap or None");
			return NULL;
		  }
	  }	

	new_pixbuf = gdk_pixbuf_get_from_drawable (pixbuf, drawable, cmap,
					src_x, src_y, dest_x, dest_y,
					width, height);

	return PyGdkPixbuf_PixbufNew (new_pixbuf);
}

/* Scaling */
	
PFUNC (_pixbuf_scale)
{
	PyObject *python_pixbuf_src, *python_pixbuf_dest;
	GdkPixbuf *pixbuf_src, *pixbuf_dest;
	int dest_x, dest_y, dest_width, dest_height;
	double offset_x, offset_y, scale_x, scale_y;
	int interp_type;	//FIXME enum type

	GET_ARGS ("O!O!iiiiddddi:_scale", 
		&PyGdkPixbuf_PixbufType, &python_pixbuf_src,
		&PyGdkPixbuf_PixbufType, &python_pixbuf_dest,
		&dest_x, &dest_y, &dest_width, &dest_height,
		&offset_x, &offset_y, &scale_x, &scale_y, &interp_type);
	pixbuf_src = PyGdkPixbuf_PixbufGet (python_pixbuf_src);
	pixbuf_dest = PyGdkPixbuf_PixbufGet (python_pixbuf_dest);

	gdk_pixbuf_scale (pixbuf_src, pixbuf_dest, dest_x, dest_y, dest_width,
			dest_height, offset_x, offset_y, scale_x, scale_y,
			(GdkInterpType) interp_type);

	//FIXME need to check mem-check pixbuf_dest, or does gtk raise error??	
	Py_INCREF (Py_None);
	return Py_None;
}

PFUNC (_pixbuf_composite)
{
	PyObject *src_python_pixbuf, *dest_python_pixbuf;
	GdkPixbuf *src_pixbuf, *dest_pixbuf;
	int dest_x, dest_y, dest_width, dest_height;
	double offset_x, offset_y, scale_x, scale_y;
	int interp_type;
	int overall_alpha;

	GET_ARGS ("O!O!iiiiddddii", &PyGdkPixbuf_PixbufType, &src_python_pixbuf,
		&PyGdkPixbuf_PixbufType, &dest_python_pixbuf,
		&dest_x, &dest_y, &dest_width, &dest_height,
		&offset_x, &offset_y, &scale_x, &scale_y,
		&interp_type,
		&overall_alpha);
	src_pixbuf = PyGdkPixbuf_PixbufGet (src_python_pixbuf);
	dest_pixbuf = PyGdkPixbuf_PixbufGet (dest_python_pixbuf);

	gdk_pixbuf_composite (src_pixbuf, dest_pixbuf,
			dest_x, dest_y, dest_width, dest_height,
			offset_x, offset_y, scale_x, scale_y,
			(GdkInterpType) interp_type,
			overall_alpha);

	Py_INCREF (Py_None);
	return Py_None;
}

PFUNC (_pixbuf_composite_color)
{
	PyObject *src_python_pixbuf, *dest_python_pixbuf;
	GdkPixbuf *src_pixbuf, *dest_pixbuf;
	int dest_x, dest_y, dest_width, dest_height;
	double offset_x, offset_y, scale_x, scale_y;
	int interp_type;
	int overall_alpha, check_x, check_y, check_size;
	long int color1, color2;

	GET_ARGS ("O!O!iiiiddddiiiiill",
		&PyGdkPixbuf_PixbufType, &src_python_pixbuf,
		&PyGdkPixbuf_PixbufType, &dest_python_pixbuf,
		&dest_x, &dest_y, &dest_width, &dest_height,
		&offset_x, &offset_y, &scale_x, &scale_y,
		&interp_type,
		&overall_alpha, &check_x, &check_y, &check_size,
		&color1, &color2);
	src_pixbuf = PyGdkPixbuf_PixbufGet (src_python_pixbuf);
	dest_pixbuf = PyGdkPixbuf_PixbufGet (dest_python_pixbuf);

	gdk_pixbuf_composite_color (src_pixbuf, dest_pixbuf,
				dest_x, dest_y, dest_width, dest_height,
				offset_x, offset_y, scale_x, scale_y,
				(GdkInterpType) interp_type,
				overall_alpha, check_x, check_y, check_size,
				(guint32) color1, (guint32) color2);

	Py_INCREF (Py_None);
	return Py_None;
}
	

PFUNC (_pixbuf_scale_simple)
{
	PyObject *python_pixbuf_src;
	GdkPixbuf *pixbuf_src, *pixbuf_scaled;
	int dest_width, dest_height, interp_type;

	GET_ARGS ("O!iii:_scale_simple", 
		&PyGdkPixbuf_PixbufType, &python_pixbuf_src, 
		&dest_width, &dest_height, &interp_type);
	pixbuf_src = PyGdkPixbuf_PixbufGet (python_pixbuf_src);

	pixbuf_scaled = gdk_pixbuf_scale_simple (pixbuf_src, dest_width,
				dest_height, (GdkInterpType) interp_type);

	return PyGdkPixbuf_PixbufNew (pixbuf_scaled);
}

PFUNC (_pixbuf_composite_color_simple)
{
	PyObject *python_pixbuf;
	GdkPixbuf *pixbuf, *new_pixbuf;
	int dest_width, dest_height;
	int interp_type;
	int overall_alpha, check_size;
	long int color1, color2;

	GET_ARGS ("O!iiiiill", &PyGdkPixbuf_PixbufType, &python_pixbuf,
		&dest_width, &dest_height,
		&interp_type,
		&overall_alpha,
		&check_size,
		&color1, &color2);
	pixbuf = PyGdkPixbuf_PixbufGet (python_pixbuf);

	new_pixbuf = gdk_pixbuf_composite_color_simple (pixbuf,
					dest_width, dest_height,
					(GdkInterpType) interp_type,
					overall_alpha, check_size,
					(guint32) color1, (guint32) color2);

	return PyGdkPixbuf_PixbufNew (new_pixbuf);
}
	
/* Animation support */

PFUNC (_animation_new_from_file)
{
	char *filename;
	GdkPixbufAnimation *animation;

	GET_ARGS ("s:_animation_new_from_file", &filename);

	animation = gdk_pixbuf_animation_new_from_file (filename);
	
	return PyGdkPixbuf_AnimationNew (animation);
}

/*FIXME why? */
PFUNC (_animation_ref)
{
	PyObject *python_animation;
	GdkPixbufAnimation *animation;
	
	GET_ARGS ("O!", &PyGdkPixbuf_AnimationType, &python_animation);
	animation = PyGdkPixbuf_AnimationGet (python_animation);
	
	return PyGdkPixbuf_AnimationNew (gdk_pixbuf_animation_ref(animation));
}

/* gdk_pixbuf_animation_unref() */

PFUNC (_animation_get_width)
{
	PyObject *python_animation;
	GdkPixbufAnimation *animation;
	int width;

	GET_ARGS ("O!", &PyGdkPixbuf_AnimationType, &python_animation);
	animation = PyGdkPixbuf_AnimationGet (python_animation);

	width = gdk_pixbuf_animation_get_width (animation);

	return Py_BuildValue ("i", width);
}

PFUNC (_animation_get_height)
{
	PyObject *python_animation;
	GdkPixbufAnimation *animation;
	int height;

	GET_ARGS ("O!", &PyGdkPixbuf_AnimationType, &python_animation);
	animation = PyGdkPixbuf_AnimationGet (python_animation);

	height = gdk_pixbuf_animation_get_height (animation);

	return Py_BuildValue ("i", height);
}

PFUNC (_animation_get_frames)
{
	PyObject *python_animation;
	GdkPixbufAnimation *animation;
	GList *frames, *node;
	PyObject *plist;
	PyObject *python_frame;
	int check;

	GET_ARGS ("O!", &PyGdkPixbuf_AnimationType, &python_animation);
	animation = PyGdkPixbuf_AnimationGet (python_animation);

	frames = gdk_pixbuf_animation_get_frames (animation);

	//plist = PyList_New (g_list_length(frames));
	plist = PyList_New (0);
	if (plist == NULL)
		return NULL;
	dprint ("made plist\n");	

	for (node = frames;  node != NULL;  node = node->next)
	{	python_frame = PyGdkPixbuf_FrameNew (node->data);
		if (python_frame == NULL)
		{	Py_DECREF (plist);
			return NULL;
		}
	
		check = PyList_Append (plist, python_frame);
		if (check != 0)
		{	Py_DECREF (plist);
			return NULL;
		}
		dprint ("appending...\n");
	}

	dprint ("returning\n");
	return plist;
}	
	
PFUNC (_animation_get_num_frames)
{
	PyObject *python_animation;
	GdkPixbufAnimation *animation;
	int num_frames;

	GET_ARGS ("O!", &PyGdkPixbuf_AnimationType, &python_animation);
	animation = PyGdkPixbuf_AnimationGet (python_animation);

	num_frames = gdk_pixbuf_animation_get_num_frames (animation);

	return Py_BuildValue ("i", num_frames);
}


/* Frame accessors */

PFUNC (_frame_get_pixbuf)
{
	PyObject *python_frame;
	GdkPixbufFrame *frame;
	GdkPixbuf *pixbuf;
	
	GET_ARGS ("O!:_frame_get_pixbuf", &PyGdkPixbuf_FrameType, 
		&python_frame);
	frame = PyGdkPixbuf_FrameGet (python_frame);

	pixbuf = gdk_pixbuf_frame_get_pixbuf (frame);
	/*FIXME ref it ???  is it a ptr or new? */
	(void) gdk_pixbuf_ref (pixbuf);
	return (PyGdkPixbuf_PixbufNew (pixbuf));
}

PFUNC (_frame_get_x_offset)
{
	PyObject *python_frame;
	GdkPixbufFrame *frame;
	int offset;
	
	GET_ARGS ("O!:_frame_get_pixbuf", &PyGdkPixbuf_FrameType,
                &python_frame);
        frame = PyGdkPixbuf_FrameGet (python_frame);

	offset = gdk_pixbuf_frame_get_x_offset (frame);

	return Py_BuildValue ("i", offset);
}

PFUNC (_frame_get_y_offset)
{
	PyObject *python_frame;
	GdkPixbufFrame *frame;
	int offset;
	
	GET_ARGS ("O!:_frame_get_pixbuf", &PyGdkPixbuf_FrameType,
                &python_frame);
        frame = PyGdkPixbuf_FrameGet (python_frame);

	offset = gdk_pixbuf_frame_get_y_offset (frame);

	return Py_BuildValue ("i", offset);
}

PFUNC (_frame_get_delay_time)
{
	PyObject *python_frame;
	GdkPixbufFrame *frame;
	int delay_time;
	
	GET_ARGS ("O!:_frame_get_pixbuf", &PyGdkPixbuf_FrameType,
                &python_frame);
        frame = PyGdkPixbuf_FrameGet (python_frame);

	delay_time = gdk_pixbuf_frame_get_delay_time (frame);

	return Py_BuildValue ("i", delay_time);
}

PFUNC (_frame_get_action)
{
	PyObject *python_frame;
	GdkPixbufFrame *frame;
	GdkPixbufFrameAction action;
	
	GET_ARGS ("O!:_frame_get_pixbuf", &PyGdkPixbuf_FrameType,
                &python_frame);
        frame = PyGdkPixbuf_FrameGet (python_frame);

	action = gdk_pixbuf_frame_get_action (frame);

	return Py_BuildValue ("i", action);
}
	
	
	
/* General (presently empty) initialization hooks, primarily for gnome-libs */
/*FIXME	gdk_pixbuf_preinit ()
	gdk_pixbuf_postinit ()
*/

/**** extra, _gtk.gtk_pixmap_set has a problem accepting 'None' as a bitmask,
	needs a PyGdkWindow_Type, even if it has none.
*/

PFUNC (_extra_gtk_pixmap_set)
{
	PyObject *python_gtkpixmap, *python_gdkpixmap;
	PyObject *python_gdkmask = NULL;
	GdkBitmap *gdkmask;

	GET_ARGS ("O!O!O:_extra_gtk_pixmap_set", &PyGtk_Type, &python_gtkpixmap,
		&PyGdkWindow_Type, &python_gdkpixmap, &python_gdkmask);
	dprint ("python_gdkmask == %p\n", python_gdkmask);

	#if 0
	Py_INCREF (Py_None);
	if (PyObject_Compare (Py_None, python_gdkmask) == 0)
		gdkmask = NULL;
	#endif

	if (python_gdkmask == Py_None)
		gdkmask = NULL;
	else
	  {	if (PyGdkWindow_Check (python_gdkmask))
			gdkmask = PyGdkWindow_Get (python_gdkmask);
		else
		  {	PyErr_SetString (PyExc_TypeError, "arg 2 (mask) is "
					"neither a GdkBitmap nor 'None'.");
			//Py_DECREF (Py_None);
			return NULL;
		  }
	  }
	//Py_DECREF (Py_None);
	
	#if 0
	if (PyErr_Occurred())	/* for PyObject_Compare() above */
		return NULL;
	#endif

	dprint ("gdkmask == %p\n", gdkmask);
	dprint_ref_count (PyGdkWindow_Get (python_gdkpixmap));

	gtk_pixmap_set (GTK_PIXMAP (PyGtk_Get(python_gtkpixmap)),
			PyGdkWindow_Get (python_gdkpixmap),
			gdkmask);

	Py_INCREF (Py_None);
	return Py_None;
}

/*FIXME why? */
/* EXTRA func, not found in pygtk */
PFUNC (_extra_gdk_pixmap_unref)
{
	PyObject *python_gdkpixmap;
	GdkPixmap *gdkpixmap;

	GET_ARGS ("O:_extra_gdk_pixmap_unref", &python_gdkpixmap);
	
	if (python_gdkpixmap == Py_None)
	{	/* no need to unref */
		Py_INCREF (Py_None);
		return Py_None;
	}

	if (PyGdkWindow_Check (python_gdkpixmap))
	  	gdkpixmap = PyGdkWindow_Get (python_gdkpixmap);
	else
	  {	PyErr_SetString (PyExc_TypeError, "expected GdkWindow");
		return NULL;
	  }

	gdk_pixmap_unref (gdkpixmap);

	Py_INCREF (Py_None);
	return Py_None;
}

/* EXTRA func, not found in pygtk */
PFUNC (_extra_gdk_bitmap_unref)
{
	PyObject *python_gdkbitmap;
	GdkBitmap *gdkbitmap;

	GET_ARGS ("O:_extra_gdk_bitmap_unref", &python_gdkbitmap);

	if (python_gdkbitmap == Py_None)
	{	/* no need to unref */
		Py_INCREF (Py_None);
		return Py_None;
	}

	if (PyGdkWindow_Check (python_gdkbitmap))
		gdkbitmap = PyGdkWindow_Get (python_gdkbitmap);
	else
	  {	PyErr_SetString (PyExc_TypeError, "expected GdkWindow");
		return NULL;
	  }

	gdk_pixmap_unref (gdkbitmap);

	Py_INCREF (Py_None);
	return Py_None;
}
	
#define PYMETHOD(function) { #function, _ ## function, METH_VARARGS }

static PyMethodDef _GdkPixbufMethods[] = {
	PYMETHOD (pixbuf_ref),
//	PYMETHOD (pixbuf_unref),
//	PYMETHOD (pixbuf_set_last_unref_handler),
//	PYMETHOD (pixbuf_finalize),

	/* GdkPixbuf accessors */
	PYMETHOD (pixbuf_get_colorspace),
	PYMETHOD (pixbuf_get_n_channels),
	PYMETHOD (pixbuf_get_has_alpha),
	PYMETHOD (pixbuf_get_bits_per_sample),
	PYMETHOD (pixbuf_get_pixels),
	PYMETHOD (pixbuf_get_width),
	PYMETHOD (pixbuf_get_height),
	PYMETHOD (pixbuf_get_rowstride),

	/* Create a blank pixbuf with an optimal rowstride and a new buffer */
	PYMETHOD (pixbuf_new),
	
	/*FIXME Copy a pixbuf 	handle in python? */
	PYMETHOD (pixbuf_copy),

	/* Simple loading */
	PYMETHOD (pixbuf_new_from_file),
	PYMETHOD (extra_BUGFIX_pixbuf_new_from_file),	/* EXTRA FUNCTION, 
							   fixes bug 
							*/
	PYMETHOD (pixbuf_new_from_data),
	PYMETHOD (pixbuf_new_from_xpm_data),

	/* Adding an alpha channel */
	PYMETHOD (pixbuf_add_alpha),
	
	/* Copy an area of pixbuf onto another one */
	PYMETHOD (pixbuf_copy_area),

	/* Rendering to a drawable */
	PYMETHOD (pixbuf_render_threshold_alpha),
	PYMETHOD (pixbuf_render_to_drawable),
	PYMETHOD (pixbuf_render_to_drawable_alpha),
	PYMETHOD (pixbuf_render_pixmap_and_mask),	/*FIXME check this one */
	PYMETHOD (extra_pixbuf_make_gtk_pixmap),	/* EXTRA func */
	PYMETHOD (pixbuf_get_from_drawable),

	/* Scaling */
	PYMETHOD (pixbuf_scale),
	PYMETHOD (pixbuf_composite),
	PYMETHOD (pixbuf_composite_color),
	PYMETHOD (pixbuf_scale_simple),
	PYMETHOD (pixbuf_composite_color_simple),

	/* Animation support */
	PYMETHOD (animation_new_from_file),
	PYMETHOD (animation_ref),
//	PYMETHOD (_animation_unref),
	PYMETHOD (animation_get_width),
	PYMETHOD (animation_get_height),
	PYMETHOD (animation_get_frames),
	PYMETHOD (animation_get_num_frames),

	/* Frame accessors */
	PYMETHOD (frame_get_pixbuf),
	PYMETHOD (frame_get_x_offset),
	PYMETHOD (frame_get_y_offset),
	PYMETHOD (frame_get_delay_time),
	PYMETHOD (frame_get_action),

	/* General (presently empty) initialization hooks, primarily for
	   gnome-libs
	*/
//	PYMETHOD (preinit)
//	PYMETHOD (postinit)

	PYMETHOD (extra_gtk_pixmap_set),	/* EXTRA func */
	PYMETHOD (extra_gdk_pixmap_unref),	/* EXTRA func */
	PYMETHOD (extra_gdk_bitmap_unref),	/* EXTRA func */

	PYMETHOD (set_debugging),
	{NULL, NULL}
};

static struct _PyGdkPixbuf_FunctionStruct functions = {
	&PyGdkPixbuf_PixbufType, 
	PyGdkPixbuf_PixbufNew,

	&PyGdkPixbuf_AnimationType,
	PyGdkPixbuf_AnimationNew,

	&PyGdkPixbuf_FrameType,
	PyGdkPixbuf_FrameNew
};

void init_GdkPixbuf (void)
{
	PyObject *pygdkpixbuf_module, *pygdkpixbuf_dictionary, *private;

	pygdkpixbuf_module = Py_InitModule ("_GdkPixbuf", _GdkPixbufMethods);
	pygdkpixbuf_dictionary = PyModule_GetDict (pygdkpixbuf_module);

	PyDict_SetItemString (pygdkpixbuf_dictionary, "GdkPixbuf_PixbufType",
			(PyObject *)&PyGdkPixbuf_PixbufType);
	PyDict_SetItemString (pygdkpixbuf_dictionary, "_PyGdkPixbuf_API",
			PyCObject_FromVoidPtr (&functions, NULL));

	private = PyDict_New ();
	PyDict_SetItemString (pygdkpixbuf_dictionary, "_private", private);
	Py_DECREF (private);

	#if 0
	PyDict_SetItemString (private, "PyGdkPixbuf_New", 
	   pygdkpixbuf_dictionary=PyCObject_FromVoidPtr(PyGdkPixbuf_New, NULL));
	Py_DECREF (pygdkpixbuf_dictionary);
	#endif

	/* get references to the pygtk types and functions */
	init_pygtk ();
	if (PyErr_Occurred())
		Py_FatalError ("can't initialize module _GdkPixbuf");
}

