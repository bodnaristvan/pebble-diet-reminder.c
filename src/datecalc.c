#include <stdio.h>
#include <stdlib.h>
#include <pebble.h>
#include "meals.h"
#include "datecalc.h"

int __struct_diff_sorter(const void *a, const void *b) { 
    struct TimeSorter *ia = (struct TimeSorter *)a;
    struct TimeSorter *ib = (struct TimeSorter *)b;
    return (int)(ia->difference - ib->difference);
}

struct TimeSorter * sort_times() {
	static struct TimeSorter sortedTime[5];
	struct tm current_time;
	struct TimeSorter *ts;
	signed int diff;

	for (int x = 0; x < 5; x++) {
		current_time = *localtime(&(time_t){time(NULL)});
		current_time.tm_hour = meals[x].hour;
		current_time.tm_min = meals[x].minute;
		current_time.tm_sec = 0;
		
		diff = mktime(&current_time) - (time(NULL) + 1);
		if (diff < 0) {
			current_time.tm_mday = current_time.tm_mday + 1;
			diff = mktime(&current_time) - (time(NULL) + 1);
		}
		
		ts = &sortedTime[x];
		ts->index = x;
		ts->difference = diff;
		ts->remindAt = current_time;
	}
	
	size_t structs_len = sizeof(sortedTime) / sizeof(struct TimeSorter);
	qsort(sortedTime, structs_len, sizeof(struct TimeSorter), __struct_diff_sorter);

	return sortedTime;
}
