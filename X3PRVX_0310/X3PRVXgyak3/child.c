#include <stdio.h>

int main()
{
    int i;
    for(i = 0; i < 5; i++)
    {
        printf("Horváth Ákos\nR3SZY2\n");
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    char *args[]={"./child",NULL};
    
	int child_pid, wait_pid, status;
	child_pid=fork();
    
	if(child_pid==0)
   	{
   		execvp(args[0],args); 
		printf("ERROR\n");
                exit(1);
	}
		else
    		{
			wait_pid=wait(NULL);
			printf("%d %d",getpid(),wait_pid);
		}
}
