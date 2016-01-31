const int SENS_1   = A0;
const int SENS_2   = A1;
const int SENS_3   = A2;
const int SENS_4   = A3;
const int SENS_5   = A4;
const int SENS_6   = A5;
const int LED_1    =  1;
const int LED_2    =  2;
const int LED_3    =  3;
const int LED_4    =  4;
const int LED_5    =  5;
const int LED_6    =  6;
const int STRIKE1  =  7;
const int STRIKE2  =  8;
const int STRIKE3  =  9;
const int BELL     = 10;
const int BUZZ     = 11;
const int GO_LEVER = 12;

const int NUM_OF_SENSORS = 6;
int strike_count = 0;
int val1=0; 
int val2=0;
int val3=0;
int val4=0;
int val5=0;
int val6=0;

/**
 * Create arrays to group sensors, leds, and values
 * IMPORTANT:
 *    Corresponding pins are given the the same array position (index)
 *    EX: SENS_2, LED_2 and val2 are all the second item, and index[1]
 */
int SENSOR_LIST[]  = { SENS_1, SENS_2, SENS_3, SENS_4, SENS_5, SENS_6  };
int LED_LIST[]     = {  LED_1,  LED_2,  LED_3,  LED_4,  LED_5,  LED_6  };
int VALUE_LIST[]   = {   val1,   val2,   val3,   val4,   val5,   val6  };

void setup() {
  // Set the sensor pins input mode
  pinMode (SENS_1, INPUT);
  pinMode (SENS_2, INPUT);
  pinMode (SENS_3, INPUT);
  pinMode (SENS_4, INPUT);
  pinMode (SENS_5, INPUT);
  pinMode (SENS_6, INPUT);
  pinMode (GO_LEVER, INPUT);
  
  // set the bell, buzzer and LED pins output mode
  pinMode(BUZZ, OUTPUT );
  pinMode(BELL, OUTPUT );
  pinMode(LED_1, OUTPUT );
  pinMode(LED_2, OUTPUT );
  pinMode(LED_3, OUTPUT );
  pinMode(LED_4, OUTPUT );
  pinMode(LED_5, OUTPUT );
  pinMode(LED_6, OUTPUT );
  pinMode(STRIKE1, OUTPUT );
  pinMode(STRIKE2, OUTPUT );
  pinMode(STRIKE3, OUTPUT );

  // Turn off strike LEDs
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
  
  if ( digitalRead(GO_LEVER) == LOW && strike_count <3) // Three tries
  {
    /*
     * List values are referenced by their index (position starting at 0)
     * This loop starts with index at 0, and ends when index is 1 minus the list size.
     * we want to stop when index is less than the size of the list because indexes 
     * start at 0, which means SENS_1 is at position [0] and SENS_6 is at position [5]
     * 
     * What the below loop does:
     *  set the value of VALUE_LIST[0] to the value of the sensor at SENSOR_LIST[0]
     *  Add 1 to the index and repeat
     *  set the value of VALUE_LIST[1] to the value of the sensor at SENSOR_LIST[1]
     *  Contnue until we have set every value in VALUE_LIST
     *  
     */
    for ( int sens_idx=0; sens_idx < NUM_OF_SENSORS; sens_idx++ )
    {
      VALUE_LIST[sens_idx] = digitalRead( SENSOR_LIST[sens_idx] );
    }
    
    //dramatic 3 blink drum roll
    for ( int blink_counter = 0; blink_counter < 7; blink_counter = blink_counter+1 )
    {
      for (int led_idx = 0; led_idx <  NUM_OF_SENSORS; led_idx++ )
      {
        digitalWrite( LED_LIST[led_idx], (blink_counter+led_idx+2) % 2 );
      }
      delay(300);
     }



     // Loop over all values and set corresponding LEDs
     for (int led_idx = 0; led_idx < NUM_OF_SENSORS; led_idx++)
     {
      digitalWrite( LED_LIST[led_idx], !VALUE_LIST[led_idx] );

      for (int blink_counter = 0; blink_counter < 4; blink_counter++ )
      {
        // loop over all unchecked leds (start at current led_index + 1) and set to alternating state
        for (int unchked_idx = (led_idx + 1); unchked_idx < NUM_OF_SENSORS; unchked_idx++)
        {
          digitalWrite( LED_LIST[unchked_idx], (blink_counter+unchked_idx+3) % 2 );
        }
        delay (300);
      }      
    }

    if (VALUE_LIST[0]==0 && VALUE_LIST[1]==0 && VALUE_LIST[2]==0 && VALUE_LIST[3]==0 && VALUE_LIST[4]==0 && VALUE_LIST[5]==0) //all answers correct
    {
      digitalWrite (BELL, HIGH);
      delay (3000);
      digitalWrite (BELL, LOW);
      while (true){
        delay(10000);
      }
    }
    else {
      strike_count = strike_count + 1;
      if (strike_count == 1){
        digitalWrite(STRIKE1,HIGH);
        digitalWrite (BUZZ,HIGH);
        delay (1000);
        digitalWrite (BUZZ,LOW); 
      }
      else if (strike_count == 2){
        digitalWrite(STRIKE2,HIGH);
        digitalWrite (BUZZ,HIGH);
        delay (1000);
        digitalWrite (BUZZ,LOW);
      }
      else if (strike_count == 3){
        digitalWrite (STRIKE3, HIGH);
        digitalWrite (BUZZ,HIGH);
        delay (3000);
        digitalWrite (BUZZ,LOW);
      }
    }
    for (int led_idx = 0; led_idx < NUM_OF_SENSORS; led_idx++)
    {
      digitalWrite (LED_LIST[led_idx], random(0,2)  );
    }
  }
  
  else {
    for (int led_idx = 0; led_idx < NUM_OF_SENSORS; led_idx++)
    {
      digitalWrite (LED_LIST[led_idx], random(0,2)  );
    }
    delay(100);
  }
}
