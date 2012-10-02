/* pygdkpixbuf.h */
#ifndef PYGDKPIXBUF_INCLUDED
#define PYGDKPIXBUF_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif /* </ifdef __cplusplus> */

#include <Python.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

struct _PyGdkPixbuf_FunctionStruct {
	PyTypeObject *pygdkpixbuf_pixbuf_type;
	PyObject * (* pygdkpixbuf_pixbuf_new)(GdkPixbuf *pixbuf);

	PyTypeObject *pygdkpixbuf_animation_type;
	PyObject * (* pygdkpixbuf_animation_new)(GdkPixbufAnimation *animation);

	PyTypeObject *pygdkpixbuf_frame_type;
	PyObject * (* pygdkpixbuf_frame_new)(GdkPixbufFrame *frame);
};

typedef struct {
	PyObject_HEAD
	GdkPixbuf *obj;
} PyGdkPixbuf_PixbufObject;

typedef struct {
	PyObject_HEAD
	GdkPixbufAnimation *obj;
} PyGdkPixbuf_AnimationObject;

typedef struct {
	PyObject_HEAD
	GdkPixbufFrame *obj;
} PyGdkPixbuf_FrameObject;

#define PyGdkPixbuf_PixbufGet(x)  (((PyGdkPixbuf_PixbufObject *)(x))->obj)
#define PyGdkPixbuf_AnimationGet(x) (((PyGdkPixbuf_AnimationObject *)(x))->obj)
#define PyGdkPixbuf_FrameGet(x) (((PyGdkPixbuf_FrameObject *)(x))->obj)

/* pygtk syntax */
#define PyGdkPixbufPixbuf_Get(x)  (((PyGdkPixbuf_PixbufObject *)(x))->obj)
#define PyGdkPixbufAnimation_Get(x) (((PyGdkPixbuf_AnimationObject *)(x))->obj)
#define PyGdkPixbufFrame_Get(x) (((PyGdkPixbuf_FrameObject *)(x))->obj)

#ifdef _INSIDE_PYGDKPIXBUF_

	#define PyGdkPixbuf_PixbufCheck(x) \
		((x)->ob_type == &PyGdkPixbuf_PixbufType)
	#define PyGdkPixbuf_AnimationCheck(x) \
		((x)->obj_type == &PyGdkPixbuf_AnimationType)
	#define PyGdkPixbuf_FrameCheck(x) \
		((x)->ob_type == &PyGdkPixbuf_FrameType)

	staticforward PyTypeObject PyGdkPixbuf_PixbufType;
	static PyObject *PyGdkPixbuf_PixbufNew (GdkPixbuf *pixbuf);
	
	staticforward PyTypeObject PyGdkPixbuf_AnimationType;
	static PyObject *PyGdkPixbuf_AnimationNew (
					GdkPixbufAnimation *animation);
	staticforward PyTypeObject PyGdkPixbuf_FrameType;
	static PyObject *PyGdkPixbuf_FrameNew (GdkPixbufFrame *frame);

#else /* _INSIDE_PYGTKPIXBUF_ isn't defined */

#if defined(NO_IMPORT) || defined(NO_IMPORT_PYGDKPIXBUF)
	extern struct _PyGdkPixbuf_FunctionStruct *_PyGdkPixbuf_API;
#else /* NO_IMPORT and NO_IMPORT_PYGDKPIXBUF undefined */
	struct _PyGdkPixbuf_FunctionStruct *_PyGdkPixbuf_API;
#endif /* </ defined(NO_IMPORT) || defined(NO_IMPORT_PYGDKPIXBUF) > */

#define PyGdkPixbuf_PixbufCheck(x) \
	((x)->ob_type == _PyGdkPixbuf_API->pygdkpixbuf_pixbuf_type)
#define PyGdkPixbuf_PixbufType *(_PyGdkPixbuf_API->pygdkpixbuf_pixbuf_type)
#define PyGdkPixbuf_PixbufNew (_PyGdkPixbuf_API->pygdkpixbuf_pixbuf_new)


#define PyGdkPixbuf_AnimationCheck(x) \
	((x)->ob_type == _PyGdkPixbuf_API->pygdkpixbuf_animation_type)
#define PyGdkPixbuf_AnimationType \
		*(_PyGdkPixbuf_API->pygdkpixbuf_animation_type)
#define PyGdkPixbuf_AnimationNew (_PyGdkPixbuf_API->pygdkpixbuf_animation_new)


#define PyGdkPixbuf_FrameCheck(x) \
	((x)->obj_type == _PyGdkPixbuf_API->pygdkpixbuf_frame_type)
#define PyGdkPixbuf_FrameType *(_PyGdkPixbuf_API->pygdkpixbuf_frame_type)
#define PyGdkPixbuf_FrameNew (_PyGdkPixbuf_API->pygdkpixbuf_frame_new)


/* pygtk syntax */
#define PyGdkPixbufPixbuf_Check(x) \
	((x)->ob_type == _PyGdkPixbuf_API->pygdkpixbuf_pixbuf_type)
#define PyGdkPixbufPixbuf_Type *(_PyGdkPixbuf_API->pygdkpixbuf_pixbuf_type)
#define PyGdkPixbufPixbuf_New (_PyGdkPixbuf_API->pygdkpixbuf_pixbuf_new)


#define PyGdkPixbufAnimation_Check(x) \
	((x)->ob_type == _PyGdkPixbuf_API->pygdkpixbuf_animation_type)
#define PyGdkPixbufAnimation_Type \
		*(_PyGdkPixbuf_API->pygdkpixbuf_animation_type)
#define PyGdkPixbufAnimation_New (_PyGdkPixbuf_API->pygdkpixbuf_animation_new)


#define PyGdkPixbufFrame_Check(x) \
	((x)->obj_type == _PyGdkPixbuf_API->pygdkpixbuf_frame_type)
#define PyGdkPixbufFrame_Type *(_PyGdkPixbuf_API->pygdkpixbuf_frame_type)
#define PyGdkPixbufFrame_New (_PyGdkPixbuf_API->pygdkpixbuf_frame_new)


#define init_pygdkpixbuf() \
{	PyObject *pygdkpixbuf = PyImport_ImportModule("_GdkPixbuf"); \
	if (pygdkpixbuf != NULL) \
	  { 	PyObject *module_dict = PyModule_GetDict(pygdkpixbuf); \
		PyObject *cobject = PyDict_GetItemString(module_dict, \
						"_PyGdkPixbuf_API"); \
		if (PyCObject_Check(cobject)  &&  cobject) \
			_PyGdkPixbuf_API = PyCObject_AsVoidPtr (cobject); \
		else \
		  {	Py_FatalError ("could not find _GdkPixbuf_API object");\
			return; \
		  } \
	  } \
	else \
	  {	Py_FatalError ("could not import _GdkPixbuf"); \
		return; \
	  } \
}

#endif /* #ifdef _INSIDE_PYGDKPIXBUF_ */

#ifdef __cplusplus
}
#endif
#endif /* PYGDKPIXBUF_INCLUDED */

