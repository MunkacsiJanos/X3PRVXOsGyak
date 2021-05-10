#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

struct egyenlet
{
    float a;
    float b;
    float c;
    float gyok1;
    float gyok2;
    int vanmegoldas;
    int egyenletekszama;
};

struct msg_buffer
{
    long mtype;
    struct egyenlet msg;
}message;

int main()
{
    key_t key = ftok("inputfile.txt", 123);
    printf("Key: %x\n",key);    

    int msgid = msgget(key, 0666|IPC_CREAT);
    message.mtype = 1;

    FILE* fptr;
    fptr = fopen("inputfile.txt","r");
    if(fptr == NULL)
    {
        perror("Hiba fájl megnyitásakor!");
        exit(1);    
    }
   
    int szamitasokszama = 0;
    fscanf(fptr,"%d",&szamitasokszama);

    struct egyenlet tomb[szamitasokszama];
    printf("Egyenletek száma: %d\n", szamitasokszama);

    for(int i = 0; i < szamitasokszama; i++)
    {
        fscanf(fptr,"%f %f %f", &tomb[i].a, &tomb[i].b, &tomb[i].c);
        tomb[i].gyok1 = 0;
        tomb[i].gyok2 = 0;
        tomb[i].vanmegoldas = 1;
        tomb[i].egyenletekszama = szamitasokszama;
    }

    fclose(fptr);

    for(int i = 0; i < sizeof(tomb)/sizeof(struct egyenlet); i++)
    {
        message.msg = tomb[i];
        msgsnd(msgid, &message, sizeof(message), 0);
    }

    printf("Üzenet elküldve\n");

    return 0;
}