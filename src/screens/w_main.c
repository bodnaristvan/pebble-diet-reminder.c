#include <pebble.h>
#include "w_main.h"
#include "meals.h"
#include "datecalc.h"
#include "screens/w_settings.h"

static TextLayer *s_title_layer;
static TextLayer *s_totalcal_layer;
static TextLayer *s_nextcal_layer;
static TextLayer *s_totalcallabel_layer;
static TextLayer *s_configlabel_layer;
static NumberWindow *s_settings_window;

static void settings_click_handler(ClickRecognizerRef recognizer, void *context) {
	s_settings_window = create_settings_window();
	window_stack_push((Window *)s_settings_window, true);
}

void click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) settings_click_handler);
}

void main_window_load(Window *window) {
	s_title_layer = text_layer_create(GRect(0, 0, 144, 35));
	text_layer_set_text_color(s_title_layer, GColorWhite);
	text_layer_set_background_color(s_title_layer, GColorBlack);
	text_layer_set_text(s_title_layer, "Diet reminder");
	text_layer_set_font(s_title_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(s_title_layer, GTextAlignmentCenter);
	
	s_totalcallabel_layer = text_layer_create(GRect(0, 40, 144, 20));
	text_layer_set_text(s_totalcallabel_layer, "Total calories:");
	text_layer_set_font(s_totalcallabel_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
	text_layer_set_text_alignment(s_totalcallabel_layer, GTextAlignmentCenter);
	
	static char calstrtemp[300];
	snprintf(calstrtemp, sizeof(calstrtemp), "%dkcal", persist_exists(PERSIST_CALORIES) ? (int)persist_read_int(PERSIST_CALORIES) : 2000);
	s_totalcal_layer = text_layer_create(GRect(0, 60, 144, 28));
	text_layer_set_text(s_totalcal_layer, calstrtemp);
	text_layer_set_font(s_totalcal_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(s_totalcal_layer, GTextAlignmentCenter);
	
	s_configlabel_layer = text_layer_create(GRect(5, 88, 139, 17));
	text_layer_set_text(s_configlabel_layer, "(press select to change)");
	text_layer_set_font(s_configlabel_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	text_layer_set_text_alignment(s_configlabel_layer, GTextAlignmentCenter);


	struct TimeSorter *st = sort_times();
	struct TimeSorter firstItem = st[0];
	struct tm firstTime = firstItem.remindAt;
	
	static char nxtstr[300];
	snprintf(nxtstr, sizeof(nxtstr), "Next meal is %s, at %02d:%02d.", meals[firstItem.index].label, firstTime.tm_hour, firstTime.tm_min);
	s_nextcal_layer = text_layer_create(GRect(5, 110, 139, 50));
	text_layer_set_text(s_nextcal_layer, nxtstr);
	text_layer_set_font(s_nextcal_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
	

	// Add it as a child layer to the Window's root layer
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_title_layer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_totalcallabel_layer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_totalcal_layer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_configlabel_layer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_nextcal_layer));
}

void main_window_unload(Window *window) {
	// Destroy TextLayer
	text_layer_destroy(s_title_layer);
	text_layer_destroy(s_totalcallabel_layer);
	text_layer_destroy(s_totalcal_layer);
	text_layer_destroy(s_configlabel_layer);
	text_layer_destroy(s_nextcal_layer);
	
	if (s_settings_window && window_is_loaded((Window *)s_settings_window)) {
		number_window_destroy(s_settings_window);
	}
}


Window* create_main_window() {
	static Window *s_main_window;
	s_main_window = window_create();
	window_set_window_handlers(s_main_window, (WindowHandlers){
		.load = main_window_load,
		.unload = main_window_unload,
	});
	window_set_click_config_provider(s_main_window, (ClickConfigProvider) click_config_provider);

	return s_main_window;
}