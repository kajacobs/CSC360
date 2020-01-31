# CSC 360 Programming Assignment #1: SEEsh
Katherine Jacobs

Resources Used:
- I used this website https://brennan.io/2015/01/16/write-a-shell-in-c/ from the lecture slides to implement
the following functions:
split_line();
get_input();
and the forking process in execute_command() was partially based of the tutorial as well

The following are some of the other websites I read to help implement parts of my code:
- https://www.geeksforgeeks.org/exec-family-of-functions-in-c/ for understanding how to implement execvp
- https://www.geeksforgeeks.org/fork-system-call/ for understanding fork()
- https://www.geeksforgeeks.org/wait-system-call-c/ for understanding wait()
- https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/ for understanding cd
- https://linux.die.net/man/3/getline - used for implementing reading in the rc file
- https://www.geeksforgeeks.org/signals-c-language/ - used for implementing a handler to catch ctrl-C

- A bug that I want to make you aware of is if the child process returns -1  at line 158 (passing an invalid argument) it then takes 2 ctrl-D's to exit SEEsh regardless of
how many other commands the shell is given. It does terminate after 2 though.
