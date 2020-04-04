#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    startLLFS();
    char args[] = "mkdir /Documents/CSC320";
    parse_arguments(args);
    char args2[] = "addfile /Documents/CSC320/Assignment3 myfile.txt";
    parse_arguments(args2);
    char args3[] = "rm /Documents";
    parse_arguments(args3);
    closeLLFS();
    return 1;
}