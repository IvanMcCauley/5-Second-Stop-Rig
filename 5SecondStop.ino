#include <LiquidCrystal.h> 

#define button 2
#define ledPin 13  // Pin for LED
#define buzzerPin 6 // Pin for buzzer

int timerMode = 0;  // Tracks state of timer (running or not)
long startTime;  // Stores time when the button is pressed
float elapsedTime = 0.0;  // Stores elapsed time
const float tolerance = 0.01;  // Prevents floating point errors
int lastBatteryPercentage = -1;  // Stores the last recorded battery percentage (set as -1 to not conflict with any possible % values (1-100))

// Initialize the LCD with pin connections
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Define buzzer tones
const int wrongTone[] = {200, 110};  //  Sound for incorrect timing
const int correctTone[] = {262, 294, 330, 349, 392, 440, 494, 523};  // Sound for correct timing

// Binary code to make a battery symbol (rectangle with a pin at the top)
byte batterySymbol[8] = {
  B01110, //   _-_
  B11111, //  |   |
  B10001, //  |   |
  B10001, //  |   | <--- Should look like this
  B10001, //  |   |
  B10001, //  |   |
  B11111, //  |___|
  B00000  //
};

// Initial setup
void setup() {
   lcd.begin(16, 2);  // Set up a 16x2 LCD display
   lcd.createChar(0, batterySymbol);  // Create custom battery symbol
   delay(500);  // Short delay for LCD initialization
   lcd.clear(); 
   pinMode(button, INPUT_PULLUP);  // Set button as input
   pinMode(ledPin, OUTPUT);  // Set LED as output
   pinMode(buzzerPin, OUTPUT);  // Set buzzer as an output
   lcd.print("Press to Start!");  // Initial message on LCD
   noTone(buzzerPin);  // Ensure buzzer is off initially
   digitalWrite(buzzerPin, LOW);  // Second way to ensure buzzer is fully OFF   at startup (just used both to be sure)
}

// Battery percentage function
void displayBatteryPercentage() {
  int analogValue = analogRead(A0);  // Read voltage from Arduino A0 pin
  float batteryVoltage = (analogValue*5.0/1023.0)*((10.0 + 4.7)/4.7);// Convert to actual voltage (as voltage was divided)

  // Convert voltage to percentage (using 6V is 0% and 9V is 100%)
  int batteryPercentage = map(batteryVoltage * 100, 600, 900, 0, 100);
  if (batteryPercentage < 0) batteryPercentage = 0;
  if (batteryPercentage > 100) batteryPercentage = 100; // to keep it in 0-100 range just in case

  // Only update the display if the battery percentage has changed
  if (batteryPercentage != lastBatteryPercentage) {
    lastBatteryPercentage = batteryPercentage;  // Update the last recorded percentage

    lcd.setCursor(14, 1); // placing battery symbol at bottom right of LCD
    lcd.write(byte(0));  // Display the battery symbol

    lcd.setCursor(15, 1); // placing percentage to the right of the battery symbol
    if (batteryPercentage < 10) lcd.print(" ");  // Adding a space for single digit numbers
    lcd.print(batteryPercentage);
    lcd.print("%");  // Display percentage sign
  }
}

// Timing Function
void loop() {
   lcd.setCursor(0, 1);  // Move cursor to second row of LCD
   displayBatteryPercentage();  // Continuously update battery percentage

   // Check if the button is pressed
   if (digitalRead(button) == LOW) {
     if (timerMode == 0) {  // If timer not running
       startTime = millis();  //Start timer
       elapsedTime = 0.0;  
       timerMode = 1;  
       digitalWrite(ledPin, LOW);  //keep led off
       lcd.clear();
       lcd.print("Timer Running...");  //timer running message
       delay(400); // small delay to debounce button
     }
     else if (timerMode == 1) {  // if timer isnt running
       elapsedTime = (millis() - startTime) / 1000.0; //calculates elapsed time in secs
       lcd.setCursor(0, 1);
       lcd.print(elapsedTime, 2);  //prints elapsed time (2 decimal places)
       displayBatteryPercentage();  //displays bat percent if timer is stopped correctly
       if (elapsedTime >= 5.00 - tolerance && elapsedTime <= 5.00 + tolerance) {  
         digitalWrite(ledPin, HIGH);  
         lcd.clear();
         lcd.print("5.00 WELL DONE!");  //sucess message
         displayBatteryPercentage();  // Making sure the battery percentage is displayed again
         for (int i = 0; i < 8; i++) {
           tone(buzzerPin, correctTone[i], 400);  //play each tone of correctTone for 400ms
           delay(400);  
         }
         delay(3000);  // display for 3s
       } else { //if not stopped correctly
         lcd.clear();
         lcd.print(elapsedTime, 2); //prints elapsed time (2 decimal places)
         lcd.print("   Try Again!");  //failure message
         displayBatteryPercentage();  // Making sure the battery percentage is displayed again
         digitalWrite(ledPin, LOW);  //keep LED off

         tone(buzzerPin, wrongTone[0], 100); //play first note of wrongTonefor 100ms  
         delay(250);                         // gap of 250ms between notes
         tone(buzzerPin, wrongTone[1], 500);  //play second note of wrongTone for 100ms  
         delay(500);  

         delay(2000);  // display it for 2s
       }
       timerMode = 0;  
       lcd.clear();
       lcd.print("Press to Start");  // resets 
       displayBatteryPercentage();  // Making sure the battery percentage is displayed again
     }
   }
