####	typedef void (* GdkPixbufDestroyNotify) (guchar *pixels, gpointer data);
####	typedef void (* GdkPixbufLastUnref) (GdkPixbuf *pixbuf, gpointer data);
####	/* Reference counting */
####	GdkPixbuf *gdk_pixbuf_ref      (GdkPixbuf *pixbuf);
####	void       gdk_pixbuf_unref    (GdkPixbuf *pixbuf);
####	void       gdk_pixbuf_set_last_unref_handler (
####					GdkPixbuf *pixbuf,
####					GdkPixbufLastUnref  last_unref_fn,
####					gpointer            last_unref_fn_data);
####	void       gdk_pixbuf_finalize (GdkPixbuf *pixbuf);

#if pixbuf-new.py
*	/* GdkPixbuf accessors */
*	GdkColorspace gdk_pixbuf_get_colorspace      (const GdkPixbuf *pixbuf);
*	int           gdk_pixbuf_get_n_channels      (const GdkPixbuf *pixbuf);
*	gboolean      gdk_pixbuf_get_has_alpha       (const GdkPixbuf *pixbuf);
*	int           gdk_pixbuf_get_bits_per_sample (const GdkPixbuf *pixbuf);
*	guchar       *gdk_pixbuf_get_pixels          (const GdkPixbuf *pixbuf);
*	int           gdk_pixbuf_get_width           (const GdkPixbuf *pixbuf);
*	int           gdk_pixbuf_get_height          (const GdkPixbuf *pixbuf);
*	int           gdk_pixbuf_get_rowstride       (const GdkPixbuf *pixbuf);
*	/* Create a blank pixbuf with an optimal rowstride and a new buffer */
*	GdkPixbuf *gdk_pixbuf_new (GdkColorspace colorspace, 
*				   gboolean has_alpha, int bits_per_sample,
*			   	   int width, int height);
*	/* Copy a pixbuf */
*	GdkPixbuf *gdk_pixbuf_copy (const GdkPixbuf *pixbuf);
*	/* Simple loading */
*	GdkPixbuf *gdk_pixbuf_new_from_file (const char *filename);
*	GdkPixbuf *gdk_pixbuf_new_from_data (const guchar *data,
*				     GdkColorspace colorspace,
*				     gboolean has_alpha,
*				     int bits_per_sample,
*				     int width, int height,
*				     int rowstride,
*				     GdkPixbufDestroyNotify destroy_fn,
*				     gpointer destroy_fn_data);
*	GdkPixbuf *gdk_pixbuf_new_from_xpm_data (const char **data);

#if util.py:
*	/* Adding an alpha channel */
*	GdkPixbuf *gdk_pixbuf_add_alpha (const GdkPixbuf *pixbuf, 
*				 gboolean substitute_color,
*				 guchar r, guchar g, guchar b);
*	/* Copy an area of a pixbuf onto another one */
*	void gdk_pixbuf_copy_area (const GdkPixbuf *src_pixbuf,
*			   int src_x, int src_y,
*			   int width, int height,
*			   GdkPixbuf *dest_pixbuf,
*			   int dest_x, int dest_y);

#if render-to-drawable.py:
*	/* Rendering to a drawable */
*	/* Alpha compositing mode */
*	typedef enum {
*		GDK_PIXBUF_ALPHA_BILEVEL,
*		GDK_PIXBUF_ALPHA_FULL
*	} GdkPixbufAlphaMode;

#if render-threshold-alpha.py:
*# were do I get a bitmap in pygtk to test this?
*	void gdk_pixbuf_render_threshold_alpha (GdkPixbuf *pixbuf, 
*					GdkBitmap *bitmap,
*					int src_x, int src_y,
*					int dest_x, int dest_y,
*					int width, int height,
*					int alpha_threshold);

#if render-to-drawable.py:
*	void gdk_pixbuf_render_to_drawable (GdkPixbuf *pixbuf,
*				    GdkDrawable *drawable, GdkGC *gc,
*				    int src_x, int src_y,
*				    int dest_x, int dest_y,
*				    int width, int height,
*				    GdkRgbDither dither,
*				    int x_dither, int y_dither);
*
*	void gdk_pixbuf_render_to_drawable_alpha (GdkPixbuf *pixbuf, 
*					  GdkDrawable *drawable,
*					  int src_x, int src_y,
*					  int dest_x, int dest_y,
*					  int width, int height,
*					  GdkPixbufAlphaMode alpha_mode,
*					  int alpha_threshold,
*					  GdkRgbDither dither,
*					  int x_dither, int y_dither);
*

#if render-pixmap-and-mask.py:
*	void gdk_pixbuf_render_pixmap_and_mask (GdkPixbuf *pixbuf,
*					GdkPixmap **pixmap_return, 
*					GdkBitmap **mask_return,
*					int alpha_threshold);

#if from-drawable.py:
*	/* Fetching a region from a drawable */
*	GdkPixbuf *gdk_pixbuf_get_from_drawable (GdkPixbuf *dest,
*					 GdkDrawable *src, GdkColormap *cmap,
*					 int src_x, int src_y,
*					 int dest_x, int dest_y,
*					 int width, int height);

#if scale-composite.py:
*	/* Scaling */
*	/* Interpolation modes */
*	typedef enum {
*		GDK_INTERP_NEAREST,
*		GDK_INTERP_TILES,
*		GDK_INTERP_BILINEAR,
*		GDK_INTERP_HYPER
*	} GdkInterpType;
*	void gdk_pixbuf_scale           (const GdkPixbuf *src,
*				 GdkPixbuf       *dest,
*				 int              dest_x,
*				 int              dest_y,
*				 int              dest_width,
*				 int              dest_height,
*				 double           offset_x,
*				 double           offset_y,
*				 double           scale_x,
*				 double           scale_y,
*				 GdkInterpType    interp_type);
*	void gdk_pixbuf_composite       (const GdkPixbuf *src,
*				 GdkPixbuf       *dest,
*				 int              dest_x,
*				 int              dest_y,
*				 int              dest_width,
*				 int              dest_height,
*				 double           offset_x,
*				 double           offset_y,
*				 double           scale_x,
*				 double           scale_y,
*				 GdkInterpType    interp_type,
*				 int              overall_alpha);
*	void gdk_pixbuf_composite_color (const GdkPixbuf *src,
*				 GdkPixbuf       *dest,
*				 int              dest_x,
*				 int              dest_y,
*				 int              dest_width,
*				 int              dest_height,
*				 double           offset_x,
*				 double           offset_y,
*				 double           scale_x,
*				 double           scale_y,
*				 GdkInterpType    interp_type,
*				 int              overall_alpha,
*				 int              check_x,
*				 int              check_y,
*				 int              check_size,
*				 guint32          color1,
*				 guint32          color2);

#if simple-scale-composite.py:
*	GdkPixbuf *gdk_pixbuf_scale_simple           (const GdkPixbuf *src,
*					      int              dest_width,
*					      int              dest_height,
*					      GdkInterpType    interp_type);
*	GdkPixbuf *gdk_pixbuf_composite_color_simple (const GdkPixbuf *src,
*					      int              dest_width,
*					      int              dest_height,
*					      GdkInterpType    interp_type,
*					      int              overall_alpha,
*					      int              check_size,
*					      guint32          color1,
*					      guint32          color2);

#if anim.py:
*	/* Animation support */
*	/* GIF-like animation overlay modes for frames */
*	typedef enum {
*		GDK_PIXBUF_FRAME_RETAIN,
*		GDK_PIXBUF_FRAME_DISPOSE,
*		GDK_PIXBUF_FRAME_REVERT
*	} GdkPixbufFrameAction;
*	GdkPixbufAnimation *gdk_pixbuf_animation_new_from_file   (
*					const char         *filename);
*	GdkPixbufAnimation *gdk_pixbuf_animation_ref (
*					GdkPixbufAnimation *animation);
*	void   gdk_pixbuf_animation_unref    (GdkPixbufAnimation *animation);
*	int  gdk_pixbuf_animation_get_width   (GdkPixbufAnimation *animation);
*	int  gdk_pixbuf_animation_get_height  (GdkPixbufAnimation *animation);
*	GList  *gdk_pixbuf_animation_get_frames (GdkPixbufAnimation *animation);
*	int gdk_pixbuf_animation_get_num_frames (GdkPixbufAnimation *animation);
*	/* Frame accessors */
*	GdkPixbuf    *gdk_pixbuf_frame_get_pixbuf     (GdkPixbufFrame *frame);
*	int         gdk_pixbuf_frame_get_x_offset   (GdkPixbufFrame *frame);
*	int         gdk_pixbuf_frame_get_y_offset   (GdkPixbufFrame *frame);
*	int         gdk_pixbuf_frame_get_delay_time (GdkPixbufFrame *frame);
*	GdkPixbufFrameAction gdk_pixbuf_frame_get_action  (
*					GdkPixbufFrame *frame);


	/* General (presently empty) initialization hooks, 
		primarily for gnome-libs */
	void gdk_pixbuf_preinit  (gpointer app, gpointer modinfo);
	void gdk_pixbuf_postinit (gpointer app, gpointer modinfo);

