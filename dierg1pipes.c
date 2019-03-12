#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<stdlib.h>
#include<ctype.h>



#define MAX_SIZE 80



int main(int argc,char* argv[]) {
	int i = 0,check_digit,j = 0,k = 0,number1 = 0,number2 = 0,result = 0,l = 0,m = 0,n = 0,w = 0;
	char read_char;
	char resultstr[MAX_SIZE + 1];
	char digit1[MAX_SIZE + 1];
	char digit2[MAX_SIZE + 1];
	char full_expression[MAX_SIZE + 1], new_expression[MAX_SIZE + 1];

	

	
		
		
	
	while(1) {
		
		for(m = 0; m <= MAX_SIZE; m++){
			full_expression[m] = '\0';
		}
		
		
		scanf("%s",full_expression);
		fflush(NULL);
			
		
		
			
		for(i = 0;i < MAX_SIZE;i++) {
			read_char = full_expression[i];
			if(read_char == 'q') {
				
				
				printf("%c",read_char);
				fflush(NULL);
				return(0);
			}
			if (read_char == '+' || read_char == '-') {
				full_expression[i] = ' ';
				do {
					
					i++;
					check_digit = full_expression[i];
					if(isdigit(check_digit)){
						digit1[j] = check_digit;
					
						j++;
					}
				} while(isdigit(check_digit));
					
				digit1[j] = '\0';
				
				i = i - j - 1;
					
				w = i;
					
				do {
					i--;
					check_digit = full_expression[i];
				} while(isdigit(check_digit) && i > 0);
					
				if (isdigit(full_expression[i])) {
						
					for(; i < w; i++) {
						digit2[k] = full_expression[i];
						k++;
					}
						
				}
					
				else {
						
					for(i = i + 1; i < w; i++) {
						digit2[k] = full_expression[i];
						k++;
					}
						
				}
					
				digit2[k] = '\0';
				i = i - strlen(digit2);
				k = 0;
					
				sscanf(digit1,"%d",&number1);
				sscanf(digit2,"%d",&number2);
				
				if (read_char == '+'){
					result = number1 + number2;
				}
				
				if (read_char == '-') {
					result = number2 - number1;
				}
				
				sprintf(resultstr,"%d",result);
				
				for(l = 0;l < (int)strlen(resultstr);l++) {
					full_expression[i] = resultstr[l];
					i++;
				}
				
				while(1) {
					check_digit = full_expression[i];
					
					if (isdigit(check_digit) || full_expression[i] == ' ') {
						full_expression[i] = ' ';
					i++;
					}
					else break;
					
				}

				j = 0;
				w = 0;
					
				for(m = 0; m < MAX_SIZE;m++) {
					
					if (full_expression[m] != ' ') {
						new_expression[n] = full_expression[m];
						n++;
					}
						
				}
					
				new_expression[n] = '\0';
				n = 0;
				full_expression[0] = '\0';
				strcpy(full_expression,new_expression);
				
				for(m = strlen(new_expression);m < MAX_SIZE;m++) {
						full_expression[m] = '\0';
				}
					
				full_expression[strlen(new_expression)+1] = '\0';
					
				for(i = 0; i <= MAX_SIZE; i++) {
					new_expression[i] = '\0';
				}
					
				new_expression[strlen(new_expression)+1] = '\0';
					
				i = 0;
				digit1[0] = '\0';
				digit2[0] = '\0';
				
					
			}
			
		}

		printf("%s\n",full_expression);
		fflush(NULL);
		
			
		for(m = 0; m <= MAX_SIZE; m++) {
			full_expression[m] = '\0';
		}

		
		
	}
	
	return(0);
	
}