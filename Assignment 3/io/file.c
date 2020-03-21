#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "../disk/disk.c"

typedef unsigned char byte;


void initLLFS(){
    // initialize disk to all 0's
    initDisk(); 

    byte* superBlock = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    // magic number 0x17 = 23
    superBlock[3] = 0x17;
    // number of blocks on disk 0x1000 = 4096 blocks
    superBlock[6] = 0x10;
    superBlock[7] = 0x00;
    writeBlock(0, superBlock);
    free(superBlock);
}