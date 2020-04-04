#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    initLLFS();
    printf("Testing create inode list.\n");
    print(inodelist_head);
    printf("Testing get free inode\n");
    int inode = pop_front(inodelist_head);
    printf("Inode #: %d\n", inode);
    print(inodelist_head);
    inode = pop_front(inodelist_head);
    printf("Inode #: %d\n", inode);
    print(inodelist_head);

    printf("-----------------------------\n");
    printf("Testing create block list.\n");
    print(blocklist_head);
    printf("Testing get free block\n");
    int block = pop_front(blocklist_head);
    printf("block #: %d\n", block);
    print(blocklist_head);
    block = pop_front(blocklist_head);
    printf("block #: %d\n", block);
    print(blocklist_head);

    printf("-----------------------------\n");
    printf("Testing closeLLFS.\n");
    closeLLFS();
    printf("BlockList: \n");
    print(blocklist_head);
    printf("No?\n");
    printf("Inode List: \n");
    print(inodelist_head);
    




    return 1;
}
