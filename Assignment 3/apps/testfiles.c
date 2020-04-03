#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    printf("Testing Create File\n");
    initLLFS();
    char* teststr = "hi my name is katherine";
    create_file((byte*)teststr);
    printf("Testing Delete File\n");
    delete_file(2);
    printf("Printing Inode List: \n");
    print(inodelist_head);
     printf("--------------------------\n");
    printf("Printing BLOC list: \n");
    print(blocklist_head);
    return 1;
}