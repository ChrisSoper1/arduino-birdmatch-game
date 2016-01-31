int SENS_1   = A0;
int SENS_2   = A1;
int SENS_3   = A2;
int SENS_4   = A3;
int SENS_5   = A4;
int SENS_6   = A5;
int LED_1    =  1;
int LED_2    =  2;
int LED_3    =  3;
int LED_4    =  4;
int LED_5    =  5;
int LED_6    =  6;
int STRIKE1  =  7;
int STRIKE2  =  8;
int STRIKE3  =  9;
int BELL     = 10;
int LOSE     = 11;
int GO_LEVER = 12;

int val1 = 1;
int val2 = 1;
int val3 = 1;
int val4 = 1;
int val5 = 1;
int val6 = 1;
int counter = 0;


void setup() {
  // put your setup code here, to run once: 
  /* 
   * This is a block comment
   * 
   */
  // Set the sensor pins input mode
  pinMode (SENS_1, INPUT);
  pinMode (SENS_2, INPUT);
  pinMode (SENS_3, INPUT);
  pinMode (SENS_4, INPUT);
  pinMode (SENS_5, INPUT);
  pinMode (SENS_6, INPUT);
  pinMode (GO_LEVER, INPUT);
  // set the LED pins output mode
  pinMode (LED_1, OUTPUT);
  pinMode (LED_2, OUTPUT);
  pinMode (LED_3, OUTPUT);
  pinMode (LED_4, OUTPUT);
  pinMode (LED_5, OUTPUT);
  pinMode (LED_6, OUTPUT);
  pinMode (STRIKE1, OUTPUT);
  pinMode (STRIKE2, OUTPUT);
  pinMode (STRIKE3, OUTPUT);
  pinMode (LOSE, OUTPUT);

  pinMode (BELL, OUTPUT); //Bell rings if all conditions are true - super answer
  // pinMode (TONE, OUTPUT); //buzzer sounds if answer incorrect
  digitalWrite (STRIKE1,LOW);
  digitalWrite (STRIKE2,LOW);
  digitalWrite (STRIKE3,LOW);
  // pullup resistors set to force input state to HIGH until a switch to ground is read (eliminates random noise)
  digitalWrite (SENS_1,HIGH);
  digitalWrite (SENS_2,HIGH);
  digitalWrite (SENS_3,HIGH);
  digitalWrite (SENS_4,HIGH);
  digitalWrite (SENS_5,HIGH);
  digitalWrite (SENS_6,HIGH);
  digitalWrite (GO_LEVER,HIGH);
}

void loop() {
  
  if ( digitalRead(GO_LEVER) == LOW && counter <3) // Three tries
  {
    val1 = digitalRead(SENS_1);
    val2 = digitalRead(SENS_2);
    val3 = digitalRead(SENS_3);
    val4 = digitalRead(SENS_4);
    val5 = digitalRead(SENS_5);
    val6 = digitalRead(SENS_6);

    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
  
    delay(300);
    //dramatic 3 blink drum roll
     for (int i = 0; i <3 ; i = i+1)
     {
    
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
    digitalWrite(LED_6, HIGH);

    delay(300);
    
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
  
    delay(300);
     }
     
      
     digitalWrite(LED_1, !val1);
     delay(1000);
    
     digitalWrite(LED_2, !val2);        // !val gives the inverse answer
     delay(1000);
    
     digitalWrite(LED_3, !val3);
     delay(1000);
    
     digitalWrite(LED_4, !val4);
     delay(1000);
 
     digitalWrite(LED_5, !val5);
     delay(1000);
    
     digitalWrite(LED_6, !val6);
     delay(1000);

    if (val1 == 0 && val2 == 0 && val3 == 0 && val4 == 0 && val5 == 0 && val6 == 0) //all answers correct
    {
      digitalWrite (BELL, HIGH);
      delay (3000);
      digitalWrite (BELL, LOW);
      while (true){
        
      }
    }
    else {
      counter = counter + 1;
      if (counter == 1){
        digitalWrite(STRIKE1,HIGH);
        digitalWrite (LOSE,HIGH);
        
        delay (1000);
        digitalWrite (LOSE,LOW); 
      }
      if (counter == 2){
        digitalWrite(STRIKE2,HIGH);
        digitalWrite (LOSE,HIGH);
        
        delay (1000);
        digitalWrite (LOSE,LOW);
      }
      if (counter == 3){
        digitalWrite (STRIKE3, HIGH);
        digitalWrite (LOSE,HIGH);
        
        delay (3000);
        digitalWrite (LOSE,LOW);
      }
      
    }
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite (BELL, LOW);
    
  }
  
  else {
      digitalWrite (LED_1, random(0,2)  );
      digitalWrite (LED_2, random(0,2)  );
      digitalWrite (LED_3, random(0,2)  );
      digitalWrite (LED_4, random(0,2)  );
      digitalWrite (LED_5, random(0,2)  );
      digitalWrite (LED_6, random(0,2)  );
      
      
      delay(100);
  }
  

}
