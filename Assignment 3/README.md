## Little Log File System
### Katherine Jacobs V00783178

Please see report.txt for a description of the design and implementation of my file system.

#### How to Run my File System
I have a shell script that compiles all the necessary files and runs all of my tests. The command ./runLLFS.sh in the top level folder that contains the script should be all you need to run my file system :)


#### Resources Used:
- Lecture slides and videos from the course.
- Code implemented closely based off of Tutorial 10 Part 1 - Free Block Vector and Bitwise Operators.
- Doubly linked list code from assignment #1, slightly modified.
I used the resource below for calculating int to hex for file size:
- https://stackoverflow.com/questions/3784263/converting-an-int-into-a-4-byte-char-array-c

I used the resource below to find the size of a given file 
- https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c

I slightly modified and used some of the following functions from my shell assignment:
- char **split_line(char* line);
- void execute_command(char **args);

My functions readBlock() and writeBlock() in disk.c were taken from tutorial.
