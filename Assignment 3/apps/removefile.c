#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    printf("Testing Delete File\n");
    startLLFS();
    printf("Testing Delete File\n");
    char *name = "MyFile.c";
    delete_file_from_directory(1, name);
    return 1;
}