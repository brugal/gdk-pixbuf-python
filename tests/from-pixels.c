#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdio.h>

static void show_pixbuf (GdkPixbuf *pixbuf, gchar *title)
{
	GtkWidget *win, *pixmap;
	GdkPixmap *gdkpixmap;
	GdkBitmap *gdkbitmap;

	win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(win), title);
	
	gdk_pixbuf_render_pixmap_and_mask (pixbuf, &gdkpixmap,
					&gdkbitmap, GDK_PIXBUF_ALPHA_FULL);
	pixmap = gtk_pixmap_new (gdkpixmap, gdkbitmap);

	gtk_widget_set_usize (win, gdk_pixbuf_get_width(pixbuf),
			gdk_pixbuf_get_height(pixbuf));

	gtk_container_add (GTK_CONTAINER (win), pixmap);
	gtk_widget_show_all (win);
}

int main (int argc, char *argv[])
{
	GdkPixbuf *pixbuf, *pixbuf2;
	FILE *fp;

	gtk_init (&argc, &argv);

	if (argc != 2)
	{	g_print ("usage: %s <image file>\n", argv[0]);
		exit (1);
	}

	pixbuf = gdk_pixbuf_new_from_file (argv[1]);
	show_pixbuf (pixbuf, "pixbuf from file");

	fp = fopen ("c.pixels", "w");
	fwrite (gdk_pixbuf_get_pixels(pixbuf), sizeof(guchar),
		gdk_pixbuf_get_height(pixbuf) * 
		gdk_pixbuf_get_rowstride(pixbuf), fp);
	fclose (fp);

	pixbuf2 = gdk_pixbuf_new_from_data (
			gdk_pixbuf_get_pixels(pixbuf),
			gdk_pixbuf_get_colorspace(pixbuf),
			gdk_pixbuf_get_has_alpha(pixbuf),
			gdk_pixbuf_get_bits_per_sample(pixbuf),
			gdk_pixbuf_get_width(pixbuf),
			gdk_pixbuf_get_height(pixbuf),
			gdk_pixbuf_get_rowstride(pixbuf),
			NULL, NULL);
	show_pixbuf (pixbuf2, "pixbuf from pixels");

	gtk_main ();
	return 0;
}
			

	
