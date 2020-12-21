#ifndef STRUCT_H
#define STRUCT_H

#define SIZE 50
#define SIZE2 128+2
#define MAXKEYSIZE 128+2
#define MAXLINESIZE 512+2

typedef struct{
    char* censusYear;  //int
    char* BlockID;  //int
    char* propertyId; //int
    char* basePropertyId; //int
    char* ClueSmallArea; 
    char* tradingName; 
    char* industryCode; //int
    char* industryDescription;  //int
    char* x;  //double...key
    char* y; //double....key
	double X;
    double Y;
    char* location;  
}dict_t;

//hmmmmmmm

typedef struct bst node_t;
typedef struct l list_t;

struct bst {
    node_t *left;
    node_t *right;
    dict_t* data;
    node_t* next; //for linked list
    list_t* list;
};

//typedef struct { 
struct l{ 
	node_t *head;
	node_t *foot;
}; 

#endif 

double* radius_calc(double x1, double y1, double x2, double y2, double* D_sq);
double* dx_dy(double nx, double qx, double* dsq);
//void radius_search(double qx,double qy, double radius, node_t* node, int c, int* count,char* xx, char* yy);
void radius_search(double qx,double qy, double radius, node_t* node, int c,int* found, int* count,char* xx, char* yy, char* rad,FILE* output);
//void print_rad_node(node_t* node, char* xx, char* yy);
void print_rad_node(node_t* node, char* xx, char* yy, char* rad,FILE* output);