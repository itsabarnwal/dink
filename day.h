/* day.h is the header file for the day module
 * contains a binary search tree of activities, sorted by importance
 */

#ifndef __DAY_H
#define __DAY_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "activity.h"

typedef struct day day_t;

//initialize a new day struct
day_t *newDay(int numHours);

//basically a priority queue
void addActivity(day_t *day, char*name, int numHours, int urg, int impt);

//pass function to modify the activity
void modifyActivity(day_t *day, int index, void*var,void(*itemfunc)(activity_t *activity, void*var));

//free memory and delete the struct
void day_delete(day_t *day);


//returns a random activity with a specified bounds of importance
activity_t *getRandActivity(day_t *day, int ibound1, int ibound2);

//return the number of activities
int getNumActivities(day_t *day);

void printDay(day_t *day, FILE* fp);

//takes in a day's worth of schedules and writes a schedule to a file 
void getSchedule(day_t *day, FILE* fp);

//return the most important task, at the top of the priority queue
activity_t *getMostImptTask(day_t *day);

//return the fastest task
activity_t *getQuickestTask(day_t *day);

#endif // __DAY_H