/* day.c  is the day module
 * it holds a binary search tree of activities ranked in order of importance
 * it also contains a getSchedule method that outputs to a file a schedule based on the given activities
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "day.h"
#include "activity.h"

/*typedef struct activityNode {
	act_node *next;
	activity_t *activity;
}act_node;*/

typedef struct day{
	int numActivities;
	int numHours; //number of hours you have in this day

	//WHAT WE WANT: a sorted, dynamically allocatable list that is easy to traverse
	//if we simply use an array and allocate more memory than necessary,
	//it is both easy to traverse and technically dynamically allocatable

	activity_t **activities; 

	//this functions as a priority queue that stores the most important tasks at the top of the array
	
}day_t;


day_t *newDay(int numHours)
{
	//initialize everything and malloc
	if(numHours<=0) return NULL;
	day_t *day = malloc(sizeof(day));
	day->activities = malloc(sizeof(activity_t *) * 1000); //we keep 1000 null activities
	day->numHours = numHours;
	day->numActivities = 0;
	return day;
}

//add an activity to the day
void addActivity(day_t *day, char*name, int numHours, int urg, int impt)
{
	//we use the activity object
	activity_t *activity = activity_new(name, numHours, urg, impt);
	if(day==NULL || activity==NULL) return;
	//make sure two activities  don't have the same name
	for(int i=0; i<day->numActivities; i++)
	{
		if(strcmp(getName(activity), getName(day->activities[i]))==0) 
			fprintf(stderr, "activities must have different names");
		if(numHours + day->numHours > 24)
			fprintf(stderr, "activity hours must be less than equal to 24");
	}



	//traverse the priority queue and find the slot it should be in
	for(int i=0; i<day->numActivities; i++)
	{
		printf("%d, %d\n", getPriority(activity), getPriority(day->activities[i]));
		if(actIsMoreImpt(activity, day->activities[i])) //if more important than what's at the given slot
		{
			//move others back
			for(int j = day->numActivities; j>i ; j--)
			{
				day->activities[j] = day->activities[j-1];
			}
			//and insert it there
			day->activities[i] = activity;
			day->numActivities++; //now that it's inserted we increment the counter and exit
			return; 
		}
	}

	//if it got here, it has the lowest priority, so put it at the end and increment the counter
	day->activities[day->numActivities] = activity; 
	day->numActivities++;
}

//modify the activity
void modifyActivity(day_t *day, int index, void*var,void(*itemfunc)(activity_t *activity, void*var))
{
	if(day==NULL || itemfunc==NULL) return;

	itemfunc(day->activities[index], var);
}

//free memory and delete
void day_delete(day_t *day)
{
	if(day==NULL) return;

	for(int i=0; i<day->numActivities-1; i++)
	{
		activity_delete(day->activities[i]);
	}
	free(day);
}

//remove an activity at an index
static activity_t *removeActivity(day_t *day, int index)
{
	//TODO: figure out how to free
	if(day==NULL || index < 0 || index >= day->numActivities) return NULL;
	activity_t *removed = day->activities[index];
	for(int i = index; i<day->numActivities; i++)
	{
		day->activities[i]=day->activities[i+1];
	}

	day->numActivities--;
	return removed;
}

//returns a random activity with a specified bounds of importance
activity_t *getRandActivity(day_t *day, int ibound1, int ibound2)
{
	ibound2+=1; //to make it inclusive [x,y] instead of [x,y)
	if(day==NULL) return NULL;
	if(ibound1 >= ibound2 || ibound1<0) ibound1=0;
	if(ibound2 > day->numActivities) ibound2 = day->numActivities;
	srand ( time(NULL) ); //necessary to seed rand
	int i = ibound1 + rand() % (ibound2-ibound1);
	return day->activities[i];
}

//takes in a day's worth of schedules and writes a schedule to a file 

activity_t *getMostImptTask(day_t *day)
{
	if(day==NULL){
		return NULL;
		printf("\nwe  are here\n");
	} 
	return removeActivity(day, 0);
}

//returns the  hardest task with an activity length less than the given double
static activity_t *getHardestTaskOfLengthLess(day_t *day, double length)
{
	if(day==NULL) return NULL;
	for(int i=0; i<day->numActivities; i++)
	{
		activity_t *activity = day->activities[i];
		if(getNumHours(activity)<=length) 
		{
			//because we store everything in descending order of difficulty
			//we return the first activity that is less than the given length
			return removeActivity(day, i); 
		}
	}
	return NULL; //no matching activity
}

//returns number of hours for most difficulty task
static int getFirstActHours(day_t *day)
{
	return getNumHours(day->activities[0]);
}

//returns quickest task
activity_t *getQuickestTask(day_t *day)
{
	if(day==NULL || day->activities[0]==NULL) return NULL; 
	int lowest = getPriority(day->activities[0]); //initialize to priority of first activity
	int index = 0;
	for(int i=0; i<day->numActivities; i++)
	{
		int currHours = getNumHours(day->activities[i]);
		if(currHours<lowest) 
		{
			lowest = currHours;
			index = i;
		}
	}

	return removeActivity(day, index);
}

//returns the number of activities
int getNumActivities(day_t *day){return (day==NULL) ? 0 : day->numActivities;}

//output a record of the day to the given file
void printDay(day_t *day, FILE *fp)
{
	if(day==NULL || fp==NULL) return;
	for(int i=0; i<day->numActivities; i++)
	{
		if(day->activities[i]!=NULL) printActivity(day->activities[i],fp);
	}
}

//uses a binary search to find the index of an activity
static int getRankingBinarySearch(day_t *day, activity_t *activity)
{
	if(day==NULL || activity==NULL) return -1;
	int p = getPriority(activity); 
    int L = 0;
    int R = day->numActivities-1;

    //keep narrowing down the field
    //until there's a match
    while (L <= R)
    { 
    	int m = (L + R)/2;
        if (getPriority(day->activities[m]) < p)
			L = m+1;
        else if (getPriority(day->activities[m]) > p)
            R = m-1;
        else return m;
    }
    return -1;
}

//find the index of an activity with given name
static int getRankingByName(day_t *day, char *activityName)
{
	if(day==NULL || activityName==NULL) return -1;
	for(int i = 0; i<day->numActivities; i++)
	{
		if(strcmp(activityName, getName(day->activities[i]))==0) return i;
	}
	return -1;
}

//get the ranking by linear search
static int getRanking(day_t *day, activity_t *activity)
{
	if(day==NULL || activity==NULL) return -1;
	for(int i = 0; i<day->numActivities; i++)
	{
		if(strcmp(getName(activity), getName(day->activities[i]))==0) return i;
	}
	return -1;
}

//this is the algo work
void getSchedule(day_t *day, FILE *fp)
{
	if(day==NULL || fp==NULL) return;

	int numHoursLeft = day->numHours;


	activity_t *activity = getHardestTaskOfLengthLess(day, 1);
	fprintf(fp, "%s", shortActivityToString(activity,fp));
	numHoursLeft-=getNumHours(activity);

	activity = getMostImptTask(day);
	fprintf(fp, "%s", shortActivityToString(activity,fp));
	numHoursLeft-=getNumHours(activity);	


	int imptHrs = getNumHours(day->activities[0]);
	activity=getQuickestTask(day);

	int qHrs=getNumHours(activity);
	int counter = 1; 

	while(numHoursLeft >= imptHrs + qHrs && day->numActivities>0)
	{
		//if we're on the first iteration don't update activity, otherwise update it
		if(counter==1) counter=2;
		else activity=getQuickestTask(day);
		fprintf(fp, "%s", shortActivityToString(activity,fp));
		numHoursLeft-=getNumHours(activity);
		qHrs=getNumHours(activity);
	}	

	while(day->numActivities>0)
	{
		activity = getMostImptTask(day);
		fprintf(fp, "%s", shortActivityToString(activity,fp));
		numHoursLeft-=getNumHours(activity);	
	}


	// while(numHoursLeft>0 && day->numActivities >= 0)
	// {
	// 	activity=getQuickestTask(day);
	// 	fprintf(fp, "%s", shortActivityToString(activity,fp));
	// 	numHoursLeft-=getNumHours(activity);
	// }


	//first one is the hardest task that will take 1 hour or less
	//second one is the hardest task
	//third one is 2 hours of small tasks
	//fourth one is the next hardest
	//with whatever time is left, do the lowest priority shit
}