# Data Parallelism 
## Katherine Jacobs V00783178

For this assignment I created 2 .c files. I started originally with datasingle.c, which is the single threaded version of this assignment. I felt it would be easier to start there, and then change it to be multithreaded. This also allowed me to use both files when analyzing the difference between multi and single threaded. 

I have created a shell script to run my tests, which is included as test.sh. Additionally I created separate .csv files, one for the small data set given in the assignment spec, and another for just the year 2002 from the 10 year data set so I could compare my slopes/absolute residuals with the information given.

**NOTE: I would like to point out that their is an issue with my multithreaded code. Everything runs smoothly on my laptop, however on the linux machines at school datapar.c seg faults on the larger data sets. I have figured out that it is due to having too many threads, which I am making the assumption that the school servers limit the number of threads I am able to create. In order to fix this I would have to change my code to use less threads, which I did not have time to implement. If you have a look at my analysis document, I have a screenshot of the tests I ran using my laptop, free of seg faults and my results. 

Resources Used:

-Programming assignment spec
https://dspace.library.uvic.ca/bitstream/handle/1828/11460/Computing%20L1%20Straight-Line%20Fits%20to%20Data%20%28Part%201%29.pdf?sequence=1&isAllowed=y (Ian Barrodales Paper)

https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/ 
https://stackoverflow.com/questions/7951019/how-to-convert-string-to-float
http://man7.org/linux/man-pages/man3/pthread_create.3.html

