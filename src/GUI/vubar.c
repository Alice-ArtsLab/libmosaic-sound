#include "include/vubar.h"
#include <gtk/gtk.h>

struct vi_led_t{
   GtkWidget *widget;
   float value;
   GdkRGBA color;
};

void vi_led_free(struct vi_led_t *led){
   free(led);
}

static void vi_led_destroy(GtkWidget *widget, struct vi_led_t *led){
   vi_led_free(led);
}


static gboolean vi_led_draw(GtkWidget *widget, GdkEventConfigure *event, struct vi_led_t *led){
   GdkWindow *window;
   cairo_t *cr;

   int value = 100 - led->value * 100;

   gtk_widget_get_allocated_width(widget);
   gtk_widget_get_allocated_height(widget);

   window = gtk_widget_get_window(widget);
   cr = gdk_cairo_create(window);

   cairo_set_line_width(cr, 1);

   int i = 0;
   for(; i < 100 ; i++){
      if(i < value){
         if(i < 20)// red
            cairo_set_source_rgb(cr, 0.5, 0, 0);
         else if(i < 40) // yellow
            cairo_set_source_rgb(cr, 0.5, 0.5, 0);
         else // green
            cairo_set_source_rgb (cr, 0, 0.5, 0);
      }else{
         if(i < 20)// red
            cairo_set_source_rgb(cr, 0.9, 0, 0);
         else if(i < 40) // yellow
            cairo_set_source_rgb(cr, 0.9, 0.9, 0);
         else // green
            cairo_set_source_rgb (cr, 0, 0.9, 0);
      }

      cairo_rectangle (cr, 0, 0 + (3*i), 20, 1.7);
      cairo_fill_preserve(cr);
      cairo_stroke(cr);
   }

   cairo_set_source_rgb (cr, 0, 0, 0);
   cairo_move_to (cr, 22, 20);
   cairo_show_text (cr, "+8");
   cairo_move_to (cr, 22, 120);
   cairo_show_text (cr, " 0");
   cairo_move_to (cr, 22, 250);
   cairo_show_text (cr, "-20");
   cairo_stroke (cr);

   /* Finish */
   cairo_destroy(cr);
   return FALSE;
}


void vi_led_create(int radius, mscsound_vubar_t **vubar){
   struct vi_led_t *led;

   /* Allocate */
   led = malloc(sizeof(struct vi_led_t));

   /* Initialize */
   gdk_rgba_parse (&led->color, "green");

   /* Drawing box */
   GtkWidget *drawing_area = gtk_drawing_area_new();
   gtk_widget_set_size_request(drawing_area, 40, 300);
   g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(vi_led_draw), led);

   /* Main widget */
   led->widget = drawing_area;
   g_signal_connect(G_OBJECT(led->widget), "destroy", G_CALLBACK(vi_led_destroy), led);


   (*vubar)->vi_led = led;
}



void vi_led_set_color(struct vi_led_t *led, GdkRGBA *color)
{
   led->color = *color;
   vi_led_draw(led->widget, NULL, led);
}


GtkWidget *vi_led_get_widget(struct vi_led_t *led)
{
   return led->widget;
}


/* --------------------------------------------------------- */
mscsound_vubar_t *mscsound_create_vubar(int framesPerBuffer, void * widget) {
  mscsound_vubar_t *vubar = malloc(sizeof(mscsound_vubar_t));
  vubar->framesPerBuffer = framesPerBuffer;
  vubar->process = mscsound_vubar_process;
  vi_led_create(13, &vubar);

  gtk_box_pack_start(GTK_BOX((GtkWidget*)(widget)),
                     vi_led_get_widget(vubar->vi_led),
                     FALSE, TRUE, 20);

  return vubar;
}

void mscsound_vubar_process(mscsound_vubar_t **vubar){
   struct vi_led_t *led = (struct vi_led_t *) (*vubar)->vi_led;
   if (led->widget == NULL) return;

   for (int i = 0; i < (*vubar)->framesPerBuffer; i++) {
     led->value = (*((*vubar)->input0))[i];
     gtk_widget_queue_draw(led->widget);
   }
}
