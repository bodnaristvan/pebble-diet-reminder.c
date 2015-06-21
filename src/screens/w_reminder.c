#include <pebble.h>
#include "w_main.h"
#include "meals.h"
#include "datecalc.h"

static TextLayer *s_reminder_title_layer;
static TextLayer *s_reminder_nextcal_layer;
static TextLayer *s_reminder_calorie_layer;

int meal_index;

void reminder_window_load(Window *window) {
	light_enable_interaction();
	vibes_double_pulse();
	
	s_reminder_title_layer = text_layer_create(GRect(0, 0, 144, 35));
	text_layer_set_text_color(s_reminder_title_layer, GColorWhite);
	text_layer_set_background_color(s_reminder_title_layer, GColorBlack);
	text_layer_set_text(s_reminder_title_layer, "Diet reminder");
	text_layer_set_font(s_reminder_title_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(s_reminder_title_layer, GTextAlignmentCenter);
	
	static char nxtstr[300];
	snprintf(nxtstr, sizeof(nxtstr), "%s", meals[meal_index].label);
	s_reminder_nextcal_layer = text_layer_create(GRect(5, 40, 139, 30));
	text_layer_set_background_color(s_reminder_nextcal_layer, GColorClear);
	text_layer_set_overflow_mode(s_reminder_nextcal_layer, GTextOverflowModeWordWrap);
	text_layer_set_text_color(s_reminder_nextcal_layer, GColorBlack);
	text_layer_set_text(s_reminder_nextcal_layer, nxtstr);
	text_layer_set_font(s_reminder_nextcal_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_text_alignment(s_reminder_nextcal_layer, GTextAlignmentCenter);
	
	static char calstr[100];
	snprintf(calstr, sizeof(calstr), "%dkcal", (int)((meals[meal_index].percentage * get_daily_allowed_calories())+0.5));
	s_reminder_calorie_layer = text_layer_create(GRect(0, 70, 144, 60));
	text_layer_set_background_color(s_reminder_calorie_layer, GColorClear);
	text_layer_set_overflow_mode(s_reminder_calorie_layer, GTextOverflowModeWordWrap);
	text_layer_set_text_color(s_reminder_calorie_layer, GColorBlack);
	text_layer_set_text(s_reminder_calorie_layer, calstr);
	text_layer_set_font(s_reminder_calorie_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
	text_layer_set_text_alignment(s_reminder_calorie_layer, GTextAlignmentCenter);
	

	// Add it as a child layer to the Window's root layer
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_reminder_title_layer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_reminder_calorie_layer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_reminder_nextcal_layer));
}

void reminder_window_unload(Window *window) {
	// Destroy TextLayer
	text_layer_destroy(s_reminder_title_layer);
	text_layer_destroy(s_reminder_calorie_layer);
	text_layer_destroy(s_reminder_nextcal_layer);
}

Window* create_reminder_window(int reminder_index) {
	static Window *s_main_window;
	s_main_window = window_create();
	meal_index = reminder_index;
	window_set_window_handlers(s_main_window, (WindowHandlers){
		.load = reminder_window_load,
		.unload = reminder_window_unload,
	});
	return s_main_window;
}