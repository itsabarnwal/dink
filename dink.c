/* main module for project
 * input: activities, number of available hours in this day
 * output: schedule
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "activity.h"
#include "day.h"

int main(const int argc, const char* argv[])
{
	day_t *day_test = newDay(10);

	// activity_t *act_test1 = addActivity(day_test, "test1", 3, 4,2); //8
	// activity_t *act_test2 = activity_new("test2", 2, 3,3); //9
	// activity_t *act_test3 = activity_new("test3", 1, 2,2); //4
	// activity_t *act_test4 = activity_new("test4", 1, 3,2); //6

	// activity_delete(act_test2);
	// activity_delete(act_test3);
	// activity_delete(act_test4);

	addActivity(day_test, "gym", 1, 3, 8);
	addActivity(day_test, "calendars", 1, 4,6);
	addActivity(day_test, "applications", 1, 2,5);
	addActivity(day_test, "networking", 1, 3,5);

	printDay(day_test, stdout);

	// THE FOLLOWING COMMENTS ARE ALL FUNCTIONAL COMMANDS THAT HAVE BEEN TESTED
	// fprintf(stdout, "ACT  TO  STRING\n");	
	// printf("%s", activityToString(act_test1, stdout));

	// fprintf(stdout, "SHORTACT  TO  STRING\n");	
	// printf("%s", shortActivityToString(act_test1, stdout));


	// fprintf(stdout, "NOW TESTING ADVANCED AND ALGORITHMIC FUNCTIONS\n");

	// int ind = getRankingBinarySearch(day_test, act_test1);
	// printf("testing getIndexByName\ntest1 has index: %d\n", ind);

	// removeActivity(day_test, ind);
	// printf("testing removeActivity\n");
	// printDay(day_test, stdout);

	// printf("testing getRandActivity\n");

	// printActivity(getRandActivity(day_test,0,2), stdout);

	// printf("testing getQuickest\n");
	// printActivity(getQuickestTask(day_test), stdout);

	getSchedule(day_test, stdout);

	day_delete(day_test);
}