#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/file.h"

int main(){
    printf("Formatting disk.\n");
    initLLFS();
    create_free_blocklist();
    print(blocklist_head);
    return 1;
}