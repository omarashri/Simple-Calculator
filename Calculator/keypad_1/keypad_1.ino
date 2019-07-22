/*
calculator
*/
char key;
double first = 0;
double second = 0;
double total = 0;
bool next=false;
char nextOp;

/*
end of calculator
*/

const int a0 = 9;
const int a1 = 10;
const int WR = 11;
const int RD = 12;
int num = 0;
int count = 0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] ={
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'C','0','=','+'}
};
int Column_check[4]= {1,1,1,1};
int counter=4;
void pins_out()
{
  pinMode(0, OUTPUT); pinMode(1, OUTPUT);
  pinMode(2, OUTPUT); pinMode(3, OUTPUT);
  pinMode(4, OUTPUT); pinMode(5, OUTPUT);
  pinMode(6, OUTPUT); pinMode(7, OUTPUT);
}
void pins_in()
{
   pinMode(0, INPUT); pinMode(1, INPUT);
  pinMode(2, INPUT); pinMode(3, INPUT);
   pinMode(4, INPUT); pinMode(5, INPUT);
  pinMode(6, INPUT); pinMode(7, INPUT);
}
void setup()
{
  pins_out();
  pinMode(a0, OUTPUT); pinMode(a1, OUTPUT);
  pinMode(WR, OUTPUT); pinMode(RD, OUTPUT);
}
void READ_Column()
{
  counter = 4 ;
   digitalWrite(a0, 0); //Port c is selected
  digitalWrite(a1, 1); //Port c is selected

  for(int j=0;j<4;j++)
  {
    digitalWrite(RD, 0);   //Enabling READ
    Column_check[j]= digitalRead(counter);
    digitalWrite(RD, 1);   //Disabling READ
    counter++;
  }
}
char READ_KEYPAD()                                                                                                                                         
{ 
  pins_in();
  digitalWrite(a0, 0); //Port c is selected
  digitalWrite(a1, 1); //Port c is selected
  digitalWrite(WR, 0);   //Enabling WRITE
  delay(10);
  digitalWrite(WR, 1);
  int i_Row=0;
   while(true)
    {
     while(i_Row<=3)
       {
   digitalWrite(0, 1);digitalWrite(1, 1);digitalWrite(2, 1);digitalWrite(3, 1);
   digitalWrite(WR, 0);   //Enabling WRITE
   delay(10);
   digitalWrite(WR, 1);
   digitalWrite(i_Row, 0);
   digitalWrite(WR, 0);   //Enabling WRITE
   delay(10);
   digitalWrite(WR, 1);
   delay(20);
   READ_Column();
   if(Column_check[0]==0 )
     {
    pins_out();
    return hexaKeys[i_Row][0];
     }
    else if(Column_check[1]==0)
     {
     pins_out();
    return hexaKeys[i_Row][1];
     }
   else if(Column_check[2]==0)
     {
     pins_out();
     return hexaKeys[i_Row][2];
     }
   else if(Column_check[3]==0)
     {
     pins_out();
    return hexaKeys[i_Row][3];
     }
    i_Row++;
   }
  i_Row=0;
}
Column_check[0] = 1;
Column_check[1] = 1;
Column_check[2] = 1;
Column_check[3] = 1;
}

void write_LCD(int value)
{
  pins_out();
  digitalWrite(a0, 1); //Port B is selected
  digitalWrite(a1, 0); //Port B is selected
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(i, (value >> i) & 0x01);
  }
  digitalWrite(WR, 0);  //WRITE ENABLED
  delay(10);
  digitalWrite(WR, 1);
  digitalWrite(a0, 0); //Port A is selected
  digitalWrite(a1, 0); //Port A is selected
  digitalWrite(6, 1);
  digitalWrite(7, 1);
  digitalWrite(WR, 0);  //WRITE ENABLED
  delay(10);
  digitalWrite(WR, 1);
  digitalWrite(6, 1);
  digitalWrite(7, 0);
  digitalWrite(WR, 0);  //WRITE ENABLED
  delay(10);
  digitalWrite(WR, 1);
}

void controlword_KEYPAD()
{
    digitalWrite(RD, 1);   //Disabling READ (read active low)
    digitalWrite(WR, 1);  //Disabling WRITE(write active low)
    digitalWrite(a0, 1);  //Selecting Control Register of 8255
    digitalWrite(a1, 1);  //Selecting Control Register of 8255
    digitalWrite(7, 1);  // active mode
    digitalWrite(6, 0);  //mode 0
    digitalWrite(5, 0);  //
    digitalWrite(4, 0);  // 8255 Ports A and B as OUTPUT
    digitalWrite(3, 1);  // Port CU as INPUT
    digitalWrite(2, 0);  //
    digitalWrite(1, 0);  //
    digitalWrite(0, 0);  //
}

void write_command(int value)
{
  digitalWrite(a0, 1); //Port B is selected
  digitalWrite(a1, 0); //Port B is selected
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(i, (value >> i) & 0x01);
  }
  digitalWrite(WR, 0);  //WRITE ENABLED
  delay(10);
  digitalWrite(WR, 1);
  digitalWrite(a0, 0); //Port A is selected
  digitalWrite(a1, 0); //Port A is selected
  digitalWrite(6, 0);
  digitalWrite(7, 1);
  digitalWrite(WR, 0);  //WRITE ENABLED
  delay(10);
  digitalWrite(WR, 1);
  digitalWrite(6, 0);
  digitalWrite(7, 0);
  digitalWrite(WR, 0);  //WRITE ENABLED
  delay(10);
  digitalWrite(WR, 1);
}
void loop() 
{
  if (num == 0)
  {
controlword_KEYPAD();
digitalWrite(WR, 0);   //Enabling WRITE
delay(10);
digitalWrite(WR, 1);
delay(50);
write_command(0x38);
delay(50);
write_command(0x0E);
delay(50);
write_command(0x01);
delay(50);
write_command(0x06);
delay(50);
num = 1;
write_command(0xc);
  }
key= READ_KEYPAD();
   
if(key!=NULL ||next==true)
    {
  if(next==true)
  {
   key=nextOp;
  }
    switch(key)
    {
     case '+':
  if (total!=0)
  first=total;
  if(next==false)
   {
      write_LCD('+');
   }
    second=GetsecondNumber();
    total=first+second;
    if(next==true)
    {
  write_LCD(nextOp);
   key=nextOp;
    }
    first=0;
    second=0;
    break;

    case'-':
 if (total!=0)
  first=total;
 if(next==false)
   {
      write_LCD('-');
   }
    second=GetsecondNumber();
    total=first-second;
    if(next==true)
    {
      write_LCD(nextOp);
   key=nextOp;
      }
    first=0;
    second=0;
    break;
    
      case'*': 
 if (total!=0)
  first=total;
   if(next==false)
   {
    write_LCD('*');
   }
    second=GetsecondNumber();
    total=first*second;
    if(next==true)
    {
      write_LCD(nextOp);
   key=nextOp;
      }
    first=0;
    second=0;
    break;
    
        case'/':
 if (total!=0)
  first=total;
    if(next==false)
   {
    write_LCD('/');
   }
    second=GetsecondNumber();
    total=first/second;
    if(next==true)
    {
      write_LCD(nextOp);
   key=nextOp;
      }
    first=0;
    second=0;
    break;

     case 'C':
     total=0;
     first=0;
     second=0;
     next=false;
     nextOp='Q';
     write_command(0x01);
     break;


      case '=':
      write_command(0x01);
      write_LCD('=');
      cout(total);
      total=0;
     break;

     
     default:
     write_command(0x01);
     if (next==false)
     {
     }
     
     first=first*10+(key-'0');
     cout(first);
     break;
      }
     }
delay(150);
}

void cout(double valu)
{
  String Val=String(valu);
  for(int i=0;i<Val.length();i++)
     write_LCD(Val[i]);
  }

long GetsecondNumber()
{
  
  key='Q';
  while(true)
  {
    key= READ_KEYPAD();    
    if(key>='0'&&key<='9')
    {
      second = second * 10 + (key - '0'); //bntra7 al asce code bta3 al 0 3l4an ngeb kimt alrakm
      write_command(0x01);
      cout(second);
    }
    
   else if(key=='=')
      {
      next=false;
      break;   
      }
     else if(key=='+')
     {
      next=true;
      nextOp='+';
      break;
      }
       else if(key=='-')
     {
      next=true;
      nextOp='-';
      break;
      }
      else if(key=='C')
      {
     total=0;
     first=0;
     second=0;
     next=false;
     nextOp='Q';
     write_command(0x01);
     break;
        }
    }
    return second;
  }
