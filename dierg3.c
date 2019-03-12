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
	int fd3,fd4,system_check = 0,m = 0, i = 0,seek_end = 0;
	char full_expression[MAX_SIZE + 1],read_char;
	
	
	
	
	fd3 = open(argv[1],O_RDONLY,S_IRWXU);
	if (fd3 < 0) {
		perror("Open error\n");
		close(fd3);
		_exit(1);
	}
	
	fd4 = open(argv[2],O_WRONLY,S_IRWXU);
	if (fd4 < 0) {
		perror("Open error\n");
		close(fd3);
		close(fd4);
		_exit(1);
	}
	
	while (1) {
		
		
		
		do{
			seek_end = lseek(fd3,0,SEEK_END);
			if (seek_end < 0){
				perror("Lseek error\n");
				close(fd3);
				close(fd4);
				_exit(1);
			}
		}while (seek_end == 0);
		
		system_check = lseek(fd3,0,SEEK_SET);
		if (system_check < 0){
				perror("Lseek error\n");
				close(fd3);
				close(fd4);
				_exit(1);
		}
		
		system_check = read(fd3,full_expression,MAX_SIZE);
		if (system_check < 0){
			perror("Read error\n");
			close(fd3);
			close(fd4);
			_exit(1);
		}
		
		
		system_check = truncate("file3",0);
		if (system_check < 0){
			perror("Truncate error\n");
			close(fd3);
			close(fd4);
			_exit(1);
		}
		
		
		
		
		
		
		m = 0;
		
		for(i = 0;i < MAX_SIZE;i++) {
			read_char = full_expression[i];
			if(read_char == 'q') {
				do {
					seek_end = lseek(fd4,0,SEEK_END);
					if (seek_end < 0){
						perror("Lseek error\n");
						close(fd3);
						close(fd4);
						_exit(1);
					}
				}while(seek_end != 0);
				system_check = write(fd4,"q",1);
				if (system_check < 0) {
					perror("Write error\n");
					close(fd3);
					close(fd4);
					_exit(1);
				}		
				return(0);
			}
			if (read_char == '0') {
				m++;
				do {
					seek_end = lseek(fd4,0,SEEK_END);
					if (seek_end < 0){
						perror("Lseek error\n");
						close(fd3);
						close(fd4);
						_exit(1);
					}
				}while(seek_end != 0);
				system_check = write(fd4,"0",1);
				if (system_check < 0){
					perror("Write error\n");
					close(fd3);
					close(fd4);
					_exit(1);
				}
				break;
				
			}
		}	
		
		if (m == 0) {
			do {
				seek_end = lseek(fd4,0,SEEK_END);
				if (seek_end < 0){
					perror("Lseek error\n");
					close(fd3);
					close(fd4);
					_exit(1);
				}
			}while(seek_end != 0);
			system_check = write(fd4,"1",1);
			if (system_check < 0){
				perror("Write error\n");
				close(fd3);
				close(fd4);
				_exit(1);
			}
		}	
		for(m = 0; m < MAX_SIZE; m++){
			full_expression[m] = '\0';
		}
	}
	
	close(fd3);
	close(fd4);
	return(0);
}