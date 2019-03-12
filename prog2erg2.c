/*this is a program that calculates a logical expression consisting of integers '<=','<','>=','+','-','==','>','&&' and returns a result (1 if the expression is true , 0 if the expression is false) this part of the program
 uses files to contact with its proccesses*/


#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>





#define MAX_SIZE 80

int main (int argc,char* argv[]) {
	char read_char;
	char full_expression[MAX_SIZE + 1],end_char[2];
	int i = 0,system_check = 0,proccess1 = 0,proccess2 = 0,proccess3 = 0,fd1,fd2,fd3,fd4,seek_end = 0,m = 0;
	
	
	
	
	
	/*open files*/
	fd1 = open("file1",O_CREAT|O_WRONLY,S_IRWXU);
	if (fd1 < 0) {
		perror("Open error\n");
		_exit(1);
	}
	
	fd2 = open("file2",O_CREAT,S_IRWXU);
	if (fd2 < 0) {
		perror("Open error\n");
		close(fd1);
		_exit(1);
	}
	
	close(fd2);
	
	fd3 = open("file3",O_CREAT,S_IRWXU);
	if (fd3 < 0) {
		perror("Open error\n");
		close(fd1);
		_exit(1);
	}
	
	close(fd3);
	
	fd4 = open("file4",O_CREAT|O_RDONLY,S_IRWXU);
	if(fd4<0) {
		perror("Open error\n");
		close(fd1);
		_exit(1);
	}
	
	
	proccess1 = fork();
	if (proccess1 < 0) {
		perror("Fork error\n");
		close(fd1);
		close(fd4);
		_exit(1);
	}
		
	if(proccess1 == 0){
		
		close(fd1);
		close(fd4);
		system_check = execlp("./dierg1","./dierg1","file1","file2",NULL);
		
		if (system_check < 0) {
			perror("Execlp error\n");
			_exit(1);
			
		}
	}
	
	
	
	proccess2 = fork();
	if (proccess2 < 0) {
		perror("Fork error\n");
		close(fd1);
		close(fd4);
		_exit(1);
	}
	
	if(proccess2 == 0){
		close(fd1);
		close(fd4);
		system_check = execlp("./dierg2","./dierg2","file2","file3",NULL);
		if (system_check < 0) {
			perror("Execlp error\n");
			_exit(1);
			
		}
	}
	
	
	
	proccess3 = fork();
	if (proccess3 < 0) {
		perror("Fork error\n");
		close(fd1);
		close(fd4);
		_exit(1);
	}
	
	if(proccess3 == 0){
		close(fd1);
		close(fd4);
		system_check = execlp("./dierg3","./dierg3","file3","file4",NULL);
		if (system_check < 0) {
			perror("Execlp error\n");	
			_exit(1);
		}
		
	}
	
	

	while (1) {
		
		
		
		printf("Please enter logical expression or press q to quit: ");
		i = 0;
		do {
			read_char = getchar();  /*delete the space characters of the given expression*/
			if(read_char != ' '){ 
				full_expression[i] = read_char;
				i++;
			}
			
		} while (read_char != '\n' && i < MAX_SIZE);
		
		
			
		
	
		
		if (full_expression[0] == 'q') {/*if q is given the main proccess  passes the q to the next proccess*/
			do {
				seek_end = lseek(fd1,0,SEEK_END);
				if (seek_end < 0){
					perror("Lseek error\n");
					close(fd1);
					close(fd4);
					_exit(1);
				}
			}while(seek_end != 0);
				
			
			system_check = write(fd1,"q",1);
			if (system_check < 0) {
				perror("Write error\n");
				close(fd1);
				close(fd4);
				_exit(1);
			}
	
		}
		
		
		
		do {
			seek_end = lseek(fd1,0,SEEK_END);
			if (seek_end < 0){
				perror("Lseek error\n");
				close(fd1);
				close(fd4);
				_exit(1);
			}
		} while(seek_end != 0);
		
		
		system_check = write(fd1,full_expression,strlen(full_expression));
		if (system_check < 0) {
			perror("Write error\n");
			close(fd1);
			close(fd4);
			_exit(1);
		}
		
		do {
			seek_end = lseek(fd4,0,SEEK_END);
			if (seek_end < 0){
				perror("Lseek error\n");
				close(fd1);
				close(fd4);
				_exit(1);
			}
		} while(seek_end == 0);
		
		system_check = lseek(fd4,0,SEEK_SET);
		if (system_check < 0) {
			perror("Lseek error\n");
			close(fd1);
			close(fd4);
			_exit(1);
		}
		
		system_check = read(fd4,end_char,1);
		if (system_check < 0) {
			perror("Read error\n");
			close(fd1);
			close(fd4);
			_exit(1);
		}
		end_char[1] = '\0';
		
		system_check = truncate("file4",0);
		if (system_check < 0) {
			perror("Truncate error\n");
			close(fd1);
			close(fd4);
			_exit(1);
		}		
		
		if (end_char[0] == 'q') break; /*if q is read from the last proccess,the main proccess terminates*/
		else printf("Result: %c\n",end_char[0]);
		
		for(m = 0; m < MAX_SIZE; m++){
			full_expression[m] = '\0';
		}
				
		
		
		
	}
	
	close(fd1);
	close(fd4);
	waitpid(proccess1,NULL,0);
	waitpid(proccess2,NULL,0);
	waitpid(proccess3,NULL,0);
	unlink("file1");
	unlink("file2");
	unlink("file3");
	unlink("file4");
	return(0);
}