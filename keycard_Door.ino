#include <SoftwareSerial.h>
SoftwareSerial RFID(8, 1);
int data1 = 0;
int ok = -1;
int yes = 4;
int no = 12  ;
int button = 7 ;
//ADDCARD>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*int tag0[14] = {63,230,230,230,76,153,102,153,50,153,76,158,61,126}; //Aj_PANYA DO NOT DEL>>>>>>>>>>>>>
//ROBOT member
int tag1[14] = {63,230,230,166,76,153,76,51,100,155,50,202,214,242};//TAG>>>>NOPPOL(first)
int tag2[14] = {63,230,230,102,153,50,153,101,203,30,50,202,214,242};//TAH>>>>SARUN
int tag3[14] = {63,102,102,38,166,153,153,100,201,26,30,202,214,242}; //TAG>>>NUT*/
//end>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int newtag[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//Start Nut Code
int n = 4; // all = ?
int password[4] = {97,98,99,100} , temppass[4];
int tag[60][14] = {
                      {63,230,230,230,76,153,102,153,50,153,76,158,61,126}//A.Panya
                     ,{63,230,230,166,76,153,76,51,100,155,50,202,214,242} //Nop
                     ,{63,230,230,102,153,50,153,101,203,30,50,202,214,242} //TOP
                     ,{63,102,102,38,166,153,153,100,201,26,30,202,214,242} //Nut
                     ,{63,102,102,38,166,153,153,102,206,50,54,202,214,242} //NUT_Head
                     ,{63,230,230,230,166,153,153,101,203,46,34,202,214,242} //TAR
                     ,{63,102,102,38,166,153,51,76,153,102,206,202,214,242} //Chaichana_1
                     ,{63,230,230,166,38,102,102,153,50,50,166,158,61,126} //Chaichana_2
                     ,{63,102,102,38,166,153,50,50,204,153,51,121,235,242} //Camp
                     ,{63,102,102,38,166,153,50,101,141,58,50,202,214,242} // Dos
                     ,{63,102,102,38,166,153,51,100,141,34,30,202,214,242} // Pang
                     ,{63,102,102,38,166,153,50,99,143,54,38,202,214,242} // Pang2
                     ,{63,102,102,38,166,153,204,50,38,38,153,60,61,126} //view
                     ,{63,102,102,38,166,153,51,100,155,26,34,202,214,242} //ploy
                     ,{63,102,102,38,166,153,50,230,204,204,51,121,235,242} //Tong
                     ,{63,102,102,38,166,153,50,153,204,51,103,229,214,242} //Jui
                     ,{63,102,102,38,166,153,153,99,202,50,62,202,214,242} //Vee
                     ,{63,102,102,38,166,153,50,102,151,46,50,202,214,242} //Nine
                     ,{63,102,102,38,166,153,153,102,199,34,38,202,214,242} //Fon
                     ,{63,230,230,230,230,204,204,166,102,102,166,158,61,126} //P
                     
                     //START TAG1-30
                     ,{63,230,230,230,76,166,204,51,101,147,58,202,214,242} //TAG 1
                     ,{63,230,230,166,204,51,50,100,143,58,26,202,214,242} //TAG 2
                     ,{63,230,230,230,76,102,153,76,166,204,153,121,245,242} //TAG 3
                     ,{63,230,230,230,76,166,153,76,153,38,153,60,61,126} //TAG 4
                     ,{63,230,230,166,204,51,100,159,54,42,62,202,214,242} //TAG 5
                     ,{63,230,230,230,76,166,153,153,100,205,58,202,214,242} //TAG 6
                     ,{63,230,230,166,204,51,76,166,153,102,166,158,61,126} //TAG 7
                     ,{63,230,230,166,204,51,204,230,76,38,166,158,61,126} //TAG 8
                     ,{63,230,230,166,204,51,50,50,51,51,166,158,61,126} //TAG 9
                     ,{63,230,230,166,204,51,204,51,76,51,153,121,245,242} //TAG 10
                     ,{63,230,230,230,76,102,153,51,50,103,143,202,214,242} //TAG 11
                     ,{63,230,230,230,76,38,153,51,51,204,76,158,61,126} //TAG 12
                     ,{63,230,230,230,76,166,153,51,51,101,145,202,214,242} //TAG 13
                     ,{63,230,230,230,76,166,153,51,204,50,50,121,235,242} //TAG 14
                     ,{63,230,230,230,76,166,153,50,102,149,50,202,214,242} //TAG 15
                     ,{63,230,230,230,76,102,153,153,103,205,42,202,214,242} //TAG 16
                     ,{63,230,230,230,76,166,153,153,76,153,50,121,235,242} //TAG 17 
                     ,{63,230,230,230,76,230,153,153,100,202,38,202,214,242} //TAG 18
                     ,{63,230,230,230,76,102,153,51,100,149,26,202,214,242} //TAG 19
                     ,{63,230,230,230,76,102,153,50,103,147,58,202,214,242} //TAG 20
                     ,{63,230,230,166,204,51,50,99,141,30,58,202,214,242} //TAG 21
                     ,{63,230,230,166,204,51,50,51,100,151,58,202,214,242} //TAG 22 
                     ,{63,230,230,166,204,51,50,101,155,26,42,202,214,242} //TAG 23
                     ,{63,230,230,166,204,51,50,100,141,34,26,202,214,242} //TAG 24
                     ,{63,230,230,230,153,50,103,141,26,42,50,202,214,242} //TAG 25
                     ,{63,230,230,230,153,50,153,103,200,26,50,202,214,242} //TAG 26
                     ,{63,230,230,230,153,50,51,50,103,145,50,202,214,242} //TAG 27
                     ,{63,230,230,230,153,50,51,100,143,38,42,202,214,242} //TAG 28
                     ,{63,230,230,230,153,50,102,155,42,50,62,202,214,242} //TAG 29
                     ,{63,230,230,230,153,50,102,141,50,50,50,202,214,242} //TAG 30
                     
                     ,{63,230,230,102,153,50,102,159,58,34,46,202,214,242} //MOS
                     ,{63,230,230,230,166,153,51,99,153,38,38,202,214,242} //POND
                     /*,{63,102,102,38,166,153,50,100,155,62,54,202,214,242} //ฮ้อ
                     ,{63,102,102,38,166,153,50,50,204,153,76,158,61,126}  *///ณัฎฐ์ศรณ์
                     //END TAG
                 }; // ,tagX
//End Nut Code
void setup()
{
  //start TOP code
  delay(1000);
  Serial.begin(9600);
  //while(!Serial); //Serial debug
  delay(500);
  RFID.begin(9600);
  pinMode(yes, OUTPUT);
  pinMode(no, OUTPUT);
  pinMode(button, INPUT);
  Serial.println("Ready!!");
}
boolean comparetag(int aa[14], int bb[14])
{
  boolean ff = false;
  int fg = 0;
  for (int cc = 0 ; cc < 14 ; cc++)
  {
    if (aa[cc] == bb[cc])
    {
      fg++;
    }
  }
  if (fg == 14)
  {
    ff = true;
  }
  return ff;
}
//startCheckCardValidity>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void checkmytags()
{
  ok = 0;
  for(int i=0;i<sizeof(tag)/sizeof(int[14]);i++)
  {
    boolean ff = false;
    int fg = 0;
    for (int cc = 0 ; cc < 14 ; cc++)
    {
      if (newtag[cc] == tag[i][cc])
      {
        fg++;
      }
    }
    if (fg == 14)
    {
      ff = true;
    }
    if(ff)
      ok++;
  }
}
//endCheckCardValidity>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void readTags()
{
  ok = -1;
  if (RFID.available() > 0) 
  {
    delay(100);
    for (int z = 0 ; z < 14 ; z++)
    {
      data1 = RFID.read();
      newtag[z] = data1;
    }
    RFID.flush(); 
    checkmytags();
  }
  if (ok > 0)
  {
    Serial.println("Accepted");
    delay(200);
    digitalWrite(no, HIGH);
    delay (120);
    digitalWrite(no, LOW);
    digitalWrite(yes, HIGH);
    delay(5500);
   //BEEP warning
    digitalWrite(no, HIGH);
    delay (120);
    digitalWrite(no, LOW);
    delay (100);
    digitalWrite(no, HIGH);
    delay (120);
    digitalWrite(no, LOW);
    //Beep warning End
    digitalWrite(yes, LOW);
    ok = -1;
    Serial.println("Ready!!");
  }
  else if (ok == 0) // if we didn't have a match
  {
    Serial.println("Rejected");
    //BEEP warning
    delay (200);
    digitalWrite(no, HIGH);
    delay (150);
    digitalWrite(no, LOW);
    delay (50);
    digitalWrite(no, HIGH);
    delay (130);
    digitalWrite(no, LOW);
    //Beep warning End
    delay(1000);
    ok = -1;
  }
}
void opendoor()
{
  Serial.println("Accepted");
    delay(200);
    digitalWrite(no, HIGH);
    delay (120);
    digitalWrite(no, LOW);
    digitalWrite(yes, HIGH);
    delay(5500);
   //BEEP warning
    digitalWrite(no, HIGH);
    delay (120);
    digitalWrite(no, LOW);
    delay (100);
    digitalWrite(no, HIGH);
    delay (120);
    digitalWrite(no, LOW);
    //Beep     
    digitalWrite(yes, LOW);
    ok = -1;
    Serial.println("Ready!!");
}
void readpassword()
{
   if (Serial.available() > 0)
  {
    delay(100);
    for (int z = 0 ; z < 4 ; z++)
    {
      data1 = Serial.read();
      temppass[z] = data1;
    }
    Serial.flush();
checkpass();   
  } 
}

void checkpass()
{
  int ch = 0 ;
  for(int x=0 ; x<4 ;x++)
  {
    if(password[x] == temppass[x])
      ch++;
  }
  if(ch == 4)
    opendoor();
  else
    Serial.println("Password Error");
}

void readbutton()
{
 int s = digitalRead(button);
 if(s == HIGH)
 {
   opendoor() ; 
 }
}
void loop()
{
  delay(50);
  readTags();
  readpassword();
  readbutton();
}
