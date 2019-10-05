/* activity module
 * a struct that stores all the attributes of an activity
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "activity.h"

typedef struct activity{
    char* name;
    int numHoursLeft;
    int priority; //made up of urgency and importance
    bool isDone;
} activity_t;

//initializes a new activity with the given parameters
activity_t *activity_new(char*name, int numHours, int urg, int impt){
    activity_t *activity = malloc(sizeof(activity));
    activity->name=name;activity->numHoursLeft=numHours;
    activity->isDone=false;
    activity->priority = urg * impt;
    return activity;
}

//returns the elements of the struct
char*getName(activity_t *activity){return (activity==NULL) ? NULL : activity->name;}
int getPriority(activity_t *activity){return (activity==NULL) ? 0 : activity->priority;}
int getNumHours(activity_t *activity){return (activity==NULL) ? 0 : activity->numHoursLeft;}
bool isDone(activity_t *activity){return (activity==NULL) ? false : activity->isDone;}

//after working on the activity we change the number of hours left
void work(activity_t *activity, int hours){
    if(activity!=NULL) activity->numHoursLeft -= hours;
}

//if the activity takes more or less time than we thought, we modify the number of hours 
void changeNumHours(activity_t *activity, int newNumHours){
    if(activity!=NULL) activity->numHoursLeft = newNumHours;
}

//finish the activity
void finish(activity_t *activity){
    if(activity==NULL) return;
    activity->numHoursLeft = 0;
    activity->isDone = true;
}

//free memory
void activity_delete(activity_t *activity)
{
    if(activity==NULL) return;
    free(activity);
}

//
bool actIsMoreImpt(activity_t *a1, activity_t  *a2)
{
    if(a1==NULL || a2 == NULL) return false;
    return (a1->priority > a2->priority);
}

void printActivity(activity_t *activity, FILE *fp)
{
    if(activity==NULL || fp==NULL) return;
    fprintf(fp, "activity name: \t%s\nnumHours: \t%d\npriority: \t%d\n",
        activity->name, activity->numHoursLeft,activity->priority);
}

char* activityToString(activity_t *activity, FILE *fp)
{
    if(activity==NULL || fp==NULL) return NULL;
    char *s1, *s2, *s3, *s4;
    char *sfinal;
    s1="activity name: \t";
    s2= activity->name;
    s3="\nnumHours: \t";
    s4="\npriority: \t";
    sfinal = malloc(strlen(s1) + strlen(s2) + + strlen(s3) + strlen(s4) + 5);
    sprintf(sfinal, "%s%s%s%d%s%d\n", s1, s2, s3, activity->numHoursLeft, s4, activity->priority);
    // sprintf(actString, "activity name: \t%s\nnumHours: \t%d\npriority: \t%d\n", activity->name, activity->numHoursLeft,activity->priority);
    return sfinal;
}

char* shortActivityToString(activity_t *activity,  FILE *fp)
{
    if(activity==NULL || fp==NULL) return "invalid activity or file\n";
    char *s1, *sfinal;
    s1="h\t";
    sfinal = malloc(strlen(activity->name) + strlen(s1) + 3);
    sprintf(sfinal, "%d%s%s\n", activity->numHoursLeft, s1, activity->name);
    // sprintf(actString, "activity name: \t%s\nnumHours: \t%d\npriority: \t%d\n", activity->name, activity->numHoursLeft,activity->priority);
    return sfinal;

}
