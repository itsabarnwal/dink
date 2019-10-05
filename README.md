# DINK productivity app

This app is a solo side project I'm currently working on. The goal of the app is to have the user input various activities with varying priorities and lengths, and output an optimal work schedule for the user to follow throughout the day.  

Currently, I've finished the data structures necessary to implement the activity, and the algorithm that prints out the schedule. I have a working prototype that is usable with bash by compiling each of the .c files and running an executable. 

Along with tweaking the algorithm and debugging the code, I am now focusing on coding a front-end for the app. 

## Overview

I'm a psych student as well a CS student, so I thought it would be cool to use what I learned about learning and workflow in psychology to code this application. The literature is not 100% conclusive, but overall suggests that it is generally good to start with a small, less time-consuming task to put the brain into a state of work (as opposed to not being able to focus on any task), and knock out the most important task for the day, and alternate between easy and difficult work to avoid burnout. We never string together multiple difficult tasks to avoid burnout, take regular breaks, and force the user to be reasonable with their goals by imposing time constraints. 

Practically, this means we take in and store a string `name` and integers `numHours` and `priority` in each `activity`. For the `day` data structure, we use a priority queue of activities implemented as a dynamically allocatable array. We choose this data structure because it makes it easy to find the most important activity (because it is at the top of the array) and because it allows for an efficient binary search to find any given activity.