struct TimeSorter {
	int index;
	signed int difference;
	struct tm remindAt;
};

int __struct_diff_sorter(const void *a, const void *b);

struct TimeSorter * sort_times();
