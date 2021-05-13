#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MSIZE 128

int main()
{
    char inBuffer[MSIZE];
    int p[2], nbytes, pid;
        if (pipe(p) < 0)
        {
	        perror("Pipe hiba");
	        exit(1);
           }
                pid = fork();

    if (pid < 0)
    {
	    exit(2);
    }
        
if (pid == 0){
	printf("Írás...\n");
	write(p[1], "MJ X3PRVX", MSIZE);
	printf("Sikeresen írás\n");
}

else if (pid > 0 ){
	wait(NULL);
	printf("Kiolvasás...\n");
	read(p[0], inBuffer, MSIZE);
	printf("Üzenet tartalma: %s\n", inBuffer);
	printf("Kiolvasás kész\n");
}

return 0;
}
