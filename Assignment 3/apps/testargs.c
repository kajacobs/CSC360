#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    printf("Testing Split Args\n");
    char args[] = "mkdir /yeet/yote/yate/mahdog";
    initLLFS();
    parse_arguments(args);
    return 1;
}