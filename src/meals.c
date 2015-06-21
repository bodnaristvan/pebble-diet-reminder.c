#include <pebble.h>
#include "meals.h"

Meal meals[5] = {
	{8, 30, "breakfast", 0.25},
	{10, 30, "snack #1", 0.1},
	{12, 30, "lunch", 0.35},
	{16, 30, "snack #2", 0.1},
	{20, 00, "dinner", 0.2}
};

int get_daily_allowed_calories() {
	return persist_exists(PERSIST_CALORIES) ? (int)persist_read_int(PERSIST_CALORIES) : DEFAULT_DAILY_CALORIES;
}