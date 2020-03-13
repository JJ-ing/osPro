#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    long int ret=syscall(332,"test.c","new.c");
    if(ret==1){
    	printf("open source file error!\n");
    	exit(-1);
	}
	else if(ret==2){
    	printf("open destination file error!\n");
    	exit(-1);		
	}
	else if(ret==3 || ret==4){
		printf("error when copy file!\n");
    	exit(-1);
	}
	else{
		printf("copy success!\n");
	}
    
    return 0;
}
