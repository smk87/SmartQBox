#include <Keypad.h>           
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Servo.h> 


//include definitions for The LED pins--------------------------------------//

#define greenPin 2
#define redPin 3

String textMessage;
int f=0;
int t=0;
int cn=0;
int lightsensor=A2;
int analogval=0;
int leagal=0;

String s1="AT+HTTPPARA=\"URL\",\"http://sqbox.000webhostapp.com/write_data.php?data1=";
 
String cmd,r1,r2,t1,t2;


Servo myservo;
SoftwareSerial SIM900(12, 13); 

                            
LiquidCrystal lcd(8,9,4,5,6,7); // initialize the LCD library with the numbers of the interface pins

                            //initialize variables
int getFingerprintIDez();
String s;
void ShowSerialData();
int cursorColumn = 0;       //this controls the cursor postition
int menu = 0;               //this controls the menu settings 
int n=0;                    // variable used to point to the bits in the keypad input array
int addr=0;
char pswrdElement=0;
char a='2';                 //variables a,b,c,d are all zero by default and store each digit of the 4 digit passcode
char b='3';
char c='3';
char d='5';
int count=0;

char password[]={a,b,c,d}; //initializing an array called password with variables a,b,c,d that hold the password digits
char input[4];             // an array that will contain the digits that are input
const byte ROWS = 4;       // Four rows
const byte COLS = 4;       // Four columns

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {52,50,48,46};

// Connect keypad COL0, COL1,COL2 and COL3 to these Arduino pins.
byte colPins[COLS] = {44,42,40,38}; 


// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup()
{
  // set the data rate for the sensor serial port
  myservo.attach(2);
  
  lcd.begin(16, 2);    // set up the LCD's number of columns and rows:
  lcd.print("Question Box-01");         // Prints a message to the LCD."

 
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  Serial.begin(9600);
  SIM900.begin(19200);
  
  // Give time to your GSM shield log on to network
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}

void bypass(){
   lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Emergency Mode."); 
   
   while(f==0){ 
    if(SIM900.available()>0){
    textMessage = SIM900.readString();
    Serial.print(textMessage);    
    delay(10);
  } 
  if(textMessage.indexOf("5566")>=0){
    // Open box and save current state
    myservo.write(90);
    f=1;
    Serial.println("Box Opened.");  
    textMessage = "";   
  }
   }
   readKeypad();
  }

void loop()
{
  analogval=analogRead(lightsensor);
  if(analogval<750 && leagal==1){
    Serial.println("Leagal Open.");
    Serial.println(analogval);
    readKeypad();
    
    }

   if(analogval<750 && leagal==0){
    Serial.println("Illeagal Open.");
    Serial.println(analogval);
    if(cn==0){
      sendSMS3();
      cn=1;
      }
    readKeypad();
    }

   if(analogval>=750){
    Serial.println(analogval);
      readKeypad();
    } 
} 


void askForCode(){
  lcd.clear();
  lcd.print("Enter the code");  //prints when the user wants to enter the code
}

void readKeypad(){
  char key = kpd.getKey();
  lcd.setCursor(cursorColumn,1);          // set the cursor to column "cursorColumn", line 1
  if(key)                      // Check for a valid key.
  {
    switch (key)
    {
      case '0':                                 // Each case is a button that is pressed
        if(menu == 1){                          // the value of "menu" determines the setting parameter and what each button does in that setting  
          lcd.print('0');
          cursorColumn=cursorColumn+1;
          input[n]='0';
          n=n+1;
        }
        else if(menu == 3){
          lcd.print('0');
          cursorColumn=cursorColumn+1;
          input[n]='0';
          n=n+1;
        }
        else if(menu == 4){
          lcd.print('0');
          cursorColumn=cursorColumn+1;
          input[n]='0';
          n=n+1;
        }
        break;
      case '1':
        if(menu == 1){
        lcd.print('1');
          cursorColumn=cursorColumn+1;
          input[n]='1';
          n=n+1;
        }
        else if(menu == 3){
          lcd.print('1');
          cursorColumn=cursorColumn+1;
          input[n]='1';
          n=n+1;
        }
        else if(menu == 4){
          lcd.print('1');
          cursorColumn=cursorColumn+1;
          input[n]='1';
          n=n+1;
        }
        break;
      case '2':
        if(menu == 1){
          lcd.print('2');
          cursorColumn=cursorColumn+1;
          input[n]='2';
          n=n+1;
        }
        else if(menu == 3){
          lcd.print('2');
          cursorColumn=cursorColumn+1;
          input[n]='2';
          n=n+1;
        }
        else if(menu == 4){
          lcd.print('2');
          cursorColumn=cursorColumn+1;
          input[n]='2';
          n=n+1;
        }
        break;
      case '3':
        if(menu == 1){
          lcd.print('3');
          cursorColumn=cursorColumn+1;
          input[n]='3';
          n=n+1;
        }
        else if(menu == 3){
          lcd.print('3');
          cursorColumn=cursorColumn+1;
          input[n]='3';
          n=n+1;
        } 
        else if(menu == 4){
          lcd.print('3');
          cursorColumn=cursorColumn+1;
          input[n]='3';
          n=n+1;
        }
        break;
      case '4':
        if(menu == 1){
          lcd.print('4');
          cursorColumn=cursorColumn+1;
          input[n]='4';
          n=n+1;
        }
        else if(menu == 3){
          lcd.print('4');
          cursorColumn=cursorColumn+1;
          input[n]='4';
          n=n+1;
        }
        else if(menu == 4){
          lcd.print('4');
          cursorColumn=cursorColumn+1;
          input[n]='4';
          n=n+1;
        }
        break;
      case '5':
        if(menu == 1){
          lcd.print('5');
          cursorColumn=cursorColumn+1;
          input[n]='5';
          n=n+1;
        }
        else if(menu == 3){
          lcd.print('5');
          cursorColumn=cursorColumn+1;
          input[n]='5';
          n=n+1;
        }
        else if(menu == 4){
          lcd.print('5');
          cursorColumn=cursorColumn+1;
          input[n]='5';
          n=n+1;
        }
        break;
      case '6':
        if(menu == 1){
          lcd.print('6');
          cursorColumn=cursorColumn+1;
          input[n]='6';
          n=n+1;
        }
        else if(menu == 3){
          lcd.print('6');
          cursorColumn=cursorColumn+1;
          input[n]='6';
          n=n+1;
        }
        else if(menu == 4){
          lcd.print('6');
          cursorColumn=cursorColumn+1;
          input[n]='6';
          n=n+1;
        }
        break;
      case '8':
        if(menu == 1){
          lcd.print('8');
          cursorColumn=cursorColumn+1;
          input[n]='8';
          n=n+1;
        }
        else if(menu == 3){
          lcd.print('8');
          cursorColumn=cursorColumn+1;
          input[n]='8';
          n=n+1;
        }
        else if(menu == 4){
          lcd.print('8');
          cursorColumn=cursorColumn+1;
          input[n]='8';
          n=n+1;
        }
        break;
      case '9':
        if(menu == 1){
          lcd.print('9');
          cursorColumn=cursorColumn+1;
          input[n]='9';
          n=n+1;
        }
        else if(menu == 3){
          lcd.print('9');
          cursorColumn=cursorColumn+1;
          input[n]='9';
          n=n+1;
        }
        else if(menu == 4){
          lcd.print('9');
          cursorColumn=cursorColumn+1;
          input[n]='9';
          n=n+1;
        }
        break;   
      case '7':
        if(menu == 1){
          lcd.print('7');
          cursorColumn=cursorColumn+1;
          input[n]='7';
          n=n+1;
        break;
        }
        else if(menu == 3){
          lcd.print('7');
          cursorColumn=cursorColumn+1;
          input[n]='7';
          n=n+1;
        }
        else if(menu == 4){
          lcd.print('7');
          cursorColumn=cursorColumn+1;
          input[n]='7';
          n=n+1;
        }   
      case 'A':
        if(menu == 0){
          lcd.setCursor(0,0);
          askForCode();
          lcd.setCursor(0,1);
          menu=menu+1;
        }
        break;
      case 'B':
        if(menu == 0){
          lcd.setCursor(0,0);
          lcd.clear();
          lcd.print("Change Code?");
          lcd.setCursor(0,1);
          menu=menu+2;
        }
      case 'C':
          if(menu == 0){
          lcd.setCursor(0,0);
          bypass();
          lcd.setCursor(0,1);
          menu=menu+1;
        }
        break;   
      case 'D':
        reset();
        break;
      case '*':
        if(menu == 2){
          lcd.setCursor(0,0);
          lcd.clear();
          lcd.print("Enter old code");
          lcd.setCursor(0,1);
          menu=menu+1;
        }  
      default:
       return; 
    }
  } 
  if(menu==1 && n > 3){                             //If the menu is in setting 1 and the input array has been filled with 4 digits then...
    boxlockCheck();    //calls the function to check whether the code that was input matches the code that is stored
  }
  else if(menu==3 && n > 3){
    oldCodeCheck();  
  }
  else if(menu==4 && n > 3){
  changeToNewCode(password,input);
  delay(250); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Code Changed");
  delay(1000);
  reset();
  }
  if(checkCode(password,input) == true){
    delay(50);
  }
}


boolean checkCode(char *a,char *b){                   //The function to check whether the contents of the first parameter,an array, match the 
  int p;                                              //match the contents of the second parameter, also an array.
  for(p=0; p<4; p++) 
    if(a[p]!=b[p]) return false;
    return true;
}

int changeToNewCode(char *a, char *b){
  int p = 0;
  for(p=0; p<4; p++){
    a[p]=b[p];
  } 
  n=0;
}

int boxlockCheck(){
  if(n > 3){
   if(checkCode(password,input) == true){
     delay(250);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Correct!"); 
     myservo.write(90);
     delay(2000);
     sendSMS();// send the sms
     sendloc();//send location
     leagal=1;
   }
  else{
   delay(250);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Invalid Code!");
   count=count+1;
    if(count==2){
     sendSMS2();// send the sms
     count=0;
      sendloc();//send location
    } 
   digitalWrite(greenPin,LOW);
   delay(2000); 
    }  
   cursorColumn=0;
   n=0;
  }
}

int oldCodeCheck(){
  if(n > 3){
   if(checkCode(password,input) == true){
     delay(250);  
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Correct!"); 
     delay(1000);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Enter new Code");
     menu=4;
   }
  else{
   delay(250);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Invalid Code!"); 
   delay(2000);
   reset();
    } 
   n=0; 
   cursorColumn=0;
  }
}

void reset(){
  int i;
  cursorColumn=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Question Box-01");
  menu=0;
  n=0;
  for(i=0;i<4;i++){
    input[i]='r';
  }

  myservo.write(0);
  f=0;
  cn=0;
  leagal==0;
}


void sendSMS() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+IPR=19200");
  delay(2000);
  
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+8801712126596\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Notification: Box-01 has been opened."); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}

void sendSMS2() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+IPR=19200");
  delay(2000);
  
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+8801712126596\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Notification: Someone tried to open Box-01."); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}

void sendloc(){
  //SIM900.begin(9600);

  SIM900.print("AT+IPR=9600");
  delay(2000);
    
  Serial.println("TCP Send :");
  Serial.print("AT\\r\\n");
  SIM900.println("AT"); /* Check Communication */
  delay(5000);
  ShowSerialData(); /* Print response on the serial monitor */
  delay(5000);

   // Set connection type to GPRS
  SIM900.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(2000);
  ShowSerialData();

  // Set the APN
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"gpinternet\"");
  delay(2000);
  ShowSerialData();

  // Enable GPRS
  SIM900.println("AT+SAPBR=1,1");
  delay(10000);
  ShowSerialData();

  // Check to see if connection is correct and get your IP address
  SIM900.println("AT+SAPBR=2,1");
  delay(2000);
  ShowSerialData();


  Serial.print("Location:");
  SIM900.println("AT+CIPGSMLOC=1,1"); /* Check Communication */
  delay(5000);
  t=1;
  ShowSerialData(); /* Print response on the serial monitor */
  //Serial.print(s[0]);
  delay(5000);

  Serial.print("Time:");
  SIM900.println("AT+CIPGSMLOC=2,1"); /* Check Communication */
  delay(5000);
  t=2;
  ShowSerialData(); /* Print response on the serial monitor */
  //Serial.print(s[0]);
  delay(5000);

  
  SIM900.print("AT+IPR=19200");
  delay(2000);
  
   
  Serial.println("Config SIM900...");
  delay(2000);
  Serial.println("Done!...");
  SIM900.flush();
  Serial.flush();

  // attach or detach from GPRS service 
  SIM900.println("AT+CGATT?");
  delay(100);
  ShowSerialData();


  // bearer settings
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);
  ShowSerialData();

  // bearer settings
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"gpinternet\"");
  delay(2000);
  ShowSerialData();

  // bearer settings
  SIM900.println("AT+SAPBR=1,1");
  delay(2000);
  ShowSerialData();
   
   // initialize http service
   SIM900.println("AT+HTTPINIT");
   delay(2000); 
   ShowSerialData();

   // set http param value
   //SIM900.println("AT+HTTPPARA=\"URL\",\"http://albusaidi.16mb.com/write_data.php?data1=2.88&data2=2.93\""); 
   //SIM900.println("AT+HTTPPARA=\"URL\",\"http://sqbox.000webhostapp.com/write_data.php?data=44444\"");  
   ShowSerialData();
   cmd=String(s1)+String(r1)+String("&data2=")+String(r2)+String("&data3=")+String(t2)+String("&data4=")+String(t1)+String("\"");
   Serial.println(cmd);
   SIM900.println(cmd);
   delay(2000);
   

   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   SIM900.println("AT+HTTPACTION=0");
   delay(6000);
   ShowSerialData();

   // read server response
   SIM900.println("AT+HTTPREAD"); 
   delay(1000);
   ShowSerialData();

   SIM900.println("");
   SIM900.println("AT+HTTPTERM");
   ShowSerialData();
   delay(300);

   SIM900.println("");
   delay(10000);
  }

  

  void ShowSerialData()
{
  while(SIM900.available()!=0) { /* If data is available on serial port */
  char c =SIM900.read(); /* Print character received on to the serial monitor */
  //Serial.print(c);

  s +=c;
  //Serial.print(s);
  }
  
  if(t==1){
     r1=s.substring(34,42);
     r2=s.substring(44,52);
    Serial.println(r1);
    Serial.println(r2);
  s="";
  t=0;
  }
  else if(t==2){
      t1=s.substring(34,44);
     t2=s.substring(45,53);
    Serial.println(t1);
    Serial.println(t2);
  s="";
  t=0;
    }
  else{
    Serial.print(s);
  s="";  
  }
}


void sendSMS3() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+IPR=19200");
  delay(2000);
  
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT + CMGS = \"+8801712126596\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Notification: Someone opened box illegally."); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}
