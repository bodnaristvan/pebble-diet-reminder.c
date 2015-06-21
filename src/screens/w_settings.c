#include <pebble.h>
#include "meals.h"
#include "w_settings.h"

void set_calories(struct NumberWindow *number_window, void *context) {
	persist_write_int(PERSIST_CALORIES, (int)number_window_get_value(number_window));
	window_stack_pop(true);
}

NumberWindow* create_settings_window() {
	static NumberWindow *s_settings_window;
	s_settings_window = number_window_create("Set calories", (NumberWindowCallbacks){
		.selected = set_calories
	}, NULL);
	number_window_set_min(s_settings_window, 100);
	number_window_set_max(s_settings_window, 10000);
	number_window_set_step_size(s_settings_window, 100);
	number_window_set_value(s_settings_window, persist_exists(PERSIST_CALORIES) ? (int)persist_read_int(PERSIST_CALORIES) : 2000);
	return s_settings_window;
}