/*
      MORSE CODE TRANSLATOR
!Works ONLY with International Morse code!
User is expected to type a message in the Serial Monitor containing
only latin letters and digits and Arduino will translate it into Morse code, 
with the dashes and dots heard from the piezo and seen from the LED.

Do not enter a sentence longer than 60 characters!

Mladen Mihalkov December 2024
*/


#define NOTE_A5  880
#define NOTE_B3  247
#define NOTE_D5  587


#define LED 8
#define PIEZO 6

// Morse code space durations
#define DIT 200
#define DASH 3 * DIT
#define SIGNAL_SPACE DIT
#define CHAR_SPACE 3 * DIT
#define WORD_SPACE 7 * DIT

/*
      TASKS
 1. (DONE)Create read_message(void):  
     - reads message from Serial Monitor  done
       - Converts all the characters to LowerCase  D
       - If no message was read reterns empty string. D
       - If message contains unsupported chars, Print error message D
       - If the message is successfully read notify the user to wait!
       
 2. (DONE)void produce_signal(bool dash_or_dit)
      - Produce dash or dit according to the value of dash_or_dit.
      - Do not wait
      
 3. (DONE) Create array MorseChar_array: 
      - of structs for each MorseChar(from a-z and 1-9)
    
 4. (DONE) convert_character(char ch)
    - reference the letter-to-morse-code array with index ch - 'a'. !! Check if it is a letter or a digit. (DONE)
    - read the three bits of the result using bitmasks (DONE)
    - call produce_signal() for each bit (DONE)
    - if the bit is empty than don't produce a sound  (DONE)
    - delay between the signals (DONE)
    - Do not handle spaces! (DONE);
    
 5.(DONE) Add print to the console and also produce a sound signal notifying that the program is ready!
    Create notify_start(void)
      -- produce short beginning sound
      -- flash the LED several times
      -- print message to the serial mointor
 6. (DONE) Create convert_message(String msg)
      - Read each character  D
      - If it is space:  D
          -- it is considered the end of a word D
          -- there sould be a word space delay  D
      - If it is not space call convert_character for each char  D
      - delay betwenn characters  D

*/

String MorseChars[] = {
    "01",  // A
    "1000", // B
    "1010", //C
    "100",  // D
    "0",   // E
    "0010",   // F
    "110",   // G
    "0000",   // H
    "00",   // I
    "0111",   // J
    "101",   // K
    "0100",   // L
    "11",   // M
    "10",   // N
    "111",   // O
    "0110",   // P
    "1101",   // Q
    "010",   // R
    "000",   // S
    "1",   // T
    "001",   // U
    "0001",   // V
    "011",   // W
    "1001",   // X
    "1011",   // Y
    "1100",    // Z
    "11111",   // 0
    "01111",   // 1
    "00111",   // 2
    "00011",   // 3
    "00001",   // 4
    "00000",   // 5
    "10000",   // 6
    "11000",   // 7
    "11100",   // 8
    "11110",   // 9
  };


String message = "";


void produce_signal(bool dash_or_dit)
{
   // dash
   if(dash_or_dit)
   {
      digitalWrite(LED, HIGH);
      tone(PIEZO, NOTE_A5, DASH);
      delay(DASH); 
      digitalWrite(LED, LOW);
      Serial.println("dash");
   } 
   else   // dit
   {
      digitalWrite(LED, HIGH);
      tone(PIEZO, NOTE_A5, DIT);
      delay(DIT); 
      digitalWrite(LED, LOW);
      Serial.println("dit");

   }
}

void convert_character(char ch)
{
    int lookup_index = 0;
    if(ch >= 'a' && ch <= 'z') lookup_index = ch - 'a';
    else lookup_index = ch - '0' + 26;
    String morse_str = MorseChars[lookup_index];
    Serial.println(morse_str);
    for(int i = 0; i < morse_str.length(); i++)
    {
       if(morse_str[i] == '1')  produce_signal(1);
       else produce_signal(0);
       delay(SIGNAL_SPACE);
    } 
}


String read_message(void)
{
  String message = "";
  char ch;
    while(Serial.available() > 0)
    {
      ch = tolower(char(Serial.read()));
      if ((ch < 'a' || ch > 'z') && (ch < '0' || ch > '9') && ch != '\n' && ch != ' ')
      {
        Serial.println("You entered unsuppored characters!!");
        message = "";
        while(Serial.available() > 0) Serial.read();
        return ""; 
      }
      message += ch;
      delay(50);
    }
    return message;
}

void notify_start(void)
{
  Serial.println("Translator is ready!");
  Serial.println("Send a message to hear and see it translated into Morse code");
  for(int i = 0; i < 5;++i)
  {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  }  
  tone(PIEZO, NOTE_B3, 300);
  delay(300);
  tone(PIEZO, NOTE_D5, 600);
  delay(700);
}

void convert_message(String msg)
{
  for(int i = 0;i < msg.length(); ++i)
  {
      if(msg[i] == ' ') delay(CHAR_SPACE);
      else
      {
          convert_character(msg[i]);
          delay(CHAR_SPACE);
      }  
  }
}



void setup() {
  digitalWrite(LED, OUTPUT);
  digitalWrite(PIEZO, OUTPUT);
  Serial.begin(9600);
  notify_start();
  digitalWrite(LED, LOW);
}

void loop() {
  if((message = read_message()) != "")
  {
    Serial.println("Mes: " + message);
    convert_message(message);
  }
}