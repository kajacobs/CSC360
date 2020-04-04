#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    printf("Testing Directory Creation\n");
    initLLFS();
    printf("1\n");
    int inode_num = create_file();
    printf("2\n");
    printf("Inode of new File: %d\n", inode_num);
    return 1;
}
