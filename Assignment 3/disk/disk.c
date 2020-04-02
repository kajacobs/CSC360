#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 4096;


/* BLOCK 0 is the Superblock */
/* BLOCK 1 is the free block list */
/* BLOCK 2 is the free inode list */
/* BLOCKS 3-259 are reserved for inodes */

void readBlock(int blockNum, unsigned char* buffer){
    FILE* disk = fopen("../disk/vdisk", "r");
    fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
    fread(buffer, BLOCK_SIZE, 1, disk);
    fclose(disk);
}

void writeBlock(int blockNum, unsigned char* data){
    FILE* disk = fopen("../disk/vdisk", "r+");
    fseek(disk, blockNum * BLOCK_SIZE, SEEK_SET);
    fwrite(data, BLOCK_SIZE, 1, disk);
    fclose(disk);
}

void initDisk(){
    FILE* disk = fopen("../disk/vdisk", "w");
    fseek(disk, (BLOCK_SIZE * NUM_BLOCKS)+1, SEEK_SET);
    fwrite("\0", 1, 1, disk);
    fclose(disk);
}