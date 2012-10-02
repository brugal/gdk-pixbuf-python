#include <string.h>

static PyTypeObject PixelsType;

#define Pixels_Check(p) \
		((p)->ob_type == &PixelsType)

typedef struct {
	PyObject_HEAD
	GdkPixbuf *pixbuf;
	guchar *pixels;
	unsigned long int length;
	//int length;
} PixelsObject;

static PyObject *Pixels_New (GdkPixbuf *pixbuf)
{
	PixelsObject *self;

	dbg();
	self = (PixelsObject *) PyObject_NEW (PixelsObject, &PixelsType);
	if (self == NULL)
		return NULL;

	self->pixbuf = pixbuf;
	self->pixels = gdk_pixbuf_get_pixels (pixbuf);
	if (self->pixels == NULL)
	{	PyErr_SetString (PyExc_Exception, "couldn't get pixels");
		return NULL;
	}

	self->length = gdk_pixbuf_get_rowstride(pixbuf) * 
		       gdk_pixbuf_get_height(pixbuf);
	gdk_pixbuf_ref (pixbuf);

	return (PyObject *) self;
}

static void Pixels_Dealloc (PixelsObject *self)
{
	dbg();
	gdk_pixbuf_unref (self->pixbuf);
	PyMem_DEL (self);
}

/* Sequence Methods */

static PyObject *Pixels__repr__ (PixelsObject *self)
{
	dbg();
	return PyString_FromStringAndSize (self->pixels, self->length);
}

static int Pixels_length (PixelsObject *self)
{
	dbg();
	return self->length;
}

static PyObject *Pixels_Concat (PixelsObject *self, PyObject *other)
{
	dbg();
	dprint ("FIXME\n");
	
	Py_INCREF (Py_None);
	return Py_None;
}

static PyObject *Pixels_Repeat (PixelsObject *self, int multiple)
{
	dbg();
	dprint ("FIXME\n");
	
	Py_INCREF (Py_None);
	return Py_None;
}

static PyObject *Pixels__getitem__ (PixelsObject *self, int i)
{
	dbg();
	if (i < 0)
		i = i + self->length;

	if (i >= self->length  ||  i < 0)
	{       PyErr_SetString (PyExc_IndexError, "index error");
                return NULL;
        }

        return Py_BuildValue ("c", self->pixels[i]);
}

static PyObject *Pixels__getslice__ (PixelsObject *self, int beg, int end)
{
	dbg();
	dprint ("beg %d\tend %d\n", beg, end);

#if 0
	/*FIXME */
	//return Py_BuildValue ("s#", self->pixels, self->length);
	return Py_BuildValue ("s#", gdk_pixbuf_get_pixels(self->pixbuf),
			gdk_pixbuf_get_height(self->pixbuf) *
			gdk_pixbuf_get_rowstride (self->pixbuf));
#endif
	/* convert them to their positive equivalents first */
	if (beg < 0)
		beg = self->length + beg;
	if (end < 0)
		end = self->length + end;
		
	if (beg < 0)
		beg = 0;
	if (beg >= self->length)
		return Py_BuildValue ("s", "");

	if (end < 0)
		return Py_BuildValue ("s", "");
	if (end > self->length)
		end = self->length;
	
	if (end <= beg)
		return Py_BuildValue ("s", "");

	dprint ("beg %d\tend %d\n", beg, end);
	
	return Py_BuildValue ("s#", self->pixels + beg, end - beg);
}

static int Pixels__setitem__ (PixelsObject *self, int i, PyObject *val)
{
	dbg();
	if (i < 0)	
		i = i + self->length;

	if (i >= self->length  ||  i < 0)
	{	PyErr_SetString (PyExc_IndexError, "pixel index out of range");
		return -1;
	}

	if (PyInt_Check(val))
	{	self->pixels[i] = (int) PyInt_AsLong (val);
		return 0;
	}

	if (!PyString_Check(val)  ||  PyString_Size(val) != 1)
	{	PyErr_SetString (PyExc_TypeError, 
				"assignment value isn't a character");	
		return -1;
	}

	self->pixels[i] = PyString_AsString(val)[0];
	return 0;
}

static int Pixels__setslice__ (PixelsObject *self, int beg, int end, 
			       PyObject *val)
{
	unsigned slice_length; //, i;
	//guchar *new_values;

	dbg();
	dprint ("beg %d\tend %d\n", beg, end);
	/* convert them to their positive equivalents first */
	if (beg < 0)
		beg = self->length + beg;
	if (end < 0)
		end = self->length + end;
		
	if (beg < 0)
		beg = 0;
	if (beg >= self->length)
		goto index_error;	

	if (end < 0)
		goto index_error;
	if (end > self->length)
		end = self->length;
	
	if (end <= beg)
		goto index_error;

	dprint ("beg %d\tend %d\n", beg, end);

	if (!PyString_Check(val))
	{	PyErr_SetString (PyExc_TypeError, "val is not a string");
		return -1;
	}

	slice_length = end - beg;
	if (PyString_Size(val) != slice_length)
	{	PyErr_SetString (PyExc_ValueError, 
				"slice length not equal to string length");
		return -1;
	}

	memcpy (self->pixels + beg, PyString_AsString(val), slice_length);

	return 0;
		
index_error:
	PyErr_SetString (PyExc_IndexError, "invalid index values");
	return -1;
}

static PySequenceMethods PixelsSequenceMethods = {
        (inquiry) Pixels_length,                /* length */
        (binaryfunc) Pixels_Concat,		/* concat */
        (intargfunc) Pixels_Repeat,		/* repeat */
        (intargfunc) Pixels__getitem__,      	/* get item */
        (intintargfunc) Pixels__getslice__,    	/* get slice */
        (intobjargproc) Pixels__setitem__,     	/* assign item */
        (intintobjargproc) Pixels__setslice__  	/* assign slice */
};

static PyTypeObject PixelsType = {
        PyObject_HEAD_INIT (&PyType_Type)
        0,                              /* ob_size */
        "Pixels",                       /* tp_name */
        sizeof(PixelsObject),           /* tp_basicsize */
        0,                            	/* tp_itemsize */
        /* methods */
        (destructor) Pixels_Dealloc,    /* tp_dealloc */
        (printfunc)0,                 	/* tp_print */
        (getattrfunc)0,      		/* tp_getattr */
        (setattrfunc)0,                 /* tp_setattr */
        (cmpfunc)0,                   	/* tp_compare */
        (reprfunc) Pixels__repr__,      /* tp_repr */
        0,                            	/* tp_as_number */
        &PixelsSequenceMethods,         /* tp_as_sequence */
        0,                       	/* tp_as_mapping */
        (hashfunc)0,                  	/* tp_hash */
        (ternaryfunc)0,                 /* tp_call */
        (reprfunc) Pixels__repr__,     	/* tp_str */
    
        /* Space for future expansion */
        0L,0L,0L,0L,
        NULL 				/* Documentation string */
};
