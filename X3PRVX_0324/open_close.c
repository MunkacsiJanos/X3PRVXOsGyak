#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{
    char buffer[20];
    int bufferLength;
    int fileDescriptor;
    int writeInfo;
    int seekInfo;
    int readInfo;

    fileDescriptor = open("X3PRVX.txt",O_RDWR);
    if (fileDescriptor == -1)
    {
        perror("open() hiba:");
        exit(fileDescriptor);
    }

    printf("File Descriptor értéke: %d\n", fileDescriptor);

    seekInfo = lseek(fileDescriptor, 0, SEEK_SET);
    if (seekInfo == -1)
    {
        perror("Pozícionálási hiba");
        exit(seekInfo);
    }

    printf("A kurzor pozicioja: %d\n", seekInfo);

    readInfo = read(fileDescriptor, buffer, 15);

    if (readInfo == -1){
        perror("Az olvasás nem volt sikeres:");
        exit(seekInfo);
    }

    printf("A read() értéke: %d\n", readInfo);
    printf("A beolvasott érték: %s", buffer);

    strcpy(buffer, "ASD123");
    bufLength = strlen(buffer);
    writeInfo = write(fileDescriptor, buffer, bufferLength);

    if (writeInfo == -1)
    {
        perror("Hiba írás közben");
        exit(writeInfo);
    }
    printf("A write()-al beirt byte-ok szama: %d\n", writeInfo);

    return 0;
}