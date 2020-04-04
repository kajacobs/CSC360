#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){  
    startLLFS();
    char args[] = "mkdir /Documents";
    parse_arguments(args);
    char args2[] = "rm /Documents";
    parse_arguments(args2);
    closeLLFS();
    return 1;
}