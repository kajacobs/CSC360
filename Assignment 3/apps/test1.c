#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    printf("Below is the hexdump after initializing the disk. This hexdump has also been added to init_hexdump.txt for comparing future tests.\n");
    initLLFS();
    closeLLFS();
    return 1;
}