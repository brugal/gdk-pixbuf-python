#include "pygtk.h"
#include "pygdkpixbuf.h"
#include <gdk-pixbuf/gdk-pixbuf-loader.h>

#ifdef DEBUG__PYGDKPIXBUF
	static int debugging = FALSE;
	#define dbg() \
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
#endif /* DEBUG__PYGDKPIXBUF_LOADER */

#define PFUNC(x) \
	static PyObject *x (PyObject *self, PyObject *args)
#define GET_ARGS(format, xxx...) \
	dbg(); \
	if (!PyArg_ParseTuple (args, format ":" __FUNCTION__, ## xxx))  \
		return NULL

PFUNC (_set_debugging)
{
#ifdef DEBUG__PYGDKPIXBUF
	GET_ARGS ("i", &debugging);
#endif
	Py_INCREF (Py_None);
	return Py_None;
}


/* Can't simply connect "frame_done" signal like the others.  The handler
   is of type:  gint func (GdkPixbufLoader *loader,
			   GdkPixbufFrame  *frame,
			   gpointer         data)
   If you simply connect it from python it will pass in 'frame' as a
   CObject, and since it wasn't created with a 'destroy' handler you can't
   manipulate 'frame' within python code (program will silently exit).
   We need to get a hold of 'frame' first, convert it to a GtkObject and
   then pass it on to the user function in python.
*/
static void marshal_frame_done_cb (GtkObject *loader_ptr, 
				   gpointer data, 
				   guint nargs, GtkArg *args)
{
	/*FIXME I'm probably fucking this up */
	PyObject *loader_python, *frame_python, *func;
	PyObject *func_and_args_tuple;
	PyObject *args_tuple, *result, *new_args_tuple;
	GdkPixbufFrame *frame;
	int args_tuple_length, check, i;
		
	PyGtk_BlockThreads ();
	dbg ();

	frame = (GdkPixbufFrame *) GTK_VALUE_POINTER(args[0]);
	func_and_args_tuple = (PyObject *) data;
	Py_XINCREF (func_and_args_tuple);

	loader_python = PyGtk_New (loader_ptr);
	if (loader_python == NULL)
	{	dprint ("couldn't make loader_python\n");
		goto error;
	}

	frame_python = PyGdkPixbuf_FrameNew (frame);
	if (frame_python == NULL)
	{	dprint ("couldn't make frame_python\n");
		goto error;
	}

	func = PyTuple_GetItem (func_and_args_tuple, 0);
	if (func == NULL)
	{	dprint ("couldn't get func from tuple\n");
		goto error;
	}

	args_tuple = PyTuple_GetItem (func_and_args_tuple, 1);
	if (args_tuple == NULL)
	{	dprint ("couldn't get args tuple\n");
		goto error;
	}

	args_tuple_length = PyTuple_Size (args_tuple);
	/* new_args_tuple = (GdkPixbufLoader *l, GdkPixbufFrame *f, 
	                     args_tuple[0], args_tuple[1], etc ...)
	*/
	new_args_tuple = PyTuple_New (args_tuple_length + 2);
	if (new_args_tuple == NULL)
	{	dprint ("couldn't create new args tuple\n");
		goto error;
	}

	check = PyTuple_SetItem (new_args_tuple, 0, loader_python);
	if (check != 0)
	{	dprint ("couldn't add GdkPixbufLoader to new args tuple\n");
		Py_XDECREF (new_args_tuple);
		goto error;
	}

	check = PyTuple_SetItem (new_args_tuple, 1, frame_python);
	if (check != 0)
	{	dprint ("couldn't add GdkPixbufFrame to new args tuple\n");
		Py_XDECREF (new_args_tuple);
		goto error;
	}

	for (i = 0;  i < args_tuple_length;  i++)
	{	PyObject *item;
		item = PyTuple_GetItem (args_tuple, i);
		if (item == NULL)
		{	Py_XDECREF (new_args_tuple);	
			goto error;
		}
		Py_XINCREF (item);

		check = PyTuple_SetItem (new_args_tuple, i + 2, item);
		if (check != 0)
		{	dprint ("couldn't convert args to new args\n");
			Py_XDECREF (new_args_tuple);
			goto error;
		}
	}
	
	result = PyObject_CallObject (func, new_args_tuple);
	if (result == NULL)
	{	Py_XDECREF (new_args_tuple);
		//dprint ("func(new_args_tuple) returned NULL\n");
		goto error;
	}

	GtkRet_FromPyObject (&args[nargs], result);

	Py_XDECREF (new_args_tuple);
	Py_DECREF (result);
	Py_XDECREF (func_and_args_tuple);
	PyGtk_UnblockThreads ();
	return;
	
error:
	//PyErr_Print ();
	//PyErr_Clear ();
	Py_XDECREF (func_and_args_tuple);
	if (PyGtk_FatalExceptions)
		gtk_main_quit ();
	else
	  {	PyErr_Print ();
		PyErr_Clear ();
	  }
	PyGtk_UnblockThreads ();
	return;
}


PFUNC (_wrap_connect_frame_done)
{
	PyObject *loader_python, *func; 
	PyObject *args_tuple;
	PyObject *data;
	int signum;
	
	GET_ARGS ("O!OO!", &PyGtk_Type, &loader_python, &func,
		&PyTuple_Type, &args_tuple);
		//&args_tuple);
	if (!PyCallable_Check (func))
	{	PyErr_SetString (PyExc_TypeError, "2nd arg not callable");
		return NULL;
	}

	Py_XINCREF (args_tuple);

	data = Py_BuildValue ("(OO)", func, args_tuple);
	if (data == NULL)
	{	Py_XDECREF (args_tuple);
		return NULL;
	}

	signum = gtk_signal_connect_full (PyGtk_Get(loader_python), 
			"frame_done", NULL,
			(GtkCallbackMarshal) marshal_frame_done_cb,
			data, 
			PyGtk_DestroyNotify, FALSE, FALSE);

	return PyInt_FromLong(signum);
}


PFUNC (_get_type)
{
	GET_ARGS ("");
	return PyInt_FromLong (gdk_pixbuf_loader_get_type());
}

PFUNC (_new)
{
	GET_ARGS ("");
	return PyGtk_New((GtkObject *) gdk_pixbuf_loader_new());
}

PFUNC (_write)
{
	PyObject *loader_py;
	GdkPixbufLoader *loader;
	char *buf;
	int count;
	gboolean ret;

	GET_ARGS ("O!s#", &PyGtk_Type, &loader_py, &buf, &count);
	loader = (GdkPixbufLoader *) PyGtk_Get (loader_py);	

	ret = gdk_pixbuf_loader_write (GDK_PIXBUF_LOADER (loader),
				(guchar *) buf,
				(size_t) count);
	return Py_BuildValue ("i", ret);
}

PFUNC (_get_pixbuf)
{
	PyObject *loader_py;
	GdkPixbufLoader *loader;
	GdkPixbuf *pixbuf;

	GET_ARGS ("O!", &PyGtk_Type, &loader_py);
	loader = (GdkPixbufLoader *) PyGtk_Get (loader_py);

	pixbuf = gdk_pixbuf_loader_get_pixbuf (GDK_PIXBUF_LOADER (loader));
	gdk_pixbuf_ref (pixbuf);

	return PyGdkPixbuf_PixbufNew (pixbuf);
}

PFUNC (_get_animation)
{
	PyObject *python_loader;
	GdkPixbufLoader *loader;
	GdkPixbufAnimation *animation;

	GET_ARGS ("O!", &PyGtk_Type, &python_loader);
	loader = (GdkPixbufLoader *) PyGtk_Get(python_loader);

	animation = gdk_pixbuf_loader_get_animation (loader);

	return PyGdkPixbuf_AnimationNew (animation);
}

PFUNC (_close)
{
	PyObject *loader_py;
	GdkPixbufLoader *loader;

	GET_ARGS ("O!", &PyGtk_Type, &loader_py);
	loader = (GdkPixbufLoader *) PyGtk_Get(loader_py);

	gdk_pixbuf_loader_close (GDK_PIXBUF_LOADER (loader));

	Py_INCREF (Py_None);
	return Py_None;
}


#define PYMETHOD(function) { #function, _ ## function, METH_VARARGS }

static PyMethodDef _GdkPixbufLoader_Methods[] = {
	PYMETHOD (wrap_connect_frame_done),
	PYMETHOD (get_type),
	PYMETHOD (new),
	PYMETHOD (write),
	PYMETHOD (get_pixbuf),
	PYMETHOD (get_animation),
	PYMETHOD (close),

	PYMETHOD (set_debugging),
	{NULL, NULL}
};

extern void init_GdkPixbufLoader (void)
{
	dbg();
	Py_InitModule ("_GdkPixbufLoader", _GdkPixbufLoader_Methods);
	init_pygtk ();
	init_pygdkpixbuf ();
	if (PyErr_Occurred())
		Py_FatalError ("can't initialize module _GdkPixbufLoader");
}
