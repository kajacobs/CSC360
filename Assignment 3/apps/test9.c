#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    startLLFS();
    char args[] = "mkdir /Documents/CSC320";
    parse_arguments(args);
    char args2[] = "addfile /Documents/CSC320/Assignment3 largefile.txt";
    parse_arguments(args2);
    char args3[] = "mkdir /Documents/CSC320/CSC360";
    parse_arguments(args3);
    char args4[] = "addfile /Documents/CSC320/myfile myfile.txt";
    parse_arguments(args4);
    char args5[] = "addfile /Documents/myfile myfile.txt";
    parse_arguments(args5);

    char args7[] = "rm /Documents/CSC320/Assignment3";
    parse_arguments(args7);
    char args8[] = "rm /Documents/CSC320/CSC360";
    parse_arguments(args8);
    char args9[] = "rm /Documents/CSC320/myfile";
    parse_arguments(args9);
    char args6[] = "rm /Documents/CSC320";
    parse_arguments(args6);
    char args10[] = "rm /Documents/myfile";
    parse_arguments(args10);
    char args11[] = "rm /Documents";
    parse_arguments(args11);
    closeLLFS();
    return 1;
}