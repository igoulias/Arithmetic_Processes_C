/*the part of the program that the contact between the proccesses is happening via pipes*/


#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>



#define MAX_SIZE 80



int main(int argc,char* argv[]) {
	
	char read_char;
	char full_expression[MAX_SIZE + 1],end_char[2];
	int fd1[2],fd2[2],fd3[2],fd4[2],system_check = 0,proccess1 = 0,proccess2 = 0,proccess3 = 0,i = 0,m = 0;
	
	
	
	
	system_check = pipe(fd1);/*create pipes*/
	if (system_check < 0) {
		perror("Pipe error");
	}
	
	system_check = pipe(fd2);
	if (system_check < 0) {
		perror("Pipe error");
		close(fd1[0]);
		close(fd1[1]);
		return(1);
	}
	
	system_check = pipe(fd3);
	if (system_check < 0) {
		perror("Pipe error");
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		return(1);
	}
	
	system_check = pipe(fd4);
	if (system_check < 0) {
		perror("Pipe error");
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		close(fd3[0]);
		close(fd3[1]);
		return(1);
	}
	
	proccess1 = fork();
	if (proccess1 < 0) {
		perror("Fork error\n");
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		close(fd3[0]);
		close(fd3[1]);
		close(fd4[0]);
		close(fd4[1]);
		_exit(1);
	}
	
	
	if(proccess1 == 0){
		dup2(fd1[0],0);
		dup2(fd2[1],1);
		
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		close(fd3[0]);
		close(fd3[1]);
		close(fd4[0]);
		close(fd4[1]);
		
		system_check = execlp("./dierg1pipes","./dierg1pipes",NULL);
		
		if (system_check < 0) {
			perror("Execlp error\n");
			_exit(1);
			
		}
	}
	
	close(fd1[0]);
	close(fd2[1]);
	
	proccess2 = fork();
	if (proccess2 < 0) {
		perror("Fork error\n");
		close(fd1[1]);
		close(fd2[0]);
		close(fd3[0]);
		close(fd3[1]);
		close(fd4[0]);
		close(fd4[1]);
		_exit(1);
	}
	
	
	if(proccess2 == 0){
		dup2(fd2[0],0);
		dup2(fd3[1],1);
		
		close(fd1[1]);
		close(fd2[0]);
		close(fd3[0]);
		close(fd3[1]);
		close(fd4[0]);
		close(fd4[1]);
		
		system_check = execlp("./dierg2pipes","./dierg2pipes",NULL);
		if (system_check < 0) {
			perror("Execlp error\n");
			_exit(1);
			
		}
	}
	
	close(fd2[0]);
	close(fd3[1]);
	
	
	
	proccess3 = fork();
	if (proccess3 < 0) {
		perror("Fork error\n");
		close(fd1[1]);
		close(fd3[0]);
		close(fd4[0]);
		close(fd4[1]);
		_exit(1);
	}
	
	if(proccess3 == 0){
		dup2(fd3[0],0);
		dup2(fd4[1],1);
		
		
		close(fd3[0]);
		close(fd4[1]);
		close(fd1[1]);
		close(fd4[0]);
		
		
		system_check = execlp("./dierg3pipes","./dierg3pipes",NULL);
		if (system_check < 0) {
			perror("Execlp error\n");	
			_exit(1);
		}
		
	}
	
	close(fd3[0]);
	close(fd4[1]);
	
	while (1) {
		
		for(m = 0; m <= MAX_SIZE; m++) {
			full_expression[m] = '\0';
		}
		
		
		printf("Please enter logical expression or press q to quit: ");
		i = 0;
		do {
			read_char = getchar();
			if(read_char != ' '){
				full_expression[i] = read_char;
				i++;
			}
			
		} while (read_char != '\n' && i < MAX_SIZE);
		full_expression[i] = '\0';
		
			
		
	
		
		if (full_expression[0] == 'q') {
			
			
			
			system_check = write(fd1[1],"q",1);
			if (system_check < 0) {
				perror("Write error\n");
				close(fd1[1]);
				close(fd4[0]);
				_exit(1);
			}
	
		}
		
		
		
		
		system_check = write(fd1[1],full_expression,strlen(full_expression));
		if (system_check < 0) {
			perror("Write error\n");
			close(fd1[1]);
			close(fd4[0]);
			_exit(1);
		}
		
		
		
		system_check = read(fd4[0],end_char,1);
		if (system_check < 0) {
			perror("Read error\n");
			close(fd1[1]);
			close(fd4[0]);
			_exit(1);
		}
		end_char[1] = '\0';
		
		
		if (end_char[0] == 'q') break;
		else printf("Result: %c\n",end_char[0]);
		
		for(m = 0; m <= MAX_SIZE; m++){
			full_expression[m] = '\0';
		}
				
		
		
		
	}
	
	close(fd1[1]);
	close(fd4[0]);
	waitpid(proccess1,NULL,0);
	waitpid(proccess2,NULL,0);
	waitpid(proccess3,NULL,0);
	return(0);
}