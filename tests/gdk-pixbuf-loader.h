#if loader.py:
*	void (* area_prepared)   (GdkPixbufLoader *loader);
*	void (* area_updated)    (GdkPixbufLoader *loader,
*                                  guint x, guint y, guint width, guint height);
*	void (* frame_done)      (GdkPixbufLoader *loader, 
*				  GdkPixbufFrame *frame);
*	void (* animation_done)  (GdkPixbufLoader *loader);
*	void (* closed)          (GdkPixbufLoader *loader);
	GtkType             gdk_pixbuf_loader_get_type      (void);
*	GdkPixbufLoader    *gdk_pixbuf_loader_new           (void);
*	gboolean      	    gdk_pixbuf_loader_write (GdkPixbufLoader *loader,
*						     const guchar    *buf,
*						     size_t           count);
*	GdkPixbuf      *gdk_pixbuf_loader_get_pixbuf (GdkPixbufLoader *loader);
*	GdkPixbufAnimation *gdk_pixbuf_loader_get_animation (
*						GdkPixbufLoader *loader);
*	void       gdk_pixbuf_loader_close       (GdkPixbufLoader *loader);

