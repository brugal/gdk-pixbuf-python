#include "pygtk.h"
#include "pygdkpixbuf.h"
//#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf-loader.h>

//#include "pygdkpixbuf-loader.h"

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

#ifdef DEBUG__PYGDKPIXBUF
PFUNC (_set_debugging)
{
	GET_ARGS ("i", &debugging);
	Py_INCREF (Py_None);
	return Py_None;
}
#endif

#if 0
static gboolean wrap_frame_done_cb (GdkPixbufLoader *loader, 
				    GdkPixbufFrame *frame, 
				    gpointer data)
{
	PyObject *result, *func, *func_data, *frame_python, *loader_python;
	PyObject *func_data_orig;
	PyObject *crap;
	int check;
	long ret;
	int func_data_length;

	//PyGTK_BLOCK_THREADS
	dbg();
	func = (PyObject *) gtk_object_get_data (GTK_OBJECT (loader),
						"py_frame_done_cb_func");
        func_data_orig = (PyObject *) gtk_object_get_data (GTK_OBJECT (loader),
						"py_frame_done_cb_data");

	Py_XINCREF (func_data_orig);
	/*FIXME check if frame_python == NULL ? */
	frame_python = PyGdkPixbuf_FrameNew (frame);

	if (!PyTuple_Check (func_data_orig))
	{	dprint ("fuck, func_data_orig isn't a tuple.\n");
		PyErr_SetString (PyExc_TypeError, 
				"func_data_orig isn't a tuple");
		goto error;
	}

	func_data_length = PyTuple_Size (func_data_orig);
	dprint ("func_data_length == %d\n", func_data_length);

	func_data = PyTuple_New (func_data_length + 2);
	if (func_data == NULL)
		goto error;

	//if (!PyList_Check (func_data))
	//	dprint ("fuck, func_data isn't a list.\n");

	//Py_XINCREF (func_data);

	loader_python = PyGtk_New ((GtkObject *) loader);
	//Py_XINCREF (loader_python);

//	crap = PyTuple_GetItem (func_data, 0); //, loader_python);
//	PyObject_Print (crap, stderr, Py_PRINT_RAW);
//	Py_XDECREF (crap);
	check = PyTuple_SetItem (func_data, 0, loader_python);
	//check = PyList_SetItem (func_data, 0, loader_python);
	dprint ("tried to set item\n");
	if (check != 0)
	{	//dprint ("error appending Loader to arg tuple %d\n", check);
		//Py_XDECREF (func_data);
		//Py_XDECREF (frame_python);
		//return TRUE;
		//PyErr_SetString (PyExc_RuntimeError, 
		//		"error appending frame to arg tuple\n");
		goto error;
	}

	check = PyTuple_SetItem (func_data, 1, frame_python);
	//check = PyList_SetItem (func_data, 1, frame_python);
	if (check != 0)
	{	//dprint ("error appending frame to arg tuple %d\n", check);
		goto error;	
	}

	result = PyObject_CallObject (func, func_data);
	if (result == NULL)
	{	
		//PyErr_Print ();
		//PyErr_Clear ();
		//PyObject_Print (func, stderr, Py_PRINT_RAW);
		//dprint ("error calling function\n");

		goto error;
	}
	
	if (PyInt_Check (result))
		ret = PyInt_AsLong (result);
	else
	  {	
		dprint ("return value of cb isn't an int??\n");
		Py_XDECREF (result);
		PyErr_SetString (PyExc_RuntimeError, 
				"return value of cb isn't an int??\n"); 
		goto error;
	  }

	Py_XDECREF (result);
	return (gboolean) ret;

error:
	Py_XDECREF (func_data);
	Py_XDECREF (frame_python);
	//dprint ("error calling frame_done_cb\n");
	//if (0) //(PyGtk_FatalExceptions)
	if (PyGtk_FatalExceptions)
	  {	//PyErr_Print ();
		//PyErr_Clear ();
		gtk_main_quit ();
	  }
	else
	  {	PyErr_Print ();
		PyErr_Clear ();
	  }
	//PyGTK_UNBLOCK_THREADS
	return TRUE;
}
#endif


#if 0
static gboolean decref_python_cb (GdkPixbufLoader *loader, gpointer data)
{
	PyObject *func, *func_data;

	dbg();
	func = (PyObject *) gtk_object_get_data (GTK_OBJECT (loader),
						"py_frame_done_cb_func");
	func_data = (PyObject *) gtk_object_get_data (GTK_OBJECT (loader),
						"py_frame_done_cb_data");

	Py_XDECREF (func);
	Py_XDECREF (func_data);

	return FALSE;
}
#endif

#if 0	
//FIXME 
PFUNC (_wrap_connect_frame_done)
{
	PyObject *loader_python, *function, *extra_args = NULL;
	GdkPixbufLoader *loader;

	GET_ARGS ("O!OO!", &PyGtk_Type, &loader_python, &function, 
		&PyTuple_Type, &extra_args);
	Py_XINCREF (loader_python);
	Py_XINCREF (function);
	Py_XINCREF (extra_args);
	loader = (GdkPixbufLoader *) PyGtk_Get (loader_python);
	
	if (!PyCallable_Check (function))
	{	PyErr_SetString (PyExc_TypeError, "arg 2 not callable");
		goto error;
	}
	#if 0
	/*
	if (!PyTuple_Check (extra_args))
	{	PyErr_SetString (PyExc_TypeError, "arg 3 not a tuple");
		goto error;
	}
	*/
	/*FIXME create a new tuple with space for 2 args */
	/* make sure args has the first 2 elements free in order to
	   add the func and func_data
	*/
	gtk_object_set_data (GTK_OBJECT (loader), "py_frame_done_cb_func",
			(gpointer) function);
	gtk_object_set_data (GTK_OBJECT (loader), "py_frame_done_cb_data",
			(gpointer) extra_args);
	/*FIXME will this really work??? What if another call-back is added
	  to "destroy" and that one returns TRUE, will this even get called?
	*/
	/*FIXME just make Loader a new PyGtk type? */
	gtk_signal_connect (GTK_OBJECT (loader), "destroy",
			GTK_SIGNAL_FUNC (decref_python_cb), NULL);
	gtk_signal_connect (GTK_OBJECT (loader), "frame_done",
			GTK_SIGNAL_FUNC (wrap_frame_done_cb), NULL);
	#endif

	Py_XDECREF (loader_python);	
	Py_INCREF (Py_None);
	return Py_None;

error:
	Py_XDECREF (loader_python);
	Py_XDECREF (function);
	Py_XDECREF (extra_args);
	return NULL;
}
#endif

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
				   gpointer func_args_tuple_ptr, 
				   guint nargs, GtkArg *args)
{
	/*FIXME I'm probably fucking this up */
	PyObject *loader_python, *func_args_tuple_orig, *frame_python, *func;
	PyObject *func_args_tuple;
	PyObject *new_args, *result;
	GdkPixbufFrame *frame;
	int check;
		
	PyGtk_BlockThreads ();
	dbg ();

	frame = (GdkPixbufFrame *) GTK_VALUE_POINTER(args[0]);
	func_args_tuple = (PyObject *) func_args_tuple_ptr;
	Py_XINCREF (func_args_tuple);

	
	//loader_python = PyGdkPixbuf_LoaderNew ((GdkPixbufLoader *) loader_ptr);
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

	func = PyTuple_GetItem (func_args_tuple, 0);
	if (func == NULL)
	{	dprint ("couldn't get func from tuple\n");
		goto error;
	}

	check = PyTuple_SetItem (func_args_tuple, 1, loader_python);
	if (check != 0)
	{	dprint ("func_args_tuple[1] = loader_python failed\n");
		goto error;
	}

	check = PyTuple_SetItem (func_args_tuple, 2, frame_python);
	if (check != 0)
	{	dprint ("func_args_tuple[2] = frame_python failed\n");
		goto error;
	}

	/*FIXME are the tuple items "stolen" references??? */
	new_args = PyTuple_GetSlice (func_args_tuple, 1, 
			 	PyTuple_Size(func_args_tuple));
	if (new_args == NULL)
	{	dprint ("new_args = func_args_tuple[1:] failed\n");
		goto error;
	}

	result = PyObject_CallObject (func, new_args);
	if (result == NULL)
	{	Py_XDECREF (new_args);
		dprint ("func(new_args) returned NULL\n");
		goto error;
	}

	GtkRet_FromPyObject (&args[nargs], result);
	Py_DECREF (result);
	PyGtk_UnblockThreads ();
	return;
	
error:
	Py_XDECREF (func_args_tuple);
	if (PyGtk_FatalExceptions)
		gtk_main_quit ();
	else
	  {	PyErr_Print ();
		PyErr_Clear ();
	  }
	PyGtk_UnblockThreads ();
	return;
}

#if 0
static void frame_done_cb_destroy_notify (gpointer func_args_tuple)
{
	/* data == the arg tuple */
	/*FIXME handle threads ? */
	//PyGTK_BLOCK_THREADS
	PyGtk_BlockThreads ();
	dbg();
	Py_DECREF ((PyObject *) func_args_tuple);
	PyGtk_UnblockThreads ();
	//PyGTK_UNBLOCK_THREADS
}
#endif

PFUNC (_wrap_connect_frame_done)
{
	PyObject *loader_python, *func; 
	//PyObject *func_args_tuple;
	PyObject *args_tuple;
	//PyObject *result;
	//int args_tuple_length, check, signum, i;
	int signum;
	
	GET_ARGS ("O!OO!", &PyGtk_Type, &loader_python, &func,
		&PyTuple_Type, &args_tuple);
	if (!PyCallable_Check (func))
	{	PyErr_SetString (PyExc_TypeError, "2nd arg not callable");
		return NULL;
	}

	Py_XINCREF (args_tuple);

	#if 0
	args_tuple_length = PyTuple_Size (args_tuple);
	/* func_args_tuple == 
	   (func, None <room for GdkPixbufLoader*>, None <room for 
	   GdkPixbufFrame*>) + args_tuple
	*/
	func_args_tuple = PyTuple_New (args_tuple_length + 3);
	if (func_args_tuple == NULL)
	{	Py_XDECREF (args_tuple);
		return NULL;
	}

	check = PyTuple_SetItem (func_args_tuple, 0, func);
	if (check != 0)
	{	Py_XDECREF (args_tuple);
		return NULL;
	}

	for (i = 0;  i < args_tuple_length;  i++)
	{
		PyObject *tuple_item;
		tuple_item = PyTuple_GetItem (args_tuple, i);
		if (tuple_item == NULL)
		{	Py_XDECREF (args_tuple);
			return NULL;
		}
		check = PyTuple_SetItem (func_args_tuple, i + 3, tuple_item);
		if (check != 0)
		{	Py_XDECREF (args_tuple);
			return NULL;
		}
	}

	signum = gtk_signal_connect_full (PyGtk_Get(loader_python), 
			"frame_done", NULL,
			(GtkCallbackMarshal) marshal_frame_done_cb,
			func_args_tuple, 
			frame_done_cb_destroy_notify, FALSE, FALSE);
	#endif
	signum = gtk_signal_connect_full (PyGtk_Get(loader_python), 
			"frame_done", NULL,
			(GtkCallbackMarshal) marshal_frame_done_cb,
			args_tuple, 
			frame_done_cb_destroy_notify, FALSE, FALSE);
	
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
	Py_XINCREF (loader_py);
	loader = (GdkPixbufLoader *) PyGtk_Get (loader_py);	

	ret = gdk_pixbuf_loader_write (GDK_PIXBUF_LOADER (loader),
				(guchar *) buf,
				(size_t) count);
	Py_XDECREF (loader_py);
	return Py_BuildValue ("i", ret);
}

PFUNC (_get_pixbuf)
{
	PyObject *loader_py;
	GdkPixbufLoader *loader;
	GdkPixbuf *pixbuf;

	GET_ARGS ("O!", &PyGtk_Type, &loader_py);
	Py_XINCREF (loader_py);
	loader = (GdkPixbufLoader *) PyGtk_Get (loader_py);

	pixbuf = gdk_pixbuf_loader_get_pixbuf (GDK_PIXBUF_LOADER (loader));
	gdk_pixbuf_ref (pixbuf);

	Py_XDECREF (loader_py);
	return PyGdkPixbuf_PixbufNew (pixbuf);
}

PFUNC (_get_animation)
{
	PyObject *python_loader;
	GdkPixbufLoader *loader;
	GdkPixbufAnimation *animation;

	GET_ARGS ("O!", &PyGtk_Type, &python_loader);
	Py_XINCREF (python_loader);
	loader = (GdkPixbufLoader *) PyGtk_Get(python_loader);

	animation = gdk_pixbuf_loader_get_animation (loader);

	Py_XDECREF (python_loader);
	return PyGdkPixbuf_AnimationNew (animation);
}

PFUNC (_close)
{
	PyObject *loader_py;
	GdkPixbufLoader *loader;

	GET_ARGS ("O!", &PyGtk_Type, &loader_py);
	Py_XINCREF (loader_py);
	loader = (GdkPixbufLoader *) PyGtk_Get(loader_py);

	gdk_pixbuf_loader_close (GDK_PIXBUF_LOADER (loader));

	Py_XDECREF (loader_py);
	Py_INCREF (Py_None);
	return Py_None;
}

PFUNC (_frame_to_pyobject)
{
	PyObject *frame_cobject;
	GdkPixbufFrame *frame;
	//PyObject *frame_new;
	
	GET_ARGS ("O", &frame_cobject);
	Py_XINCREF (frame_cobject);

	if (!PyCObject_Check (frame_cobject))
	{	PyErr_SetString (PyExc_TypeError, "arg not a CObject");
		Py_XDECREF (frame_cobject);
		return NULL;
	}

	frame = (GdkPixbufFrame *) PyCObject_AsVoidPtr (frame_cobject);

	dprint ("returning\n");	
	Py_XDECREF (frame_cobject);
	
	//frame_new = _PyGdkPixbuf_API->pygdkpixbuf_frame_new (frame);
	//return frame_new;
	return PyGdkPixbuf_FrameNew (frame);
}

#define PYMETHOD(function) { #function, _ ## function, METH_VARARGS }

static PyMethodDef _GdkPixbufLoader_Methods[] = {
#ifdef DEBUG__PYGDKPIXBUF
	PYMETHOD (set_debugging),
#endif
	PYMETHOD (wrap_connect_frame_done),
	PYMETHOD (get_type),
	PYMETHOD (new),
	PYMETHOD (write),
	PYMETHOD (get_pixbuf),
	PYMETHOD (get_animation),
	PYMETHOD (close),

	PYMETHOD (frame_to_pyobject),
	{NULL, NULL}
};

extern void init_GdkPixbufLoader (void)
{
	dbg();
	(void) Py_InitModule ("_GdkPixbufLoader", _GdkPixbufLoader_Methods);
	init_pygtk ();
	init_pygdkpixbuf ();
	if (PyErr_Occurred())
		Py_FatalError ("can't initialize module _GdkPixbufLoader");
	//dbg();
}
