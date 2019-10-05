# IMPLEMENTATION

To use the day object, call `addActivity` and input the parameters, then to get the optimal schedule call the `getSchedule` method. 

# DESIGN
We created the activity struct to have parameters including name, the number of hours it takes to complete, urgency, and importance. day.c contains a priority queue of activities implemented as a dynamically allocatable array, and also keeps track of the number of activities in the array. 

We used an array instead of a linkedlist or binary search trees because it would allow for faster searches at a specific index of the priority queue. We need it to be resizable because we do not know how many activities the user wants to get done that day.

The priority queue is used over other structures like stacks because the best-out structure is optimal for this project. We want to get the most important task done first thing in the morning, so the most important task is stored at the top so we have the easiest access to it. 

To calculate importance, we compute priority * urgency. This draws from the Eisenhower Matrix (although we substitute the word priority for importance), which says that the most important task is one that is both of great priority and great urgency, and the least important is one of least priority and least urgency. I learned about the Eisenhower Matrix by studying psychology. 

## Methods
* `addActivity` creates a new activity in the priority queue of a day struct
* `modifyActivity` allows for modification of an activity (for instance, if we have worked on an activity we can decrease the number of hours left to finish it)
* `day_delete` deletes the day object and frees memory
* `printDay` prints the entire day's worth of activities in order of most important task to least important
* `getSchedule` outputs a schedule for the day based on the given activities.

## TODO // What I'm currently working on
I've tested the functions and they seem to be working decently well, so the next step is to utilize them with a user interface / front end so that a user can actually use them. I coded this in C because I just learned it from taking CS50 at Dartmouth, but I'm realizing that it may have been ideal to use JavaScript instead, because that is a classic front-end language. My JS experience is rather minimal, as I have little to show besides a small Chrome extension in high school, so it may take a few weeks before the application is up. However, this library is very usable!