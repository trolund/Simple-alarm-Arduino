#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define onLED 4 
#define offLED 5 
#define buttonPin 6 

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int buttonState = 0; 

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers



void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  // LED
  pinMode(onLED, OUTPUT);
  pinMode(offLED, OUTPUT); 

  pinMode(buttonPin, INPUT);
    
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Alarm er tændt"); // print some text in Serial Monitor
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println(" cm");

  if(distance > 5 && state) {
    digitalWrite(onLED, HIGH);   // turn the LED on (HIGH is the voltage level)
    
    // Serial.println("hyl");
    }
   else {
     digitalWrite(onLED, LOW);   // turn the LED on (HIGH is the voltage level)
    
     // Serial.println("stop");
 
    }

  reading = digitalRead(buttonPin);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();    
  }

     if(state) {
      digitalWrite(offLED, HIGH);
      Serial.println("active");
     } 
     else {
      digitalWrite(offLED, LOW);
      Serial.println("inactive");
     }

  previous = reading;
    
}
