#include "pebble.h"

#include "hands.h"
	
static Window *window;

static BitmapLayer *image_layer;
static Layer *layer;

static GBitmap *image;

static GPath *minute_hand;
static GPath *second_hand;
static GPath *tick_paths[NUM_CLOCK_TICKS];
Layer *hands_layer;

static void layer_update_callback(Layer *me, GContext* ctx) {
  // We make sure the dimensions of the GRect to draw into
  // are equal to the size of the bitmap--otherwise the image
  // will automatically tile. Which might be what *you* want.

  GRect bounds = image->bounds;

  graphics_draw_bitmap_in_rect(ctx, image, (GRect) { .origin = { 0, 12 }, .size = bounds.size });
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed){
	
	
}


int main(void) {
    window = window_create();
    window_stack_push(window, true /* Animated */);

  // Init the layer for display the image
    Layer *window_layer = window_get_root_layer(window);
	window_set_background_color(window, GColorBlack);
  GRect bounds = layer_get_frame(window_layer);
  layer = layer_create(bounds);
  layer_set_update_proc(layer, layer_update_callback);
  layer_add_child(window_layer, layer);

  image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_FLAME);

	tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler);
	
  app_event_loop();

  gbitmap_destroy(image);

    tick_timer_service_unsubscribe();	
    window_destroy(window);
    layer_destroy(layer);
}
