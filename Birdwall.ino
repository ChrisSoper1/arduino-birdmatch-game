/**
 * This is where we define every variable we are going to use
 * in this program.  When this section of code is run, the arduino
 * makes room for each variable.
 * 
 * We can also set the value of the variables here, but we are not required to.
 */


/**
 * First we "name" the ports (also called pins) we are using with variables.
 * This is done so the code is easier for humans to read. and is
 * turned into binary (1s and 0s) when it is sent to the arduino.
 * 
 * Each value (A0-A5 and 1-12) refers to a port on the board.
 */

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
int BUZZER   = 11;
int GO_LEVER = 12;

/**
 * Then we tell the arduino to make room for 6 variables.
 * These will store whether an answer is correct.
 */
int val1 = 1;
int val2 = 1;
int val3 = 1;
int val4 = 1;
int val5 = 1;
int val6 = 1;

// Last, create a counter that stores how many strikes the player has.
int counter = 0;

/**
 * This is the first block of code the arduino runs after being turned on. 
 * To run this function again, the reset button needs to be pressed
 * 
 * The purpose of this function is to set up everything the program needs before running
 * like what we want the ports to do, and how many strikes you start out with
 */
void setup() {
// Tell the arduino that we will get data from the sensor and start button pins.
  pinMode (SENS_1, INPUT);
  pinMode (SENS_2, INPUT);
  pinMode (SENS_3, INPUT);
  pinMode (SENS_4, INPUT);
  pinMode (SENS_5, INPUT);
  pinMode (SENS_6, INPUT);
  pinMode (GO_LEVER, INPUT);
  
  // Tell the arduino that we will send data from the LED, BELL, and buzzer pins.
  pinMode (LED_1, OUTPUT);
  pinMode (LED_2, OUTPUT);
  pinMode (LED_3, OUTPUT);
  pinMode (LED_4, OUTPUT);
  pinMode (LED_5, OUTPUT);
  pinMode (LED_6, OUTPUT);
  pinMode (STRIKE1, OUTPUT);
  pinMode (STRIKE2, OUTPUT);
  pinMode (STRIKE3, OUTPUT);
  pinMode (BUZZER, OUTPUT);
  pinMode (BELL, OUTPUT);

  // Set the strike counter to 0
  counter = 0;
  
  // Turn off the Strike LEDs
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

/**
 * This is the main part of the program, and runs after the program has been
 * set up by the setup() function above.  Once the arduino gets to the end of
 * this section of code, it runs it again (and again, and again, and again....)
 * until it is reset or turned off.  
 * 
 * The arduino is a 16MHz computer, which means that it can 
 * read 16,000 lines of code every second!
 * 
 * Compare this to the iPhone 6, which has two 1.4GHz cores, 
 * which can EACH read 140,000 lines of code a second, for a 
 * total of 280,000 lines of code EVERY SECOND!
 */
void loop() {
  /**
   * The first thing we do is check the start button to see if it has been pressed.
   * This is done by "reading" the value from the button pin. If the power level is LOW
   * then we know that the button is being pressed.
   * 
   * We also check to see if the strike counter is less than 3, because if there is 
   * 3 or more strikes, we do not want to do anything.
   * 
   * If both of those conditions are true, we run the next block of code.
   */
  if ( digitalRead(GO_LEVER) == LOW && counter <3) // Three tries
  {
    // Record the player's answers in variables
    val1 = digitalRead(SENS_1);
    val2 = digitalRead(SENS_2);
    val3 = digitalRead(SENS_3);
    val4 = digitalRead(SENS_4);
    val5 = digitalRead(SENS_5);
    val6 = digitalRead(SENS_6);

    // Turn of the LEDs
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    
    // Wait 300 milliseconds (0.3 seconds) before continuing
    delay(300);
    //dramatic 3 blink drum roll
    for (int i = 0; i <3 ; i = i+1)
    {
      // Turn all LEDs on
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, HIGH);
      digitalWrite(LED_5, HIGH);
      digitalWrite(LED_6, HIGH);

      // Wait 300ms
      delay(300);

      // Turn all LEDs off
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      digitalWrite(LED_5, LOW);
      digitalWrite(LED_6, LOW);

      // Wait 300ms
      delay(300);
    }
    /**
     * The sensors send a LOW signal when the answer is correct and a HIGH when wrong
     * but a HIGH signal turns on the green LED a LOW signal turns on the red LED, we send
     * the LED the opposite signal that we get from the sensor.  The exclaimation mark (!)
     * is used to turn a variable into its opposite.
     */
     digitalWrite(LED_1, !val1);
     delay(1000);
    
     digitalWrite(LED_2, !val2);
     delay(1000);
    
     digitalWrite(LED_3, !val3);
     delay(1000);
    
     digitalWrite(LED_4, !val4);
     delay(1000);
 
     digitalWrite(LED_5, !val5);
     delay(1000);
    
     digitalWrite(LED_6, !val6);
     delay(1000);

    // Check if all sensors are LOW (correct)
    if (val1 == 0 && val2 == 0 && val3 == 0 && val4 == 0 && val5 == 0 && val6 == 0) //all answers correct
    {
      // Turn on the bell for 3 seconds
      digitalWrite (BELL, HIGH);
      delay (3000);
      digitalWrite (BELL, LOW);
      
      /** 
       *  while(true) is an infinate loop, which means once the arduino tries to run this line,  
       *  it will be stuck here forever (or until it is reset).
       */
      // Stop the game after winning
      while (true){}
    }
    else {
      // Not all of the answers were correct
      // Add a strike 
      counter = counter + 1;

      // Turn on one light for each strike and sound the buzzer
      if (counter == 1){
        digitalWrite(STRIKE1,HIGH);
        digitalWrite (BUZZER,HIGH);
        delay (1000);
        digitalWrite (BUZZER,LOW); 
      }
      if (counter == 2){
        digitalWrite(STRIKE2,HIGH);
        digitalWrite (BUZZER,HIGH);
        delay (1000);
        digitalWrite (BUZZER,LOW);
      }
      if (counter == 3){
        digitalWrite (STRIKE3, HIGH);
        digitalWrite (BUZZER,HIGH);
        delay (3000);
        digitalWrite (BUZZER,LOW);
      }  
    }
    // Turn off the LEDs and the bell so the game can be played again
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    digitalWrite(LED_5, LOW);
    digitalWrite(LED_6, LOW);
    digitalWrite (BELL, LOW);
    
  }
  
  else {
    // Randomly turn each LED to either LOW (0) or HIGH (1) for 100ms
    digitalWrite (LED_1, random(0,2)  );
    digitalWrite (LED_2, random(0,2)  );
    digitalWrite (LED_3, random(0,2)  );
    digitalWrite (LED_4, random(0,2)  );
    digitalWrite (LED_5, random(0,2)  );
    digitalWrite (LED_6, random(0,2)  );
    delay(100);
  }
}
