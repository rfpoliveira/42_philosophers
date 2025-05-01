# 42_philosophers

About:
This project is meant to introduce ourselves to mutexes and threads with the classical problem of the dinning philosophers.

These philosophers can be eating, thinking and sleeping. To eat, they need two forks. If a philosopher doesn't start eating within a specified time, they will die. The program takes some command-line arguments: the number of philosophers, some times to limit the time they have to their actions, and an optional one on how many times each philosopher will eat. 
The program must display the philosophers activities with timestamps and end if someone dies or everyone reaches the optional limit.


Usage:
Clone
cd philo
make
to run:
$ ./philo [n of philos] [time to die] [time to eat] [time to sleep] [n times each philo must eat]
