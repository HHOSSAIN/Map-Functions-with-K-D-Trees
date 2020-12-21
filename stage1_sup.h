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

double* radius(double x1, double y1, double x2, double y2, double* D_sq);
double* distance(double x1, double y1, double x2, double y2, double* D_sq);
double* distance_check(double nx, double qx, double* dsq);
//node_t* shortest(double qx,double qy,node_t* node, double* Dsq,int c,int* pos, int* count,int first, node_t* best);
void shortest(double qx,double qy,node_t* node, double* Dsq,int c,int* pos, int* count,int first, node_t** best);
void print_shortest(node_t* best, char* xx, char* yy, FILE* output);