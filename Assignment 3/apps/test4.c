#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){ 
    startLLFS();
    char args[] = "mkdir /Documents/CSC320/CSC360/CSC361";
    parse_arguments(args);
    char args2[] = "rm /Documents/CSC320/CSC360/CSC361";
    parse_arguments(args2);
    char args3[] = "rm /Documents/CSC320/CSC360";
    parse_arguments(args3);
    char args4[] = "rm /Documents/CSC320";
    parse_arguments(args4);
    char args5[] = "rm /Documents";
    parse_arguments(args5);
    closeLLFS();
    return 1;
}