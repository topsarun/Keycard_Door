#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#define MAX 500
#define	DOOR 1
#define BUZZ 0
#define BUTTON 2
#define BUTTON_ADD_CARD 4
#define LED_STATUS 27

struct id
{
    char uuid[15];
    int ch;
};
struct id x[MAX];

load()
{
    int temp = 0 ,ch=0 ;
    FILE *data;
    data = fopen("uuid.txt","r");
    printf("READ DATABASE (uuid.txt)\n");
    for(temp=0;temp<MAX;temp++)
    {
        fscanf(data,"%s",x[temp].uuid);
    }

    //for(temp=0;temp<MAX;temp++)
    //{
        //printf("%s\n",x[temp].uuid);
    //}

    printf(">> Member Load\n");
    fclose(data);
    return 0;
}


addCardSound()
{
    pinMode (BUZZ, OUTPUT) ;
    delay (100);
    digitalWrite(BUZZ, HIGH);
    delay (500);
    digitalWrite(BUZZ, LOW);
    return 0;
}
addCard(char st[])
{

    int temp = 0;
    FILE *data;
    if(digitalRead(BUTTON_ADD_CARD))
    {
        printf("Write DATABASE (uuid.txt) %s\n", st);
    	data = fopen("uuid.txt","a");
        fprintf(data,"%s\n",st);
        printf("addCard %s\n", st);
        fclose(data);
		load();
        addCardSound();
        return 0;
    }

    return 1;
}

access()
{
    pinMode (DOOR, OUTPUT) ;
    pinMode (BUZZ, OUTPUT) ;
    delay (100);
    digitalWrite (BUZZ, HIGH);
    delay (120);
    digitalWrite (BUZZ, LOW);
    digitalWrite (DOOR, HIGH) ;
    delay (5000) ;
    digitalWrite (BUZZ, HIGH);
    delay (120);
    digitalWrite (BUZZ, LOW);
    delay (100);
    digitalWrite (BUZZ, HIGH);
    delay (120);
    digitalWrite (BUZZ, LOW);
    digitalWrite (DOOR, LOW) ;
    return 0;
}

accessdenied()
{
    pinMode (BUZZ, OUTPUT) ;
    delay (100);
    digitalWrite(BUZZ, HIGH);
    delay (150);
    digitalWrite(BUZZ, LOW);
    delay (50);
    digitalWrite(BUZZ, HIGH);
    delay (130);
    digitalWrite(BUZZ, LOW);
    delay (1000);
    return 0;
}

readbutton()
{
    pinMode (BUTTON, INPUT) ;
    int s = digitalRead(BUTTON);
    if(s == 1)
    {
        access() ;
    }
}


int main (void)
{
    printf ("Raspberry Pi LockDoor System\n") ;

    int fd , i=0 ,j,found=0;

    if ((fd = serialOpen ("/dev/ttyUSB0", 9600)) < 0)
    {
        printf ("Unable to open serial device\n") ;
        return 1 ;
    }

    if (wiringPiSetup () == -1)
    {
        printf ("Unable to start wiringPi\n") ;
        return 1 ;
    }
    pinMode (27, OUTPUT) ;
	pinMode(BUTTON_ADD_CARD, OUTPUT);

    pinMode (DOOR, OUTPUT) ;
    digitalWrite (DOOR, LOW) ;
    FILE * uuid ;
    char temp[15],ch[15];

    load();
	int loop = 10;
	while (loop > 0) 
	{
	    digitalWrite (27, 0) ;
		delay(500);
	    digitalWrite (27, 1) ;
		delay(500);
		loop--;
	}
    while(1)
    {
		serialFlush(fd);
        readbutton();
        fflush (stdout) ;
        fflush (stdin) ;
        if(serialDataAvail(fd)>0)
        {
            j=0; found=0;
            for(i=0;i<14;i++)
            {
                temp[i] = serialGetchar (fd) ;
                if(temp[i]>='0'&&temp[i]<='9')
                {
                    ch[j++] = temp[i];
                }
            }
            ch[j] = '\0' ;
            for(i=0;i<MAX;i++)
            {
                if(strcmp(ch,x[i].uuid)==0)
                {
                    found ++;
                }
            }
            if(found>0)
            {
                printf("%s found\n",ch);
                access();
            }
            else
            {
                printf("%s not found!\n",ch);
				if (addCard(ch))
                	accessdenied();
            }
        }
    }
    return 0 ;
}
