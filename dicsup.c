#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dicsup.h"

/* the functions below read each of the columns from csv dataset */

void read_cyear(dict_t *line, FILE* fp){  
    int c=0, i=0;
    int check=0, found=0, count=0;
    
	int m_size=2; int r_size=0;
	line->censusYear=malloc(sizeof(char)*m_size);
	
    assert(line->censusYear);
    while ((c = getc(fp)) != EOF){ 

		
		 if(r_size == (m_size-1)){
			
			m_size *= 2;
           
			line->censusYear=realloc(line->censusYear, sizeof(char)*m_size);
			assert(line->censusYear);
		} 

        if(check==0 && c=='"'){
            found=1;
            check=1; //my permanent flag
        }
        if(found && c=='"'){
            count +=1 ;
            if(count==1){
                continue; 
            }
        }
        if( (count%2 != 0) && count>1 && c=='"' && c!='\r' && c!='\n'){ 
            line->censusYear[i++]=c;

			r_size += 1;
        }
        else{
            if( (c == ',') && (count%2==0) ){  
                break;
            }
            if(c != '"' && c!='\r' && c!='\n'){
                line->censusYear[i++]= c;
				r_size += 1;
            }
        }
    }
    line->censusYear[i++]='\0';
} 

 void read_block_id(dict_t *line, FILE* fp){ 
    int c=0, i=0;
    int check=0, found=0, count=0;
	int r_size=0, m_size=SIZE;
    line->BlockID=malloc(sizeof(char)*SIZE);
    assert(line->BlockID);
    while ((c = getc(fp)) != EOF){
		
		if(r_size == (m_size-1)){
			m_size *= 2;
			line->BlockID=realloc(line->BlockID, sizeof(char)*m_size);
			assert(line->BlockID);
		}
		
        if(check==0 && c=='"'){
            found=1;
            check=1; //my permanent flag
        }
        if(found && c=='"'){
            count +=1 ;
            if(count==1){
                continue;
            }
        }
        if( (count%2 != 0) && count>1 && c=='"' && c!='\r' && c!='\n'){ 
            line->BlockID[i++]=c;
			r_size += 1;
        }
        else{
            if( (c == ',') && (count%2==0)){  
                break;
            }
            if(c != '"' && c!='\r' && c!='\n'){
                line->BlockID[i++]= c;
				r_size += 1;
            }
        }
    }
    line->BlockID[i++]='\0';
}    

void read_property_id(dict_t *line, FILE* fp){  
    int c=0, i=0;
	int r_size=0, m_size=SIZE;
    line->propertyId=malloc(sizeof(char)*SIZE);
    assert(line->propertyId);
    int check=0, found=0, count=0;
    while ((c = getc(fp)) != EOF){
		
		if(r_size == (m_size-1)){
			m_size *= 2;
			line->propertyId=realloc(line->propertyId, sizeof(char)*m_size);
			assert(line->propertyId);
		}
		
        if(check==0 && c=='"'){
            found=1;
            check=1; //my permanent flag
        }
        if(found && c=='"'){
            count +=1 ;
            if(count==1){
                continue;
            }
        }
        if( (count%2 != 0) && count>1 && c=='"' && c!='\r' && c!='\n'){ 
            line->propertyId[i++]=c;
			r_size += 1;
        }
        else{
            if( (c == ',') && (count%2==0) ){  
                break;
            }
            if(c != '"' && c!='\r' && c!='\n'){
                line->propertyId[i++]= c;
				r_size += 1;
            }
        }
    }
    line->propertyId[i++]='\0';
}

void read_base_property_id(dict_t *line, FILE* fp){  
    int c=0, i=0;
	int r_size=0, m_size=SIZE;
    line->basePropertyId=malloc(sizeof(char)*SIZE);
    assert(line->basePropertyId);
    int check=0, found=0, count=0;
    while ((c = getc(fp)) != EOF){
		
		if(r_size == (m_size-1)){
			m_size *= 2;
			line->basePropertyId=realloc(line->basePropertyId, sizeof(char)*m_size);
			assert(line->basePropertyId);
		}
		
        if(check==0 && c=='"'){
            found=1;
            check=1; //my permanent flag
        }
        if(found && c=='"' && c!='\r' && c!='\n'){
            count +=1 ;
            if(count==1){
                continue;
            }
        }
        if( (count%2 != 0) && count>1 && c=='"' && c!='\r' && c!='\n'){ 
            line->basePropertyId[i++]=c;
			r_size += 1;
        }
        else{
            if( (c == ',') && (count%2==0) ){  
                break;
            }
            if(c != '"' && c!='\r' && c!='\n'){
                line->basePropertyId[i++]= c;
				r_size += 1;
            }
        }
    }
    line->basePropertyId[i++]='\0';
}

void read_clue_area(dict_t *line, FILE* fp){  //line= node->data
    int c=0, i=0;
	int r_size=0, m_size=MAXKEYSIZE;
    line->ClueSmallArea=malloc(sizeof(char)*MAXKEYSIZE);
    assert(line->ClueSmallArea);
    int check=0, found=0, count=0;
    while ((c = getc(fp)) != EOF){
		
		if(r_size == (m_size-1)){
			m_size *= 2;
			line->ClueSmallArea=realloc(line->ClueSmallArea, sizeof(char)*m_size);
			assert(line->ClueSmallArea);
		}
		
        if(check==0 && c=='"'){
            found=1;
            check=1; //my permanent flag
        }
        if(found && c=='"'){
            count +=1 ;
            if(count==1){
                continue;
            }
        }
        if( (count%2 != 0) && count>1 && c=='"' && c!='\r' && c!='\n'){ 
            line->ClueSmallArea[i++]=c;
			r_size += 1;
        }
        else{
            if( (c == ',') && (count%2==0) ){  
                break;
            }
            if(c != '"' && c!='\r' && c!='\n'){
                line->ClueSmallArea[i++]= c;
				r_size += 1;
            }
        }
    }
    line->ClueSmallArea[i++]='\0';
} 

 void read_trading_name(dict_t *line, FILE* fp){  
    int c=0, i=0;
	
	int r_size=0; int m_size=5;
	line->tradingName=malloc(sizeof(char)*m_size);
    assert(line->tradingName);
    int count=0; int check=0; 
    int found=0;

    while ((c = getc(fp)) != EOF){  
		/* adding new  */
		if(r_size == (m_size-1)){
			m_size *= 2;
			line->tradingName=realloc(line->tradingName, sizeof(char)*m_size);
			assert(line->tradingName);
		} 
		/* end of new */
		
        if(check==0 && c=='"'){
            found=1;
            check=1; //my permanent flag
        }
        if(found && c=='"'){
            count +=1 ;
            if(count==1){
                continue;
            }
        }
        if( (count%2 != 0) && count>1 && c=='"' && c!='\r' && c!='\n'){ 
            line->tradingName[i++]=c;
			r_size += 1;
        }
        else{
            if( (c == ',') && (count%2==0) ){  
                break;
            }
            if(c != '"' && c!='\r' && c!='\n'){
                line->tradingName[i++]= c;
				r_size += 1;
            }
        }
    }
    line->tradingName[i++]='\0';
} 
    

 void read_industry_code(dict_t *line, FILE* fp){ 
    int c=0, i=0;
	int r_size=0, m_size=SIZE; 
    line->industryCode=malloc(sizeof(char)*SIZE);
    assert(line->industryCode);
    int check=0, found=0, count=0;
    while ((c = getc(fp)) != EOF){
		
		if(r_size == (m_size-1)){
			m_size *= 2;
			line->industryCode=realloc(line->industryCode, sizeof(char)*m_size);
			assert(line->industryCode);
		}
		
        if(check==0 && c=='"'){
            found=1;
            check=1; //my permanent flag
        }
        if(found && c=='"'){
            count +=1 ;
            if(count==1){
                continue;
            }
        }
        if( (count%2 != 0) && count>1 && c=='"' && c!='\r' && c!='\n'){ 
            line->industryCode[i++]=c;
			r_size += 1;
        }
        else{
            if( (c == ',') && (count%2==0) ){  
                break;
            }
            if(c != '"' && c!='\r' && c!='\n'){
                line->industryCode[i++]= c;
				r_size += 1;
            }
        }
    }
    line->industryCode[i++]='\0';
}

void read_industry_description(dict_t* line, FILE* fp){ 
    int i=0,c=0, count=0; int check=0; 
    int found=0;
	int r_size=0, m_size=MAXKEYSIZE;
    line->industryDescription=malloc(sizeof(char)*MAXKEYSIZE);
    assert(line->industryDescription);
    while ((c = getc(fp)) != EOF){
		
		if(r_size == (m_size-1)){
			m_size *= 2;
			line->industryDescription=realloc(line->industryDescription, sizeof(char)*m_size);
			assert(line->industryDescription);
		}
		
        if(check==0 && c== '"'){
            found=1;
            check=1;
        }

        if(c=='"' && found){
            count += 1;
        }

        if(found){
            if(count<2 && c=='"'){
                continue;
            }
            if(count >=2 && c==','){
                break;
            }
            
            if(c!='"' && c!='\r' && c!='\n'){
                line->industryDescription[i++]=c;
				r_size += 1;
            }
        }
        else{
            if(c!=',' && c!='\r' && c!='\n'){
                line->industryDescription[i++]=c;
				r_size += 1;
            }
            if(c==','){ 
                line->industryDescription[i++]='\0';
                break;
            }
            
        }
    }
    line->industryDescription[i++]='\0';
}

void read_x(dict_t *line, FILE* fp){ 
    int c=0, i=0;
	int r_size=0, m_size=SIZE;
    line->x=malloc(sizeof(char)*SIZE);
    assert(line->x);
    int check=0, found=0, count=0;
    while ((c = getc(fp)) != EOF){
		
		if(r_size == (m_size-1)){
			m_size *= 2;
			line->x=realloc(line->x, sizeof(char)*m_size);
			assert(line->x);
		}
		
        if(check==0 && c=='"'){
            found=1;
            check=1; //my permanent flag
        }
        if(found && c=='"'){
            count +=1 ;
            if(count==1){
                continue;
            }
        }
        if( (count%2 != 0) && count>1 && c=='"' && c!='\r' && c!='\n'){ 
            line->x[i++]=c;
			r_size += 1;
        }
        else{
            if( (c == ',') && (count%2==0) ){ 
                break;
            }
            if(c != '"' && c!='\r' && c!='\n'){
                line->x[i++]= c;
				r_size += 1;
            }
        }
    }
    line->x[i++]='\0';
    line->X=atof(line->x);
}

void read_y(dict_t *line, FILE* fp){ 
    int c=0, i=0;
	int r_size=0, m_size=SIZE;
    line->y=malloc(sizeof(char)*SIZE);
    assert(line->y);
    int check=0, found=0, count=0;
    while ((c = getc(fp)) != EOF){
		
		if(r_size == (m_size-1)){
			m_size *= 2;
			line->y=realloc(line->y, sizeof(char)*m_size);
			assert(line->y);
		}
		
        if(check==0 && c=='"'){
            found=1;
            check=1; //my permanent flag
        }
        if(found && c=='"'){
            count +=1 ;
            if(count==1){
                continue;
            }
        }
        if( (count%2 != 0) && count>1 && c=='"' && c!='\r' && c!='\n'){ 
            line->y[i++]=c;
			r_size += 1;
        }
        else{
            if( (c == ',') && (count%2==0) ){  
                break;
            }
            if(c != '"' && c!='\r' && c!='\n'){
                line->y[i++]= c;
				r_size += 1;
            }
        }
    }
    line->y[i++]='\0';
    line->Y=atof(line->y);
}

void read_location(dict_t* line, FILE* fp){
    int i=0,c=0, count=0; int found=0; int check=0; 
	int r_size=0, m_size=MAXKEYSIZE;
    line->location=malloc(sizeof(char)*MAXKEYSIZE);
    assert(line->location);
    while ((c = getc(fp)) != EOF && (c!='\n') && (c!='\r')){ 
		
		if(r_size == (m_size-1)){
			m_size *= 2;
			line->location=realloc(line->location, sizeof(char)*m_size);
			assert(line->location);
		}
		
        if(check==0 && c=='"'){
            found=1;
            check=1; //my permanent flag
        }
        if(found && c=='"'){
            count +=1 ;
            if(count==1){
                continue;
            }
        }
        if( (count%2 != 0) && count>1 && c=='"' && c!='\r' && c!='\n'){ 
            line->location[i++]=c;
			r_size += 1;
        }
        else{
            if( (c == ',') && (count%2==0) ){  
                break;
            }
            if(c != '"' && c!='\r' && c!='\n'){
                line->location[i++]= c;
				r_size += 1;
            }
        }
    }
    line->location[i++]='\0';
}
   
       

void read_1_line(dict_t* line, FILE*fp){
    read_cyear(line,fp);
    if(line->censusYear[0] != '\0'){
        read_block_id(line,fp);
        read_property_id(line, fp);
        read_base_property_id(line, fp); 
        read_clue_area(line, fp);
        read_trading_name(line, fp);
        read_industry_code(line, fp);
        read_industry_description(line,fp); //8
        read_x(line, fp); //9
        read_y(line, fp); //10
        read_location(line, fp); //11
    }
}

/* prints record of each attribute */
void print_1_line(dict_t* line, FILE* fp){
    printf("%s\n", line->censusYear); 
    printf("%s\n", line->BlockID);
    printf("%s\n", line->propertyId);
    printf("%s\n", line->basePropertyId);
    printf("%s\n", line->ClueSmallArea);
    printf("c%sc\n", line->tradingName);
    printf("%s\n", line->industryCode);
    printf("%s\n", line->industryDescription); //8
    printf("%s\n", line->x); 
    printf("%s\n", line->y); 
    printf("%s\n", line->location); 
} 