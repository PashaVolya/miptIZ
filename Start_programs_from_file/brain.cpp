#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc,char *argv[],char *envp[]) { 
	pid_t pid[10];
    FILE* fd;
    fd = fopen("/home/pavel/kek/test/programs.txt","r"); 
    int i; 
    int time[10];
    char way[35][35];
	i=0;
	while(!feof(fd)) 
                {
		fscanf(fd,"%d",&time[i]);
		fscanf(fd,"%s",way[i]);
                i++;
                };
        fclose(fd);
	i--; 
	printf("Всего %d программы: \n",i);
	int k,n; 
	for (k = 1;k <i;k++) pid[k] = 0; 
	pid[0] = fork();
	n = 0;
	for (k = 1;k <i;k++)
		 if (pid[k-1] != 0) 
			{
			 pid[k] = fork(); 
			n = k;
			};
	
	if (pid[i-1] > 0)	
	 {
		int sys;
		for (k = 0;k < i;k++) 
			waitpid(pid[k],&sys,0);
	}
	 else 
	{
		sleep(time[n]);
		printf("I was sleeping %d seconds, my way -%s \n",time[n],way[n]);
		execlp(way[n],way[n],NULL);	
	} 
	return 0;
	}
