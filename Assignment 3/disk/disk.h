#ifndef __disk_h__
#define __disk_h__

const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 4096;

void readBlock(int blockNum, unsigned char* buffer);
void writeBlock(int blockNum, unsigned char* data);
void initDisk();


#endif