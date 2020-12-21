/*  Creating a K-D tree based to store information from the 
 *  City of Melbourne Census of Land Use and Employment (CLUE)
 *  and finding the location(s) in the dataset which are closest 
 *  to a specied coordinate.
 * 
 *  Coded by HASNE HOSSAIN *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "list_tree.h"
#include "dicsup.h"
#include "stage1_sup.h"

int main(int argc, char **argv){
    FILE *fp;
    FILE *output;

    char *line = NULL;  
    size_t lineBufferLength = 0;    
    
    fp= fopen(argv[1], "r");
    assert(fp);
    output=fopen(argv[2],"w");
    assert(output);
 
	/* using getline to get rid of the headers  */
    getline(&line, &lineBufferLength, fp ); 
	
    node_t* nodp;     
    node_t *parent=NULL;
	
	/* PART1- going thorugh data in csv file and storing them in a K_D
	 * tree and potential linked list at some nodes */
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

        if(nodp->data->censusYear[0] != '\0'){ //new
            parent=bstInsert(parent,nodp->data); 
			                      
        }

    }while ((nodp->data->censusYear[0]) != '\0'); 

    /*.................................End of tree making............................*/

    free(nodp); 

    /*NEW */
    char *line2 = NULL;  
    size_t lineBufferLength2 = 34; //line_buff_size
    size_t chars2= 0; //line_size

    char* xx; char* yy; char* helper;

    while((chars2=getline(&line2, &lineBufferLength2, stdin ))!= -1){
        char *token;
   
        /* get the first token */
        int tok_count=0;
        token = strtok(line2, " "); 
   
        /* walk through other tokens */
        while( token != NULL ) {
            if(tok_count==0){
                xx=token;
                //printf("xx=%s ",xx);
            }
            
            if(tok_count==1){
                int len= strlen(token);
                if(token[len-2]=='\r' && token[len-1]=='\n'){
                    helper= strtok(token,"\r\n");
                    //rad=helper;
                    yy=helper;
                }
                else if(token[len-1]=='\n'){
                    helper= strtok(token,"\n");
                    //rad=helper;
                    yy=helper;
                }
                else if(token[len-2]=='\r' || token[len-1]=='\r'){
                    helper= strtok(token,"\r");
                    //rad=helper;
                    yy=helper;
                }
                else{
                    //rad=token;
                    yy=token;
                } 

                /* print statement for ease of debugging commented out */
                //printf("yy=%seeee \n",yy); //there's '\r' at its end...try to remove

            }
            tok_count += 1;
            token = strtok(NULL, " ");
        }    
        
        //printf("yy=%s ",yy);
        double xs= atof(xx);
        double ys= atof(yy);
        //printf("xs=%f ys=%f\n", xs, ys);

        double* Dsq=malloc(sizeof(double)); int c=0; int pos=0, count=0, first=1; 
    
        node_t* best= NULL;

        /* returns best node;updates Dsq nd count */
        shortest(xs,ys,parent,Dsq,c,&pos,&count,first, &best); 
        
        print_shortest(best,xx,yy,output);

        free(Dsq); 

        //printf("check2\n");
        //printf("count=%d\n", count);
        printf("%s %s --> %d\n",xx,yy, count);
    } 

    /*......................end of stage1.............................*/
    
    fclose(fp);
    fclose(output);
    free(line);
    free(line2);
    free_tree(parent);
    //free(Dsq);
   
    return 0;

	/*................................DONE............................... */
	/*                         ALGORITHMS ARE FUN!                        */
}
