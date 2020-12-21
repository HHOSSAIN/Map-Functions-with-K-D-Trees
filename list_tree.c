#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "list_tree.h"

/* some functions here was written by Alistair Moffat and has been modified 
 * by Hasne Hossain according to his project need  */

node_t *bstInsert(node_t *parent, dict_t* data){
    /* Write this function. */
    node_t **insertLocation = &parent; int stop=0;
                                     
    int count=0; int ll=0; 
	while(*insertLocation && stop==0){ 

        /* Print statements for debugging purpose */
		    /*printf("hmm,got inside of loop\n");
		    printf("atof data x= %f ", atof(data->x));
		    printf("inside loop data er string x= %s,  data->X=%f\n", data->x, data->X);
		*/

        if(count%2 == 0){
		    if(atof(data->x) < atof((*insertLocation)->data->x)){ 
			    insertLocation = &((*insertLocation)->left); 
		    } 

            else { //>=
                if(atof(data->x) == atof((*insertLocation)->data->x) && atof(data->y) == atof((*insertLocation)->data->y)){
                    if((*insertLocation)->list == NULL){
                        (*insertLocation)->list= make_empty_list();
                        assert((*insertLocation)->list);
                    }
                    (*insertLocation)->list= insert_at_foot((*insertLocation)->list, data);
					ll=1;
                    stop=1; //flag variable to stop the loop
                }
                else{
			        insertLocation = &((*insertLocation)->right);
                }
		    }
        }

        else{
            if(data->Y < (*insertLocation)->data->Y){
                insertLocation = &((*insertLocation)->left);
            }
            else{ //>=
                if(data->X == (*insertLocation)->data->X && data->Y == (*insertLocation)->data->Y){ 
                    /* make a linked list */
                     if((*insertLocation)->list == NULL){
                        (*insertLocation)->list= make_empty_list();
                        assert((*insertLocation)->list);
                    }
                    (*insertLocation)->list= insert_at_foot((*insertLocation)->list, data);
                    ll=1;
                    stop=1; //means stop the loop
                }
                else{
                    insertLocation = &((*insertLocation)->right);
                }
            }
            
        }
        if(ll==0){
            count += 1;
        }
        
	}
    if(ll==0){
		*insertLocation = (node_t *) malloc(sizeof(node_t)); 
		assert(*insertLocation);
	
		(*insertLocation)->left = NULL;
		(*insertLocation)->right = NULL;
		(*insertLocation)->next = NULL;
		(*insertLocation)->data = data; 
	}
	
	
	return parent;
} 

/*void printLeft(node_t *parent){
    node_t* shifter;
    shifter= parent;
    while (shifter){
        printf("x=%s, y=%s\n", shifter->data->x, shifter->data->y);
        shifter=shifter->left;
    }
}*/
void printList(node_t *parent){
    node_t* shifter;
    printf("parent x=%s, y=%s\n", parent->data->x, parent->data->y);
    shifter= parent->left;
    printf("left is x=%s, y=%s\n", shifter->data->x, shifter->data->y);
}

list_t
*make_empty_list(void) {
	list_t *list;  
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
   	return list;
}

list_t
*insert_at_foot(list_t *list, dict_t*value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(node_t));
	assert(list!=NULL && new!=NULL);
	new->data = value;
	new->next = NULL;
    new->left = NULL;
	new->right = NULL;
	new->list = NULL;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}


void free_tree(node_t* node){ 
    if(node != NULL){
        free_tree(node->left);
        free_tree(node->right);
        if(node->list){
            free_list(node->list);
        }
        free(node->data->censusYear); //1
        free(node->data->BlockID); //1
        free(node->data->propertyId); //1
        free(node->data->basePropertyId); //1
        free(node->data->ClueSmallArea); //1
        free(node->data->tradingName); //1
        free(node->data->industryCode); //1
        free(node->data->industryDescription); //1
        free(node->data->x); //1
        free(node->data->y); //1
        free(node->data->location); //1
        free(node->data); //1 added
		//free(node);
        free(node);
    }
}

 
void free_list(list_t *list) {
	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;  
	while (curr) {
		prev = curr;
		curr = curr->next;
        free(prev->data->censusYear);
        free(prev->data->BlockID); 
        free(prev->data->propertyId); 
        free(prev->data->basePropertyId); 
        free(prev->data->ClueSmallArea); 
        free(prev->data->tradingName); 
        free(prev->data->industryCode); 
        free(prev->data->industryDescription); 
        free(prev->data->x); 
        free(prev->data->y); 
        free(prev->data->location); 
        free(prev->data);
		free(prev);
	}
	free(list);
} 

node_t* make_node(){
    node_t *new=malloc(sizeof(node_t));
    assert(new);
    new->data=malloc(sizeof(dict_t));
    assert(new->data);

    new->data->censusYear=NULL;
    new->data->BlockID = NULL;
    new->data->propertyId = NULL;
    new->data->basePropertyId=NULL;
    new->data->ClueSmallArea=NULL;
    new->data->tradingName=NULL;
    new->data->industryCode=NULL;
    new->data->industryDescription=NULL;
    new->data->x=NULL;
    new->data->y=NULL;
    new->data->location=NULL;

    new->next=NULL;
    new->left=NULL;
    new->right=NULL;
    return new;
}
