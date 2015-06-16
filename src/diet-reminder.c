#include <pebble.h>

#include <stdio.h>

#include "meals.h"
#include "datecalc.h"
#include "screens/w_main.h"
#include "screens/w_reminder.h"

static Window *s_main_window, *s_reminder_window;

Meal meals[5] = {
	{8, 30, "breakfast", 0.25},
	{10, 30, "snack #1", 0.1},
	{12, 30, "lunch", 0.35},
	{16, 30, "snack #2", 0.1},
	{20, 00, "dinner", 0.2}
};

static void register_next_wakeup() {
	struct TimeSorter *st = sort_times();
	wakeup_cancel_all();
	wakeup_schedule(mktime(&st[0].remindAt), st[0].index, true);
}

static void wakeup_handler(WakeupId id, int32_t reason) {
	s_reminder_window = create_reminder_window((int)reason);
	register_next_wakeup();
	window_stack_push(s_reminder_window, false);
}

static void init(void) {
	// Check to see if we were launched by a wakeup event
	if (launch_reason() == APP_LAUNCH_WAKEUP) {
		// app wakeup
		WakeupId id = 0;
		int32_t reason = 0;
		wakeup_get_launch_event(&id, &reason);

		s_reminder_window = create_reminder_window((int)reason);
		window_stack_push(s_reminder_window, false);
	} else {
		s_main_window = create_main_window();
		window_stack_push(s_main_window, false);
	}
	register_next_wakeup();
	
	// subscribe to wakeup service to get wakeup events while app is running
	wakeup_service_subscribe(wakeup_handler);
}

static void deinit(void) {
	if (s_main_window && window_is_loaded(s_main_window)) {
		window_destroy(s_main_window);
	}
	if (s_reminder_window && window_is_loaded(s_reminder_window)) {
		window_destroy(s_reminder_window);
	}
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}