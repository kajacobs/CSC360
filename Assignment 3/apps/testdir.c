#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    printf("Testing Directory Creation\n");
    initLLFS();
    int inode_num = create_file();
    printf("Inode of new File: %d\n", inode_num);
    return 1;
}