#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void handleSignal();

int main()
    {
        signal(SIGINT, handleSignal); //A handleSignal-nak átadom az Interrupt Signal-okat, hogy kezelje le őket ha érkeznek.
        signal(SIGQUIT, handleSignal); //A Quit Signal-t átadom ugyan úgy a handleSignal-nak
            
            for (int i=0; i<10; i++)
            { //Várunk 10-szer a felhasználóra
	            printf("Varunk...\n");
	            pause();
            }
return 0;
}

//Hangup Signal 1-essel tér vissza
//Interrupt Signal 2-essel tér vissza
//A Quit Signal 3-assal tér vissza
//Az Illegal Instruction Signal 4-essel tér vissza
//A Trace Trap Signal 5-össel tér vissza
//Az Abort Signal 6-ossal tér vissza

void handleSignal(int sig){
char desc[50];
switch(sig){// A kapot jel értéke alapján a switch kiválasztja a megfelelő case-t és azt futtatja tovább
	case 1: {
	strcpy(desc, "Hangup Signal");
	break;
	}

	case 2: {
	    strcpy(desc, "Interrupt Signal");
	    signal(SIGINT, SIG_DFL);//Az interruptot az eredeti állapotára állítjuk
	    printf("\nA CTRL + C most már ki fogja léptetni a programból!");
	break;
	}

	case 3: {
	    strcpy(desc, "Quit Signal");
	break;
	}

	case 4: {
	    strcpy(desc, "Illegal Instruction Signal");
	break;
	}

	case 5: {
	    strcpy(desc, "Trace Trap Signal");
	break;
	}

	case 6: {
	    strcpy(desc, "Abort Signal");
	break;
	}
}
    printf("\nAz elkapott jel: %s\n", desc);
}
