#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#define MAX 500
#define	DOOR 1
#define BUZZ 0
#define BUTTON 2

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
    printf("READ DATABASS (uuid.txt)\n");
    for(temp=0;temp<MAX;temp++)
    {
        fscanf(data,"%s",x[temp].uuid);
    }

    for(temp=0;temp<MAX;temp++)
    {
        printf("%s\n",x[temp].uuid);
    }

    printf(">> Member Load\n");
    fclose(data);
    return 0;
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
    pinMode (DOOR, OUTPUT) ;
    digitalWrite (DOOR, LOW) ;
    int fd , i=0 ,j,found=0;
    FILE * uuid ;
    char temp[15],ch[15];

    printf ("Raspberry Pi LockDoor System\n") ;

    if ((fd = serialOpen ("/dev/ttyUSB0", 9600)) < 0)
    {
        printf ("Unable to open serial device\n") ;
        return 1 ;
    }
    serialFlush(fd);

    if (wiringPiSetup () == -1)
    {
        printf ("Unable to start wiringPi\n") ;
        return 1 ;
    }

    load();
    while(1)
    {
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
                accessdenied();
            }
        }
    }
    return 0 ;
}


