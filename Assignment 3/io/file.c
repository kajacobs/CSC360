#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "../disk/disk.c"


typedef unsigned char byte;

struct node {
    int number;
    struct node* next;
    struct node* prev;
};

struct node** blocklist_head;
struct node** inodelist_head;


// Node Funtions 
struct node* create(int elem);
struct node* begin(struct node* ref);
struct node* end(struct node* ref);
struct node* next(struct node* ref);
struct node* prev(struct node* ref);
int getValue(struct node* ref);
void push_back(struct node** listHead, int newElem);
int pop_front(struct node** listHead);
void erase(struct node* ref);
void print(struct node** listHead);

// FS Functions 
void initLLFS();
void startLLFS();
byte* init_freeblocks();
byte* init_inodes();
void create_free_blocklist();
void create_free_inodelist();
void set_block(byte* block, int block_num);
void unset_block(byte* block, int block_num);
int get_block(byte* block, int block_num);
int create_directory();
void add_file_to_directory(int parent_node_num, int child_node_num, char* filename);

// To DO (back end)
void delete_directory();
void addto_directory();
void create_file();
void delete_file();
void write_inode();
void write_block();
// add ref to directory
// close llfs and free lists (add clear() from linked list)


//TO do (user)
void parse_arguments();


/* -------------------Node Structure--------------------------*/
// Code was taken from the doubly linked list code in assignment #1
// and slightly modified to suite this assignment.

struct node* create(int elem) {
    struct node* newNode
        = (struct node*)malloc(sizeof(struct node));
    newNode->number = elem;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

struct node* begin(struct node* ref) {
    if (ref == NULL) return NULL;
    while(ref->prev) {
        ref = prev(ref);
    }
    return ref;
}

struct node* end(struct node* ref) {
    if (ref == NULL) return NULL;
    while(ref->next) {
        ref = next(ref);
    }
    return ref;
}

struct node* next(struct node* ref) {
    if (ref == NULL) return NULL;
    return ref->next;
}

struct node* prev(struct node* ref) {
    if (ref == NULL) return NULL;
    return ref->prev;
}

int getValue(struct node* ref) {
    return ref->number;
}

void push_back(struct node** listHead, int newElem) {
    struct node* ref = *listHead;
    struct node* temp = create(newElem);
    
    if (ref == NULL){
        ref = temp;
        *listHead = ref;
    } else {
        ref = end(ref);
        ref->next = temp;
        temp->prev = ref;
    }
}

int pop_front(struct node** listHead) {
    struct node* ref = *listHead;
    int value = -1;
    ref = begin(ref);
    if (next(ref) == NULL) {
        value = getValue(ref);
        erase(ref);
        *listHead = NULL;
    } else {
        ref = next(ref);
        value = getValue(prev(ref));
        erase(prev(ref));
        *listHead = ref;
    }
    return value;
}

void erase(struct node* ref) {
    struct node* nx = next(ref);
    struct node* px = prev(ref);

    free(ref);

    if(nx) {
        nx->prev = px;
    }

    if(px) {
        px->next = nx;
    }
}

void print(struct node** listHead) {
    struct node* ref = *listHead;
    ref = begin(ref);
    if (ref == NULL) return;
    do {
        printf("%d ",ref->number);
    } while((ref = next(ref)) != NULL);
    printf("\n");
}

/*--------------------------Init and Start LLFS---------------------------------*/

/* Initializes the LLFS with Superblock, free inode and block vectors
 * creates free inode and block lists, formats disk to all 0's,
 * and creates the root directory inode */
void initLLFS(){
    // initialize disk to all 0's
    initDisk(); 

    // Initialization of Superblock.
    byte* superBlock = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    // magic number 0x17 = 23
    superBlock[3] = 0x17;
    // number of blocks on disk 0x1000 = 4096 blocks
    superBlock[6] = 0x10;
    superBlock[7] = 0x00;
    // number of inodes on disk 0x100 = 256 inodes
    superBlock[10] = 0x01;
    superBlock[11] = 0x00;
    writeBlock(0, superBlock);
    free(superBlock);

    // bit vector for determining which blocks are available.
    // Ignores first 259 blocks
    byte* free_block_vector = init_freeblocks();
    writeBlock(1, free_block_vector);
    free(free_block_vector);

    // bit vector for determining which inodes are available.
    // Ignores blocks after 256
    byte* free_inode_vector = init_inodes();
    writeBlock(2, free_inode_vector);
    free(free_inode_vector);

    startLLFS();

    //create root directory inode
    int root_directory = create_directory();
    char *name = "..";
    add_file_to_directory(root_directory, root_directory, name);

}


// opens LLFS
void startLLFS(){
    create_free_blocklist();
    create_free_inodelist();
}

/*-------------------Init Free block and inode bit vectors-----------------------*/

// Initializes free_block vector. blocks 0-258 are set to 1
byte* init_freeblocks(){
    byte* free_block_vector = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    for (int i = 0; i < BLOCK_SIZE; i++){
        if (i < 32){
            free_block_vector[i] = 0xFF;
        } else if (i == 32){
            free_block_vector[i] = 0xE0;
        } else {
            free_block_vector[i] = 0x0;
        }
    }
    return free_block_vector;
}

// Initializes free_inode vector. blocks 256-> are set to 1.
byte* init_inodes(){
    byte* free_inode_vector = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    for (int i = 0; i < BLOCK_SIZE; i++){
        if (i == 0){
            free_inode_vector[i] = 0xFF;
        }
        else if (i < 256){
            free_inode_vector[i] = 0x00;
        } else {
            free_inode_vector[i] = 0xFF;
        }
    }
    return free_inode_vector;
}

/* -------------------Create free block and inode lists-------------------------*/
void create_free_blocklist(){
    blocklist_head = (struct node**)calloc(1, sizeof(struct node*));
    *blocklist_head = NULL;

    byte* block = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    readBlock(1,block);

    for (int i = 0; i < BLOCK_SIZE; i++){
        if (get_block(block, i) == 0){
             push_back(blocklist_head, i);
        }
    }
}

 // creates a list of all free inodes at program start time
void create_free_inodelist(){
    inodelist_head = (struct node**)calloc(1, sizeof(struct node*));
    *inodelist_head = NULL;
    byte* block = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    readBlock(2, block);

    for (int i = 0; i < BLOCK_SIZE; i++){
        if (block[i] == 0){
            push_back(inodelist_head, i);
        }
    }
}

/* -------------------------Bit vector functions --------------------------------*/
// sets block value to 1 in bit vector
void set_block(byte* block, int block_num){
    int index = block_num / 8;
    int bit_index = block_num % 8;
    bit_index = 7 - bit_index;
    block[index] |= 1UL << bit_index;
}

// unsets value of block in bit vector
void unset_block(byte* block, int block_num){
    int index = block_num / 8;
    int bit_index = block_num % 8;
    bit_index = 7 - bit_index;
    block[index] &= ~(1UL << bit_index);
}

// gets status of block, either 1 or 0
int get_block(byte* block, int block_num){
    int index = block_num / 8;
    int bit_index = block_num % 8;
    bit_index = 7 - bit_index;
    int bit = (block[index] >> bit_index) & 1U;
    return bit;
}

/* --------------------------------------------------------------------------------*/

int create_directory(){
    int block_num = pop_front(blocklist_head);
    int inode_num = pop_front(inodelist_head);

    // Create Inode
    byte* inode = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    //size of file
    inode[3] = 32;
    //set flag to be directory
    inode[4] = 0xDD;
    inode[8] = block_num / 256;
    inode[9] = block_num % 256;

    writeBlock((inode_num+2), inode);

    byte* free_inode_vector = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    readBlock(2, free_inode_vector);
    free_inode_vector[inode_num] = 0xFF;
    writeBlock(2, free_inode_vector);
    free(free_inode_vector);

    // Create reference Block
    byte* block = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    block[0] = inode_num;
    printf("Inode number = %d\n", inode_num);
    strncpy((char*)(block + 1),".", 1);
    writeBlock(block_num, block);
    free(block);

    byte* free_block_vector = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    readBlock(1, free_block_vector);
    set_block(free_block_vector, block_num);
    writeBlock(1, free_block_vector);
    free(free_block_vector);

    return inode_num;
}

// adds given file to directory
// Used resource below for calculating int to hex for file size
// https://stackoverflow.com/questions/3784263/converting-an-int-into-a-4-byte-char-array-c
void add_file_to_directory(int parent_node_num, int child_node_num, char* filename){
    //get parent inode block
    byte* parent_inode = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    readBlock((parent_node_num + 2), parent_inode);

    int parent_block_num = ((int)parent_inode[8])*256 + (int)parent_inode[9];
    printf("Parent block number is: %d\n", parent_block_num);

    //get parent block
    byte* parent_block = (byte*)calloc(BLOCK_SIZE, sizeof(byte));
    readBlock(parent_block_num, parent_block);

    // add file to directory
    for (int i = 0; i < BLOCK_SIZE; i += 32){
        if (parent_block[i] == 0x00){
            printf("We doing the thing now.\n");
            parent_block[i] = child_node_num;
            strncpy((char*)(parent_block + (i+1)), filename, strlen(filename));
            break;
        } else {
            printf("Checking next spot.\n");
        }
    }

    int dir_size = ((int)parent_inode[3]) + 256*((int)parent_inode[2]) + 256*256*((int)parent_inode[1]);
    dir_size += 32;
    printf("DIR SIZE HUR DUR: %d\n", dir_size);
    parent_inode[3] = dir_size & 0xFF;
    parent_inode[2] = (dir_size >> 8) & 0xFF;
    parent_inode[1] = (dir_size >> 16) & 0xFF;
    parent_inode[0] = (dir_size >> 24) & 0xFF; 

    writeBlock(parent_block_num, parent_block);
    writeBlock((parent_node_num + 2), parent_inode);
    free(parent_block);
    free(parent_inode);

}