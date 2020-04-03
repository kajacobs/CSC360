#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    printf("Testing Add File\n");
    initLLFS();
    char* teststr = "hi my name is katherine";
    create_file((byte*)teststr);
    printf("Testing Add File to Directory File\n");
    char *name = "MyFile.c";
    add_file_to_directory(1, 2, name);
    closeLLFS();
    return 1;
}