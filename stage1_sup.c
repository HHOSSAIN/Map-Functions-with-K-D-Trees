#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "stage1_sup.h"

/* finds radius */
double* radius(double x1, double y1, double x2, double y2, double* D_sq){ 
    *D_sq=sqrt(pow((x1-x2),2) + pow((y1-y2),2));
    return D_sq;
}

/* finds distance^2 */
double* distance(double x1, double y1, double x2, double y2, double* D_sq){ 
    *D_sq=pow((x1-x2),2) + pow((y1-y2),2);
    return D_sq;
}

/*finds di^2, i.e distance betn query key's x or y with corresponding x or y of node */
double* distance_check(double nx, double qx, double* dsq){  
    *dsq=pow( (nx-qx), 2 ); 
    return dsq;
} 

/* Finds the node/point which is the closest to query point */ 
void shortest(double qx,double qy,node_t* node, double* Dsq,int c,int* pos, int* count,int first, node_t** best){
    if(node == NULL){
        //printf("best0->data->X=%f, Y=%f\n",(*best)->data->X, (*best)->data->Y);
        return;
    }
    else{
        *count +=1;
    }

    double* tmp_Dsq=malloc(sizeof(double));  
    assert(tmp_Dsq);

    tmp_Dsq= distance(qx,qy, node->data->X, node->data->Y, tmp_Dsq); //distance() finds radius or radius^2
    //printf("tmp_Dsq=%f\n",*tmp_Dsq);

    double* dsq= malloc(sizeof(double));
    assert(dsq);

    if(*pos==0){
        *Dsq= *tmp_Dsq;
        //printf("Dsq=%f\n",*Dsq);
        *pos+=1;
        // *count += 1;  
    
    } 
    /* if (*tmp_Dsq <= *Dsq),then only go left."==" only 1st case ei hobe as baki went to linked list Also, *Dsq=*tmp_Dsq 
        now */
     if(first==1 || *tmp_Dsq < *Dsq){
        
        (*best)=node;
        
        if(first==1){
            first=0;
        }
        *Dsq=*tmp_Dsq; //updating Dsq
        (*best)=node; 
    }
    free(tmp_Dsq); //NEW

        if(c%2==0){
            if(qx<node->data->X){ 
                shortest(qx,qy,node->left, Dsq,c+1,pos,count, first,best);   

                /* left confirmed at top, need to check if both */
                dsq=distance_check(qx,node->data->X,dsq); //finds di or di^2
                //printf("*dsqx=%f\n",*dsq);
                if(*dsq <= *Dsq){ 
                    shortest(qx,qy,node->right, Dsq,c+1,pos,count, first,best);
                    if(node->right){
                       //  *count += 1;
                    }
                }
                free(dsq); //NOTUN
            }

            else{ 
                shortest(qx,qy,node->right, Dsq,c+1,pos,count, first,best);
                if(node->right){
                    // *count += 1;
                } 

                /* right confirmed,need to check if both */
                 dsq=distance_check(qx,node->data->X,dsq);
                //printf("*dsqx=%f\n",*dsq);
                if(*dsq <= *Dsq){ 
                    shortest(qx,qy,node->left, Dsq,c+1,pos,count, first,best); 
                    if(node->right){
                        // *count += 1;
                    }

                    //free(dsq); //NOTUN
                }
                free(dsq); //NOTUN
            }
        }
        else{
            if(qy<node->data->Y){ 
                shortest(qx,qy,node->left, Dsq,c+1,pos,count, first,best);
                if(node->left){
                     // *count+=1;  
                }

                dsq=distance_check(qy,node->data->Y,dsq);
                //printf("*dsqy=%f\n",*dsq);
                if(*dsq <= *Dsq){ 
                    shortest(qx,qy,node->right, Dsq,c+1,pos,count, first,best);
                    if(node->right){
                       //  *count += 1;
                    }

                    //free(dsq); //NOTUN
                }
                free(dsq); //NOTUN
            }
            else{ 
                shortest(qx,qy,node->right, Dsq,c+1,pos,count, first,best);
                if(node->right){
                    // *count += 1;
                } 

                dsq=distance_check(qx,node->data->X,dsq);
                //printf("*dsqx=%f\n",*dsq);
                if(*dsq <= *Dsq){ //i.e if di <= radius,go both ways
                    shortest(qx,qy,node->left, Dsq,c+1,pos,count, first,best); //
                    if(node->right){
                        // *count += 1;
                    }

                    //free(dsq); //NOTUN
                }
                free(dsq); //NOTUN
            }
        }
        // *count += 1;
} 

/* prints the details of the point or points closes to query point */
void print_shortest(node_t* best, char* xx, char* yy, FILE* output){
    node_t* new=best; 
    int count=0;
    while (new){
        fprintf(output, "%s %s --> Census year: %s || Block ID: %s || Property ID: %s || Base property ID: %s || CLUE small area: %s || Trading Name: %s || Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: %s || \n",xx,yy, new->data->censusYear, new->data->BlockID, 
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
    fprintf(output, "\n");
    return;
}

