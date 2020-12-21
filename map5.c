/*  Creating a K-D tree based to store information from the 
 *  City of Melbourne Census of Land Use and Employment (CLUE)
 *  and finding the locations in the dataset which falls within
 *  a specified radius from a specied coordinate
 * 
 *  Coded by HASNE HOSSAIN *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "stage2_sup.h"
#include "list_tree.h" //also stage1
#include "dicsup.h" //also stage1


double* distance(double x1, double y1, double x2, double y2, double* D_sq);
double* distance_check(double nx, double qx, double* dsq);
void shortest(double qx,double qy,node_t* node, double* Dsq,int c,int* pos, int* count,int first, node_t** best);
void print_shortest(node_t* best, char* xx, char* yy);

int main(int argc, char **argv){
    FILE *fp;
    FILE *output;
    output=fopen(argv[2],"w");
    assert(output); 

    char *line = NULL;  
    size_t lineBufferLength = 0;    
    
    fp= fopen(argv[1], "r");
    assert(fp);
 
	/* using getline to get rid of the headers  */
    getline(&line, &lineBufferLength, fp ); 
	
    node_t* nodp;     
    node_t *parent=NULL;
	
	/* PART1- going thorugh data in csv file and storing them in a
	 * K-D tree with potential linked list along some nodes 
     * for identical keys */
    nodp= make_node();  
    assert(nodp);

    do{
		if(nodp->data->censusYear == NULL){
			read_1_line(nodp->data,fp); 
		}
		else{
			nodp->data= malloc(sizeof(dict_t)); 
			read_1_line(nodp->data,fp); 
		}

		/*if(nodp->data->censusYear[0] != '\0'){ //ki hoche ekhane????
			//printf("read x=%s\n", nodp->data->x);
			//printf("read y=%s\n", nodp->data->y);
			
		} */

        if(nodp->data->censusYear[0] != '\0'){ //new
            parent=bstInsert(parent,nodp->data);                     
        }
        
      //printf("hi,1 bst insert finished\n");

    }while ((nodp->data->censusYear[0]) != '\0'); 
    
    /*.......................END OF MAKING TREE..................*/

    free(nodp); //NOTUN

    char *line2 = NULL;  //line_buff
    size_t lineBufferLength2 = 34; //line_buff_size
    size_t chars2= 0; //i added; //line_size

    char* xx; char* yy; char* rad; char* helper; //int i=0,j=0,k=0;
    
    /* Read lines from "key" file and processing them */
    while((chars2=getline(&line2, &lineBufferLength2, stdin ))!= -1){
        char *token;
   
        /* get the first token */
        int tok_count=0;
        token = strtok(line2, " "); //edit
   
        /* walk through other tokens */
        while( token != NULL ) {
            if(tok_count==0){
                xx=token;
                //printf("xx=%s ",xx);
            }
            if(tok_count==1){
                yy=token;
                //printf("yy=%s ",yy);
            }
            if(tok_count==2){
                int len= strlen(token);
                if(token[len-2]=='\r' && token[len-1]=='\n'){
                    helper= strtok(token,"\r\n");
                    rad=helper;
                }
                else if(token[len-1]=='\n'){
                    helper= strtok(token,"\n");
                    rad=helper;
                }
                else if(token[len-2]=='\r' || token[len-1]=='\r'){
                    helper= strtok(token,"\r");
                    rad=helper;
                }
                else{
                    rad=token;
                }                
                //printf("rad=%seeee \n",rad); //there's '\r' at its end...try to remove
            }
            tok_count += 1;
            token = strtok(NULL, " ");
        }    
        
        double xs= atof(xx);
        double ys= atof(yy);
        double rads= atof(rad);

        //printf("xs=%f ys=%f rads=%f\n", xs, ys,rads);

        int c=0; int count=0; int found=0; //first=1; 
        
        //printf("check1\n");
    
        radius_search(xs,ys,rads,parent,c,&found,&count,xx,yy,rad,output);
        if(found == 0){
            fprintf(output,"%s %s %s --> NOTFOUND\n",xx,yy,rad);
        }
        fprintf(output,"\n");
        
        /*printf("check2\n");
        printf("count=%d\n", count); */

        printf("%s %s %s --> %d\n",xx,yy,rad, count);;
    } 

    /*......................end of part1.............................*/
    
    fclose(fp);
    fclose(output);
    free(line);
    free(line2); //NOTUN
    free_tree(parent);

    return 0;

	/*................................DONE............................... */
	/*                         ALGORITHMS ARE FUN!                        */
}



