import gtk
#from GdkPixbuf import _GdkPixbufKlass, _GdkPixbufAnimationKlass, _GdkPixbufFrameKlass
from GdkPixbuf import GdkPixbuf, GdkPixbufAnimation, GdkPixbufFrame
import _GdkPixbufLoader

class GdkPixbufLoader(gtk.GtkObject):
    """
    signals: 
        "area_prepared"     (loader)
        "area_updated"         (loader, x, y, width, height)
        "frame_done"         (loader, frame)
        "animation_done"     (loader)
        "closed"         (loader)
    """
    get_type = _GdkPixbufLoader.get_type
    def __init__ (self, _obj=None):
        if _obj:
            self._o = _obj
            return
        self._o = _GdkPixbufLoader.new ()
        self.__connect = self.connect
        self.connect = self.__wrap_connect

    def write (self, buf):
        return _GdkPixbufLoader.write (self._o, buf)
    def get_pixbuf (self):
        pixbuf_obj = _GdkPixbufLoader.get_pixbuf (self._o)
        return GdkPixbuf(_obj=pixbuf_obj)
    def get_animation (self):
        anim_obj = _GdkPixbufLoader.get_animation (self._o)
        return GdkPixbufAnimation(_obj=anim_obj)
    def close (self):
        _GdkPixbufLoader.close (self._o)

    class __frame_done_wrapper:
        def __init__ (self, func):
            self.func = func
        def __call__ (self, loader_obj, frame_obj, *args):
            #print loader_obj, frame_obj, args
            loader = GdkPixbufLoader (loader_obj)
            frame = GdkPixbufFrame (_obj=frame_obj)
            a = list(args)
            for i in range(len(args)):
                if type(args[i]) == _gtk.GtkObjectTupe:
                    a[i] = gtk._obj2inst (args[i])
            a = (loader, frame) + tuple(a)
            ret = apply (self.func, a)
            if hasattr(ret, "_o"):
                ret = ret._o
            return ret

    #FIXME return signal id??
    def __wrap_connect (self, signal_string, func, *args):
        if signal_string == "frame_done":
            #print "__wrap_connect", signal_string, func, args
            fwrap = self.__frame_done_wrapper (func)
            _GdkPixbufLoader.wrap_connect_frame_done (self._o, fwrap, args)
        else:
            a = list(args)
            a.insert (0, func)
            a.insert (0, signal_string)
            a = tuple (a)
            return apply(self.__connect, a)


gtk._name2cls["GdkPixbufLoader"] = GdkPixbufLoader
