#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED

#include "scheduler.h"

#include <assert.h>
#include <curses.h>
#include <ucontext.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "util.h"


int main() {
    double clk = (double)clock();
    double cps = (double)CLOCKS_PER_SEC;
    double t = ((double)clock())/((double)CLOCKS_PER_SEC)*1000;
    printf("%f\n",t);
    printf("%f\n",clk/cps);

    sleep(2);
    t = ((double)clock())/((double)CLOCKS_PER_SEC)*1000;
    printf("%f\n",t);
    return 1;
}