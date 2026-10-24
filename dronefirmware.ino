#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <DabbleESP32.h>
#include <ESP32Servo.h>

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

#define ESC1_PIN 25 
#define ESC2_PIN 26
#define ESC3_PIN 14  
#define ESC4_PIN 12
#define pump 18

#define RX 16;
#define TX 17;

// ESC throttle range
#define MIN_THROTTLE 1000 
#define MAX_THROTTLE 2000

int throttle = MIN_THROTTLE;

unsigned long lastThrottleUpdate = 0;
unsigned long update2 = 0;
const unsigned long throttleInterval = 1000;
const unsigned long Interval2 = 10000;

bool flagname = false;
bool tomato = false;

void setup() {

  // Bluetooth name
  Dabble.begin("ESP32_MOTOR");
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  pinMode(18, OUTPUT);


  // ESC PWM
  ESC1.setPeriodHertz(50);
  ESC2.setPeriodHertz(50);
  ESC3.setPeriodHertz(50);
  ESC4.setPeriodHertz(50);


  ESC1.attach(ESC1_PIN, MIN_THROTTLE, MAX_THROTTLE);
  ESC2.attach(ESC2_PIN, MIN_THROTTLE, MAX_THROTTLE);
  ESC3.attach(ESC3_PIN, MIN_THROTTLE, MAX_THROTTLE);
  ESC4.attach(ESC4_PIN, MIN_THROTTLE, MAX_THROTTLE);

  // ESC ARM
  ESC1.writeMicroseconds(MIN_THROTTLE);
  ESC2.writeMicroseconds(MIN_THROTTLE);
  ESC3.writeMicroseconds(MIN_THROTTLE);
  ESC4.writeMicroseconds(MIN_THROTTLE);

  digitalWrite(18, LOW);

  delay(3000);
}

void loop() {


  Dabble.processInput();

  if (Serial2.available()) {
    String msg = Serial2.readStringUntil('\n');
    msg.trim();  // removes any stray \r or whitespace

    if (msg == "1") {
        Serial.println("Arecanut detected!");
        flagname = false;
        throttle = throttle;
        tomato = true;
        Serial.println("Stable at throttle");
        digitalWrite(18, HIGH);
        delay(10000);

        // turn LED on
    } else if (msg == "0") {
        Serial.println("Not detected");
        // turn LED off
    }


}

  if(tomato == true)
  {
    if(throttle>=1000){
      unsigned long now2 = millis();
      if(throttle>=1000){
      if(now2 - update2 >= throttleInterval)
      {
        throttle = throttle - 50;
        update2 = now2;
        digitalWrite(18, LOW);
      }
    
    }
    
  }
    
  }

  // UP = increase throttle
  if (GamePad.isUpPressed()) {
    throttle += 5;
  }

  // DOWN = decrease throttle
  if (GamePad.isDownPressed()) {
    throttle -= 5;
  }

  // Triangle = emergency stop
  if (GamePad.isTrianglePressed()) {
    throttle = MIN_THROTTLE;
    flagname = false;
  }

  if(GamePad.isCrossPressed()){
    flagname = true;
    tomato = false;
  }
    if(flagname==true){
      unsigned long now = millis();
    if(throttle<=1600){
    if((now - lastThrottleUpdate >= throttleInterval) && (flagname==true))
    {
      throttle = throttle+50;
      Serial.println(throttle);
      lastThrottleUpdate = now;
    }
    }
    }

  // Keep throttle within limits
  throttle = constrain(throttle, MIN_THROTTLE, MAX_THROTTLE);

  // Both ESCs receive same throttle
  ESC1.writeMicroseconds(throttle);
  ESC2.writeMicroseconds(throttle);
  ESC3.writeMicroseconds(throttle);
  ESC4.writeMicroseconds(throttle);


  delay(20);
}