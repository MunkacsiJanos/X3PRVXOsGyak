#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void megoldas(struct egyenlet* e);

int main()
{
    key_t key = ftok("inputfile.txt", 123);
    printf("key: %x\n",key);
   
    int msgid = msgget(key, 0666|IPC_CREAT);

    printf("Várakozás az üzenetre...\n");
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    struct egyenlet egyenlet1 = message.msg;
    struct egyenlet tomb[egyenlet1.egyenletekszama];
    tomb[0] = egyenlet1;

    for(int i = 1; i < sizeof(tomb)/sizeof(struct egyenlet); i++)
    {
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        tomb[i] = message.msg;
    }
  

    FILE* fptr;
    fptr = fopen("outputfile.txt","w");  
    if(fptr == NULL)
    {
        perror("Hiba fájl megnyitásakor!");
         exit(1);    
    }

    for(int i = 0; i < sizeof(tomb)/sizeof(struct egyenlet); i++)
    {
        megoldas(&tomb[i]);
        if(tomb[i].vanmegoldas==0)
        {
            printf("%f %f %f nincs megoldás\n", tomb[i].a, tomb[i].b, tomb[i].c);
            fprintf(fptr,"%f %f %f nincs megoldás\n", tomb[i].a, tomb[i].b, tomb[i].c);
        }
        else
        {
            printf("%f %f %f %f %f\n", tomb[i].a, tomb[i].b, tomb[i].c, tomb[i].gyok1, tomb[i].gyok2);
            fprintf(fptr,"%f %f %f %f %f\n", tomb[i].a, tomb[i].b, tomb[i].c, tomb[i].gyok1, tomb[i].gyok2);
        }

    }

    return 0;
}

void megoldas(struct egyenlet* e)
{
    float d = e->b * e->b - 4 * e->a * e->c;
      
    if(d < 0)
    {
        e->vanmegoldas = 0;
    }
    else if(d==0)
    {
        e->gyok1 = -e->b /(2* e->a);
        e->gyok2 = -e->b /(2* e->a);
    }
    else
    {
      
        e->gyok1 = ( -e->b + sqrt(d)) / (2* e->a);
        e->gyok2 = ( -e->b - sqrt(d)) / (2* e->a);
    }
}