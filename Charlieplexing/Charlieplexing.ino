#define A 3
#define B 4
#define C 5
#define D 6
#define E 7

unsigned long previousMillis = 0; 
long duration = 700;
int displayedsymbolindex = -1;
String inputString = "";
boolean stringComplete = false;
boolean serialControll = false;
int chartoindexresult = 9001;
char charbuf[100];
int serialindex = 0;
boolean cmdmode = false;
boolean cmdexe = false;
String cmd = "";
boolean soe = true;

byte ledPin[4][5][2] =
{{{E,A},{E,B},{E,C},{E,D},{D,E}},         // { A , B }
 {{D,A},{D,B},{D,C},{C,D},{C,E}},         //   ^   ^
 {{C,A},{C,B},{B,C},{B,D},{B,E}},         //  LOW HIGH
 {{B,A},{A,B},{A,C},{A,D},{A,E}}};

const boolean symbol[][5][4]={{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}  //    0
                             ,{{0,1,1,0},{1,0,0,1},{1,0,0,1},{1,0,0,1},{0,1,1,0}}  // 0  1
                             ,{{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}}  // 1  2
                             ,{{1,1,1,1},{0,0,0,1},{1,1,1,1},{1,0,0,0},{1,1,1,1}}  // 2  3
                             ,{{1,1,1,1},{0,0,0,1},{1,1,1,1},{0,0,0,1},{1,1,1,1}}  // 3  4
                             ,{{1,0,0,1},{1,0,0,1},{1,1,1,1},{0,0,0,1},{0,0,0,1}}  // 4  5
                             ,{{1,1,1,1},{1,0,0,0},{1,1,1,1},{0,0,0,1},{1,1,1,1}}  // 5  6
                             ,{{1,1,1,1},{1,0,0,0},{1,1,1,1},{1,0,0,1},{1,1,1,1}}  // 6  7
                             ,{{1,1,1,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}}  // 7  8
                             ,{{1,1,1,1},{1,0,0,1},{1,1,1,1},{1,0,0,1},{1,1,1,1}}  // 8  9
                             ,{{1,1,1,1},{1,0,0,1},{1,1,1,1},{0,0,0,1},{1,1,1,1}}  // 9  10
                             ,{{0,1,1,0},{1,0,0,1},{1,1,1,1},{1,0,0,1},{1,0,0,1}}  // A  11
                             ,{{1,1,1,0},{1,0,0,1},{1,1,1,0},{1,0,0,1},{1,1,1,0}}  // B  12
                             ,{{0,1,1,1},{1,0,0,0},{1,0,0,0},{1,0,0,0},{0,1,1,1}}  // C  13
                             ,{{1,1,1,0},{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,0}}  // D  14
                             ,{{1,1,1,1},{1,0,0,0},{1,1,1,1},{1,0,0,0},{1,1,1,1}}  // E  15
                             ,{{1,1,1,1},{1,0,0,0},{1,1,1,1},{1,0,0,0},{1,0,0,0}}  // F  16
                             ,{{1,1,1,1},{1,0,0,0},{1,0,1,1},{1,0,0,1},{1,1,1,1}}  // G  17
                             ,{{1,0,0,1},{1,0,0,1},{1,1,1,1},{1,0,0,1},{1,0,0,1}}  // H  18
                             ,{{0,1,1,1},{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,1,1,1}}  // I  19
                             ,{{1,1,1,1},{0,0,0,1},{0,0,0,1},{1,0,0,1},{0,1,1,1}}  // J  20
                             ,{{1,0,0,1},{1,0,1,0},{1,1,0,0},{1,0,1,0},{1,0,0,1}}  // K  21
                             ,{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,1,1,1}}  // L  22
                             ,{{1,0,0,1},{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,0,0,1}}  // M  23
                             ,{{1,0,0,1},{1,1,0,1},{1,1,1,1},{1,0,1,1},{1,0,0,1}}  // N  24
                             ,{{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,1}}  // O  25
                             ,{{1,1,1,1},{1,0,0,1},{1,1,1,1},{1,0,0,0},{1,0,0,0}}  // P  26
                             ,{{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,0,1,1},{1,1,1,1}}  // Q  27
                             ,{{1,1,1,1},{1,0,0,1},{1,1,1,1},{1,0,1,0},{1,0,0,1}}  // R  28
                             ,{{0,1,1,1},{1,0,0,0},{1,1,1,1},{0,0,0,1},{1,1,1,0}}  // S  29
                             ,{{0,1,1,1},{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}}  // T  30
                             ,{{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,1}}  // U  31
                             ,{{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,0,0,1},{0,1,1,0}}  // V  32
                             ,{{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,1},{1,0,0,1}}  // W  33
                             ,{{1,0,0,1},{1,0,0,1},{0,1,1,0},{1,0,0,1},{1,0,0,1}}  // X  34
                             ,{{0,1,0,1},{0,1,0,1},{0,1,0,1},{0,0,1,0},{0,0,1,0}}  // Y  35
                             ,{{1,1,1,1},{0,0,0,1},{0,1,1,0},{1,0,0,0},{1,1,1,1}}  // Z  36
                             ,{{0,0,0,0},{0,0,1,0},{0,1,1,1},{0,0,1,0},{0,0,0,0}}  // +  37
                             ,{{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}}  // -  38
                             ,{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,1,0}}  // .  39
                             ,{{0,0,0,0},{0,1,1,0},{0,0,0,0},{0,1,1,0},{0,0,0,0}}  // :  40
                             ,{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,1,0},{0,1,0,0}}  // ,  41
                             ,{{0,0,0,0},{0,0,1,0},{0,0,0,0},{0,0,1,0},{0,1,0,0}}  // ;  42
                             ,{{0,1,1,0},{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,1,1,0}}  // !  43
                             ,{{1,0,1,0},{0,1,0,1},{1,0,1,0},{0,1,0,1},{1,0,1,0}}  // ERROR  44
};


void clearDisplay()
{
  pinMode(A,INPUT);
  digitalWrite(A,LOW);
  pinMode(B,INPUT);
  digitalWrite(B,LOW);
  pinMode(C,INPUT);
  digitalWrite(C,LOW);
  pinMode(D,INPUT);
  digitalWrite(D,LOW);
  pinMode(E,INPUT);
  digitalWrite(E,LOW);
}

void led( byte pins[2] )
{
  pinMode( pins[1], OUTPUT );
  digitalWrite( pins[1], HIGH );
  pinMode( pins[0], OUTPUT );
  digitalWrite( pins[0], LOW );
}

void displaysymbol(int index){
  clearDisplay();
  for(int row=0; row < 5; row++){
    for(int column=0; column < 4; column++){
      if(symbol[index] [row] [column]){
        led(ledPin[column] [row]);
      }
      else if (symbol[index] [row] [column] == 0){
        clearDisplay();
      }
      else {
        led(ledPin[column] [row]);
      }
      
      clearDisplay();
    }
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      serialindex = 0;
      stringComplete = true;
      
      inputString = inputString.substring(0, inputString.length()-1);
      if(inputString == "!cmd"){
         cmdmode = true;
        Serial.println("[CMD]: ON! [BETA]");
      }
     else{
      if (cmdmode == false){
        serialControll = true;
        if(soe) {
          inputString += ' ';
          
          
        }
          inputString += ' ';
          inputString += ' ';
          char buf[inputString.length()];
          snprintf( buf, sizeof(buf)-1, "%s", inputString.c_str() );
          buf[sizeof(buf)] = '\0';
          for(int i = 0; i < sizeof(buf); i++){
            if(buf[i-1]!=NULL){
              charbuf[i] = buf[i];
            }
          }
          chartoindex(charbuf[0]);
          displayedsymbolindex = chartoindexresult;
          Serial.println("Jetzt wird:");
          Serial.println(inputString);
          Serial.println("angezeigt");
        }
        else{
          if(cmdexe){
            if(cmd == "dur"){
              cmdexe = false;
              cmdmode = false;
              cmd = "";
              duration = inputString.toInt();
              Serial.print("[CMD]: Duration: ");
              Serial.println(inputString.toInt());
              Serial.println("[CMD]: OFF");
              break;
            }
          }
          else{
          if(inputString == "dur"){
              Serial.println("[CMD]: Please send new duration");
              cmdexe = true;
              cmd = "dur"; 
          }
          else if(inputString == "chartest"){
              serialControll = false;
              Serial.println("[CMD]: chartest mode");
              Serial.println("[CMD]: OFF");
              cmdmode = false;
          }
          else if(inputString == "bgn"){
            Serial.println("[CMD]: Beginning from start");
            Serial.println("[CMD]: OFF");
            serialindex = 0;
            cmdmode = false;
          }
          else if(inputString == "soe"){
            if(soe) {
              soe = false;
              Serial.println("[CMD]: SOE OFF");
              
            }
            else{
              soe = true;
              Serial.println("[CMD]: SOE ON");
            }
            Serial.println("[CMD]: OFF");
            Serial.println(soe);
            cmdmode = false;
          }
          else{
              cmdmode = false;
              Serial.println("[CMD]: OFF");
          }
        }
        
      }
     }
     
   }
 
  }
}


void chartoindex(char input){
  switch (input) {
  case ' ':
    chartoindexresult = 0;
    break;
  case '0':
    chartoindexresult = 1;
    break;
  case '1':
    chartoindexresult = 2;
    break;
  case '2':
    chartoindexresult = 3;
    break;
  case '3':
    chartoindexresult = 4;
    break;
  case '4':
    chartoindexresult = 5;
    break;
  case '5':
    chartoindexresult = 6;
    break;
  case '6':
    chartoindexresult = 7;
    break;
  case '7':
    chartoindexresult = 8;
    break;
  case '8':
    chartoindexresult = 9;
    break;
  case '9':
    chartoindexresult = 10;
    break;
  case 'A':
    chartoindexresult = 11;
    break;
  case 'B':
    chartoindexresult = 12;
    break;
  case 'C':
    chartoindexresult = 13;
    break;
  case 'D':
    chartoindexresult = 14;
    break;
  case 'E':
    chartoindexresult = 15;
    break;
  case 'F':
    chartoindexresult = 16;
    break;
  case 'G':
    chartoindexresult = 17;
    break;
  case 'H':
    chartoindexresult = 18;
    break;
  case 'I':
    chartoindexresult = 19;
    break;
  case 'J':
    chartoindexresult = 20;
    break;
  case 'K':
    chartoindexresult = 21;
    break;
  case 'L':
    chartoindexresult = 22;
    break;
  case 'M':
    chartoindexresult = 23;
    break;
  case 'N':
    chartoindexresult = 24;
    break;
  case 'O':
    chartoindexresult = 25;
    break;
  case 'P':
    chartoindexresult = 26;
    break;
  case 'Q':
    chartoindexresult = 27;
    break;
  case 'R':
    chartoindexresult = 28;
    break;
  case 'S':
    chartoindexresult = 29;
    break;
  case 'T':
    chartoindexresult = 30;
    break;
  case 'U':
    chartoindexresult = 31;
    break;
  case 'V':
    chartoindexresult = 32;
    break;
  case 'W':
    chartoindexresult = 33;
    break;
  case 'X':
    chartoindexresult = 34;
    break;
  case 'Y':
    chartoindexresult = 35;
    break;
  case 'Z':
    chartoindexresult = 36;
    break;
  case '+':
    chartoindexresult = 37;
    break;
  case '-':
    chartoindexresult = 38;
    break;
  case '.':
    chartoindexresult = 39;
    break;
  case ':':
    chartoindexresult = 40;
    break;
  case ',':
    chartoindexresult = 41;
    break;
  case ';':
    chartoindexresult = 42;
    break;
  case '!':
    chartoindexresult = 43;
    break;
  default:
    chartoindexresult = 44;
}
}

void setup() {
  Serial.begin(9600);
  //Serial.println("Booting... (BUG: send ' ')");
  inputString.reserve(200);
  clearDisplay();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= duration) {
   
    if (serialControll == false){
    displayedsymbolindex++;
    }
    else{
       if(serialindex == sizeof(charbuf) || charbuf[serialindex] == NULL) serialindex = 0;
       char currcharbuf = charbuf[serialindex];
       chartoindex(currcharbuf);
       displayedsymbolindex = chartoindexresult;
       serialindex++;
      
    }
    if(displayedsymbolindex == 44) displayedsymbolindex = 0;
    previousMillis = currentMillis;
  }
  displaysymbol(displayedsymbolindex);
  
  if (stringComplete) {
    

    inputString = "";
    stringComplete = false;
  }
}



