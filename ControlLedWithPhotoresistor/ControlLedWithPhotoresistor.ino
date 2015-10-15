    /* Photocell simple testing sketch. 
     
    Connect one end of the photocell to 5V, the other end to Analog 0.
    Then connect one end of a 10K resistor from Analog 0 to ground 
    Connect LED from pin 11 through a resistor to ground 
    For more information see http://learn.adafruit.com/photocells */
     
    int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
    int pirSensorPin = 2;
    int photocellReading;     // the analog reading from the sensor divider
    int LEDpin = 11;          // connect Red LED to pin 11 (PWM pin)
    int LEDbrightnessLow=5;        //
    int LEDbrightnessHigh = 175;
    int modeNo2Limit = 200;
    int modeNo1Limit = 450;
    int modeNo0Limit = 600;
    int prevmode = 0;
    int currentBrightness;
    int pirSensor;
    int LEAVE_LED_LIT_TIME = 60; //leave led lit this number of cycles
    int counterForLedLit=0; 

    int modeNo = 0;
    void setup(void) {
      // We'll send debugging information via the Serial monitor
      pinMode(pirSensorPin, INPUT_PULLUP);
      
      Serial.begin(9600);
      setBrightnessOfLed();  
       
    }
    void loop(void) {
      photocellReading = analogRead(photocellPin);
      pirSensor = digitalRead(pirSensorPin);
      Serial.print("Analog reading = ");
      Serial.println(photocellReading);     // the raw analog reading
      Serial.println(modeNo);
      if (prevmode!=modeNo){
          setBrightnessOfLed();
        }
      if (modeNo==2){
        counterForLedLit++;
        if (pirSensor==LOW){
          counterForLedLit=0; 
        }
        Serial.println(counterForLedLit);
        //delay(6000);
        //pirSensor = digitalRead(pirSensorPin);
        if (counterForLedLit >LEAVE_LED_LIT_TIME){
          modeNo=1;
        }
        
        }
      if (modeNo==0){  
        if (photocellReading<modeNo1Limit){
          int counter = 0;
          while(counter <20){
            if (analogRead(photocellPin)>modeNo1Limit){
              break;
            }
            delay(1000);
            counter++;
          }
          if(counter==20){
            modeNo=1;
          }
          
        }
      }  //end mode0
      if (modeNo==1){
        if (photocellReading>modeNo0Limit){
          modeNo=0;
        }
        if (pirSensor==LOW){ 
          modeNo=2;
        }
        
      }
      
      delay(1000);
      
    }
    void setBrightnessOfLed(){
      if (modeNo==0){
        Serial.print("Entering mode 0");
        //analogWrite(LEDpin,0);
        //currentBrightness=0;
        stepBrightness(0);

      }
      if (modeNo==1){
        Serial.print("Entering mode 1");
        //analogWrite(LEDpin,LEDbrightnessLow);
        //currentBrightness=LEDbrightnessLow;
        stepBrightness(LEDbrightnessLow);
      }
      if (modeNo==2){
        Serial.print("Entering mode 2");
        //analogWrite(LEDpin,LEDbrightnessHigh);
        //currentBrightness = LEDbrightnessHigh;
        stepBrightness(LEDbrightnessHigh);
      }
      
      prevmode=modeNo;
    }
    void stepBrightness(int endPoint){
      if (currentBrightness==endPoint){
        return;
      }
      if(currentBrightness<endPoint){
        setIntensity(currentBrightness+1);
      }
      if(currentBrightness>endPoint){
        setIntensity(currentBrightness-1);
      }
      delay(30);
      stepBrightness(endPoint);
    }
    void setIntensity(int value){
      analogWrite(LEDpin,value);
      currentBrightness=value;
    }
    
    
