#ifndef STRUCT_H
#define STRUCT_H

#define SIZE 50
#define SIZE2 128+2
#define MAXKEYSIZE 128+2
#define MAXLINESIZE 512+2

typedef struct{
    char* censusYear;
    char* BlockID; 
    char* propertyId;
    char* basePropertyId; 
    char* ClueSmallArea; 
    char* tradingName; 
    char* industryCode; 
    char* industryDescription; 
    char* x; 
    char* y; 
	double X;
    double Y;
    char* location;  
}dict_t;


typedef struct bst node_t;
typedef struct l list_t;

struct bst {
    node_t *left;
    node_t *right;
    dict_t* data;
    node_t* next; 
    list_t* list;
};

//typedef struct { 
struct l{ 
	node_t *head;
	node_t *foot;
}; 

#endif 

list_t *make_empty_list(void);
list_t *insert_at_foot(list_t *list, dict_t*value);
void free_list(list_t *list);
void free_tree(node_t* node);
node_t *bstInsert(node_t *parent, dict_t* data);
void printLeft(node_t *parent);
node_t* make_node();
void printList(node_t *parent);