#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<stdlib.h>
#include<ctype.h>



#define MAX_SIZE 80


int main (int argc,char* argv[]) {
	int m = 0, i = 0;
	char full_expression[MAX_SIZE + 1],read_char;
	
	

	while (1) {
		
		for(m = 0; m <= MAX_SIZE; m++){
			full_expression[m] = '\0';
		}
		
		scanf("%s",full_expression);
		fflush(NULL);
		
		
		
		
		m = 0;
		
		for(i = 0;i < MAX_SIZE;i++) {
			read_char = full_expression[i];
			if(read_char == 'q') {
				
				printf("%c",read_char);
				fflush(NULL);
				return(0);
			}
			if (read_char == '0') {
				m++;
				
				printf("%c",'0');
				fflush(NULL);
				break;
				
			}
		}	
		
		if (m == 0) {
			
			printf("%c",'1');
			fflush(NULL);
			
		}	
		for(m = 0; m < MAX_SIZE; m++){
			full_expression[m] = '\0';
		}
	}
	
	
	return(0);
}