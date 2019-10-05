/* header file for activity module
 * an activity has a name, number of hours it will take, priority, and whether it's active or finished
 */

#ifndef __ACTIVITY_H
#define __ACTIVITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct activity activity_t;

//initializes a new activity with the given parameters
activity_t *activity_new(char*name, int numHours, int urg, int impt);

//returns the elements of the struct
char*getName(activity_t *activity);
int getPriority(activity_t *activity);
int getNumHours(activity_t *activity);
bool isDone(activity_t *activity);

//modifies the elements of the struct
void work(activity_t *activity, int hours);
void changeNumHours(activity_t *activity, int newNumHours);
void finish(activity_t *activity);
void activity_delete(activity_t *activity);

//see if an activity has higher priority than another
bool actIsMoreImpt(activity_t *a1, activity_t  *a2);
void printActivity(activity_t *activity, FILE *fp);
char* activityToString(activity_t *activity, FILE *fp);
char* shortActivityToString(activity_t *activity,  FILE *fp);

#endif // __ACTIVITY_H