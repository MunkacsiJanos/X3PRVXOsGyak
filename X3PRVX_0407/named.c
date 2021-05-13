#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define MSIZE 128


int main()
{
    char inBuffer[MSIZE];
    int pid, fileDesc;
    char input[] = "Munkácsi János";
    char * fifo = "/tmp/x3prvx";
    mkfifo(fifo, 0666);
    pid = fork();

        if (pid < 0)
	     exit(2);


    if (pid == 0)
    {
	    printf("Írás...\n");
	    fileDesc = open(fifo, O_WRONLY);
	    write(fileDesc, input, strlen(input)+1);
	    printf("Sikeres írás\n");
    }

     else if (pid > 0 )
        {
	        fileDesc = open(fifo, O_RDONLY);
	        read(fileDesc, inBuffer, strlen(input)+1);
	        printf("Üzenet tartalma: %s\n", inBuffer);
	        close(fileDesc);
        }

    return 0;
}
