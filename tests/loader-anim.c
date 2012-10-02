#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk-pixbuf/gdk-pixbuf-loader.h>
#include <stdio.h>

GdkPixbufLoader *loader;
FILE *fp;

#define BUFFER_SIZE (64)

static gboolean feed_loader (gpointer nada)
{
	char *data[BUFFER_SIZE];
	size_t nbytes;

	nbytes = fread (data, sizeof(char), BUFFER_SIZE, fp);
	if (nbytes <= 0)
	{	fclose (fp);
		gdk_pixbuf_loader_close (GDK_PIXBUF_LOADER (loader));
		return FALSE;
	}

	gdk_pixbuf_loader_write (GDK_PIXBUF_LOADER (loader),
				(guchar *) data, nbytes);
	return TRUE;
}

static gboolean frame_done_cb (GdkPixbufLoader *loader, GdkPixbufFrame *frame)
{
	GdkPixbuf *pixbuf;

	pixbuf = gdk_pixbuf_frame_get_pixbuf (frame);
	g_print ("frame_done_cb():  pixbuf (%p)\n", pixbuf);	
	return FALSE;
}

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	loader = gdk_pixbuf_loader_new ();
	gtk_signal_connect (GTK_OBJECT (loader), "frame_done",
			GTK_SIGNAL_FUNC (frame_done_cb), NULL);
	fp = fopen ("anim.gif", "r");
	gtk_timeout_add (500, feed_loader, NULL);
	gtk_main ();
	return 0;
}

	
