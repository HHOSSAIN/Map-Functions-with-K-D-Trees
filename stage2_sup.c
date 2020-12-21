#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "stage2_sup.h"

/* Calculates radius or distance between 2 points */
double* radius_calc(double x1, double y1, double x2, double y2, double* D_sq){ //finds radius or radius^2
    *D_sq=sqrt(pow((x1-x2),2) + pow((y1-y2),2));
    return D_sq;
}

/* finds di or di^2, i.e distance betn query key er x or y with corresponding x or y of node */
double* dx_dy(double nx, double qx, double* dsq){  
    *dsq = nx-qx; //prolly this dsq needs to be freed
    return dsq;
}

/* finds points within specified radius and also prints their details to ouptut file */
void radius_search(double qx,double qy, double radius, node_t* node, int c,int* found, int* count,char* xx,
                    char* yy,char* rad, FILE* output){
    if(node == NULL){
        //printf("best0->data->X=%f, Y=%f\n",(*best)->data->X, (*best)->data->Y);
        return;
    }
    else
    {
        *count += 1;
    }
    
   
    double* di= malloc(sizeof(double));
    assert(di);
    double* tmp_r = malloc(sizeof(double));
    assert(tmp_r);
    tmp_r= radius_calc(qx,qy,node->data->X, node->data->Y, tmp_r);
    
    if(*tmp_r <= radius){
        *found=1;
        print_rad_node(node,xx,yy,rad,output);
    }
    free(tmp_r); 

    /* finding distance between node and query point's corresponding x or y values*/
    di=dx_dy(qx,node->data->X,di);
    //printf("*di=%f\n",*di);

    if(c%2 == 0){
        if(qx < node->data->X){

            /* search left */
            radius_search(qx,qy,radius,node->left,c+1,found,count,xx,yy,rad,output); 

            if(*di <= radius){ //i.e if di <= radius,go both ways
                radius_search(qx,qy,radius,node->right,c+1,found,count,xx,yy,rad,output);           
            }
        }

        else{

            /* search right */
            radius_search(qx,qy,radius,node->right,c+1,found,count,xx,yy,rad,output);
            
            /* if di <= radius,go both ways */
            if(*di <= radius){ 
                radius_search(qx,qy,radius,node->left,c+1,found,count,xx,yy,rad,output);
            }
        }
        
    }
    else{
        if(qy<node->data->Y){

            /*search left */
            radius_search(qx,qy,radius,node->left,c+1,found,count,xx,yy,rad,output);

            /* i.e if di <= radius,go both ways */
            if(*di <= radius){ 
                radius_search(qx,qy,radius,node->right,c+1,found,count,xx,yy,rad,output);          
            }
        }
        else{ 

            /* search right */
            radius_search(qx,qy,radius,node->right,c+1,found,count,xx,yy,rad,output);

            /* if di <= radius,go both ways */
            if(*di <= radius){ 
                radius_search(qx,qy,radius,node->left,c+1,found,count,xx,yy,rad,output);
            }
        }
    }
    free(di);
}

/* prints details of node or nodes into file */
void print_rad_node(node_t* node, char* xx, char* yy, char* rad, FILE* output){
    
    /* node_t* new points to shortest path node */
    node_t* new=node;
    int count=0;
    while (new){
        fprintf(output, "xx=%s yy=%s rad=%s --> Census year: %s || Block ID: %s || Property ID: %s || Base property ID: %s || CLUE small area: %s || Trading Name: %s || Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: %s || \n",xx,yy,rad ,new->data->censusYear, new->data->BlockID, 
                new->data->propertyId,new->data->basePropertyId, 
                new->data->ClueSmallArea, new->data->tradingName, new->data->industryCode, 
                new->data->industryDescription, new->data->x, 
                new->data->y, new->data->location);
        if(new->list && count==0){
            new->next= new->list->head;
            count = 1;
        }
        new=new->next;
    }   
    return;
} 