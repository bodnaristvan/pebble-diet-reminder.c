// Meals contain time in day, a label, and the percentage of the total daily intake.
typedef struct {
	int hour;
	int minute;
	char label[30];
	float percentage;
} Meal;
// List of meals configured for reminders.
extern Meal meals[];


/* Storage of the total daily calorie intake. */

// Default intake, that can be overridden via settings.
#define DEFAULT_DAILY_CALORIES 2000
// Persistent key for intake setting
enum {
  PERSIST_CALORIES
};
// Convenience method for getting the daily intake value from 
// the persistent storage, or returning the default if that does not exist.
int get_daily_allowed_calories();