#define TOTAL_CALORIES 2062

enum {
  PERSIST_CALORIES
};

typedef struct {
	int hour;
	int minute;
	char label[30];
	float percentage;
} Meal;

extern Meal meals[];

// int total_calories;