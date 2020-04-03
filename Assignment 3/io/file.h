#ifndef __file_h__
#define __file_h__

typedef unsigned char byte;
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
void clear(struct node** listHead);
void print(struct node** listHead);

// FS Functions 
void initLLFS();
void startLLFS();
void closeLLFS();
byte* init_freeblocks();
byte* init_inodes();
void create_free_blocklist();
void create_free_inodelist();
void set_block(byte* block, int block_num);
void unset_block(byte* block, int block_num);
int get_block(byte* block, int block_num);
int create_directory();
void add_file_to_directory(int parent_inode_num, int child_node_num, char* filename);
int delete_file_from_directory(int parent_inode_num, char* filename);
int create_file();
void delete_file(int inode_num);
void reclaim_block(int block_num);
void reclaim_inode(int inode_num);

#endif