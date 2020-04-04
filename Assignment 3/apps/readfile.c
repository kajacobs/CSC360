#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    printf("Testing Read File\n");
    char args[] = "read /yeet/yote/myfile";
    startLLFS();
    parse_arguments(args);
    return 1;
}