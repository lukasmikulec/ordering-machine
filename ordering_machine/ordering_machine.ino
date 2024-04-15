int leftButton = 4; // define left button pin
int middleButton = 3; // define middle button pin
int rightButton = 2; // define right button pin

String screenPage = "Start"; // initialize a string with a value to check if this is a beginning of the program or not

#include <Wire.h> // import library for communication with I2C devices
#include <LiquidCrystal_I2C.h> // import library for the LCD screen
#include <FastLED.h> // import library for the LED stripe
#include <Servo.h> // import library for the servo motors

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27, with 20 characters, and 4 lines

#define LED_PIN     7   // define the pin of the LED stripe
#define NUM_LEDS    45  // define the number of LEDs on the LED stripe

CRGB leds[NUM_LEDS]; // define array type CRGB, each member contains three bite data members (for red, green, and blue)

Servo ServoMeat; // create a Servo object for the servo motor that displays nudge against meat options
Servo ServoHealth; // create a Servo object for the servo motor that displays praise for choosing non-meat options

int servoMeatPin = 9; // define the pin of the servo motor for meat options
int servoHealthPin = 10; // define the pin of the servo motor for non-meat options


String whichButton() { // define a function which will check which button was pressed
  String button_nr = "None"; // define a variable which will be outputted by the function
  
  if (digitalRead(rightButton) == HIGH) { // if right button was pressed
    button_nr = "right";  // output "right"
  }
  else if (digitalRead(middleButton) == HIGH) { // if the middle button was pressed
    button_nr = "middle"; // output "middle"
  }
  else if (digitalRead(leftButton) == HIGH) { // if the left button was pressed
    button_nr = "left"; // output "left"
  }
  else { // if no button was pressed
    button_nr = "None"; // output "None"
  }
  return button_nr;  // return which button was pressed (including none)
}

String whichButtonClicked = whichButton(); // create a variable which will store which button was clicked the last

void setup() {
  pinMode (leftButton, INPUT); // set left button as input
  pinMode (middleButton, INPUT); // set middle button as input
  pinMode (rightButton, INPUT); // set right button as input

  lcd.init();         // initialize the LCD screen
  lcd.backlight();    // turn on the LCD screen backlight

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); // initialize the LED stripe using parameters define above

  ServoMeat.attach(servoMeatPin); // associate the servo motor object with the pin the servo motor is connected to
  ServoHealth.attach(servoHealthPin); // associate the servo motor object with the pin the servo motor is connected to

  ServoHealth.write(160); // set the Servo health to the initial position

  Serial.begin(9600); // initialize the Serial Monitor for tracking
}

void loop() {
  if (screenPage == "Start") { // if this is the beginning of the program
    FastLED.clear();  // clear previously turned-on LEDs
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(6, 0); // on first line starting with the 7th character
    lcd.print("WELCOME"); // write
    lcd.setCursor(4, 1); // on second line starting with the 5th character
    lcd.print("Order here"); // write
    lcd.setCursor(0, 3); // on fourth line starting with the 1st character
    lcd.print("Press yellow button"); // write
    for (int i = 4; i <= 5; i++) { // for the left side in the middle on the LED stripe
        leds[i] = CRGB (255, 255, 0); // set the LED to yellow
        FastLED.show(); // turn the LED to that color
        delay(40); // wait 40 miliseconds
    }
      for (int i = 36; i <= 37; i++) { // for the right side in the middle on the LED stripe
        leds[i] = CRGB (255, 255, 0); // set the LED to yellow
        FastLED.show(); // turn the LED to that color
        delay(40); // wait 40 miliseconds
    }
    delay(500); // wait 500 miliseconds so the system has the chance to notice button press
    whichButtonClicked = whichButton(); // check which button was pressed (including none)

    while (whichButtonClicked == "None" || whichButtonClicked == "left" || whichButtonClicked == "right") {// run until the middle button is pressed
      whichButtonClicked = whichButton(); // check if any button was clicked
    }
    screenPage = "MenuFirst"; // set the screen to be displayed to the first page of menu after pushing the middle button
  }

  if (screenPage == "MenuFirst") { // if Menu 1 page should be displayed
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(1, 0); // on first line starting with the 2nd character
    lcd.print("Stir fried Bok choy"); // write
    lcd.setCursor(19, 1); // on second line starting with the 20th character
    lcd.print(">"); // write the indicator that user can go right in the menu selection
    lcd.setCursor(7, 3); // on fourth line starting with the 8th character
    lcd.print("Select"); // write
    FastLED.clear();  // clear previously turned-on LEDs
    for (int i = 2; i <= 3; i++) { // for the left side in the middle on the LED stripe
        leds[i] = CRGB (0, 128, 0); // set the LED to green
        FastLED.show(); // turn the LED to that color
        delay(40); // wait 40 miliseconds
      }
      for (int i = 38; i <= 39; i++) { // for the right side in the middle on the LED stripe
        leds[i] = CRGB (0, 128, 0); // set the LED to green
        FastLED.show(); // turn the LED to that color
        delay(40); // wait 40 miliseconds
      }
    
    delay(500); // wait 500 miliseconds so the system has the chance to notice button press
    whichButtonClicked = whichButton(); // check which button was pressed (including none)
    
    while (whichButtonClicked == "None" || whichButtonClicked == "left") {// run until the right or middle button is pressed
      whichButtonClicked = whichButton(); // check which button was pressed (including none)
    }

    if (whichButtonClicked == "right") { // if right button was pressed
      screenPage = "MenuSecond";  // set the next page to be displayed to Menu 2
    }
    else if (whichButtonClicked == "middle") { // if the middle button was pressed
      screenPage = "Checkout"; // set the next page to be displayed to Checkout page
    }
  }

  if (screenPage == "MenuSecond") { // if Menu 2 page should be displayed
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(2, 0); // on first line starting with the 3rd character
    lcd.print("Plain cheung fen"); // write
    lcd.setCursor(0, 1); // on second line starting with the 1st character
    lcd.print("<"); // write the indicator that user can go left in the menu selection
    lcd.setCursor(19, 1); // on second starting with the 20th character
    lcd.print(">"); // write the indicator that user can go right in the menu selection
    lcd.setCursor(7, 3); // on fourth line starting with the 8th character
    lcd.print("Select"); // write
    FastLED.clear();  // clear previously turned-on LEDs
    for (int i = 2; i <= 3; i++) { // for the left side in the middle on the LED stripe
        leds[i] = CRGB (0, 128, 0); // set the LED to green
        FastLED.show(); // turn the LED to that color
        delay(40); // wait 40 miliseconds
    }
    for (int i = 38; i <= 39; i++) { // for the right side in the middle on the LED stripe
      leds[i] = CRGB (0, 128, 0); // set the LED to green
      FastLED.show(); // turn the LED to that color
      delay(40); // wait 40 miliseconds
    }
    
    delay(500); // wait 500 miliseconds so the system has the chance to notice button press
    whichButtonClicked = whichButton(); // check which button was pressed (including none)

    while (whichButtonClicked == "None") {// run until the right, middle, or left button is pressed
      whichButtonClicked = whichButton(); // check which button was pressed (including none)
      Serial.println(whichButtonClicked);
    }

    if (whichButtonClicked == "right") { // if right button was pressed
      screenPage = "MenuThird";  // set the next page to be displayed to Menu 3
    }
    else if (whichButtonClicked == "middle") { // if the middle button was pressed
      screenPage = "Checkout"; // set the next page to be displayed to Checkout page
    }
    else if (whichButtonClicked == "left") { // if the left button was pressed
      screenPage = "MenuFirst"; // set the next page to be displayed to Menu 1 page
    }
  }

  if (screenPage == "MenuThird") { // if Menu 3 page should be displayed
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(4, 0); // on first line starting with the 5th character
    lcd.print("Pineapple bun"); // write
    lcd.setCursor(0, 1); // on second line starting with the 1st character
    lcd.print("<"); // write the indicator that user can go left in the menu selection
    lcd.setCursor(19, 1); // on second starting with the 20th character
    lcd.print(">"); // write the indicator that user can go right in the menu selection
    lcd.setCursor(7, 3); // on fourth line starting with the 8th character
    lcd.print("Select"); // write
    FastLED.clear();  // clear previously turned-on LEDs
    for (int i = 2; i <= 3; i++) { // for the left side in the middle on the LED stripe
        leds[i] = CRGB (0, 128, 0); // set the LED to green
        FastLED.show(); // turn the LED to that color
        delay(40); // wait 40 miliseconds
    }
    for (int i = 38; i <= 39; i++) { // for the right side in the middle on the LED stripe
      leds[i] = CRGB (0, 128, 0); // set the LED to green
      FastLED.show(); // turn the LED to that color
      delay(40); // wait 40 miliseconds
    }
    
    delay(500); // wait 500 miliseconds so the system has the chance to notice button press
    whichButtonClicked = whichButton(); // check which button was pressed (including none)

    while (whichButtonClicked == "None") {// run until the right, middle, or left button is pressed
      whichButtonClicked = whichButton(); // check which button was pressed (including none)
      Serial.println(whichButtonClicked);
    }

    if (whichButtonClicked == "right") { // if right button was pressed
      screenPage = "MenuFourth";  // set the next page to be displayed to Menu 4
    }
    else if (whichButtonClicked == "middle") { // if the middle button was pressed
      screenPage = "Checkout"; // set the next page to be displayed to Checkout page
    }
    else if (whichButtonClicked == "left") { // if the left button was pressed
      screenPage = "MenuSecond"; // set the next page to be displayed to Menu 2 page
    }
  }

  if (screenPage == "MenuFourth") { // if Menu 4 page should be displayed
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(4, 0); // on first line starting with the 5th character
    lcd.print("Ma lai gao"); // write
    lcd.setCursor(0, 1); // on second line starting with the 1st character
    lcd.print("<"); // write the indicator that user can go left in the menu selection
    lcd.setCursor(19, 1); // on second starting with the 20th character
    lcd.print(">"); // write the indicator that user can go right in the menu selection
    lcd.setCursor(7, 3); // on fourth line starting with the 8th character
    lcd.print("Select"); // write
    FastLED.clear();  // clear previously turned-on LEDs
    for (int i = 2; i <= 3; i++) { // for the left side in the middle on the LED stripe
        leds[i] = CRGB (0, 128, 0); // set the LED to green
        FastLED.show(); // turn the LED to that color
        delay(40); // wait 40 miliseconds
    }
    for (int i = 38; i <= 39; i++) { // for the right side in the middle on the LED stripe
      leds[i] = CRGB (0, 128, 0); // set the LED to green
      FastLED.show(); // turn the LED to that color
      delay(40); // wait 40 miliseconds
    }
    
    delay(500); // wait 500 miliseconds so the system has the chance to notice button press
    whichButtonClicked = whichButton(); // check which button was pressed (including none)

    while (whichButtonClicked == "None") {// run until the right, middle, or left button is pressed
      whichButtonClicked = whichButton(); // check which button was pressed (including none)
    }

    if (whichButtonClicked == "right") { // if right button was pressed
      screenPage = "MenuFifth";  // set the next page to be displayed to Menu 5
    }
    else if (whichButtonClicked == "middle") { // if the middle button was pressed
      screenPage = "Checkout"; // set the next page to be displayed to Checkout page
    }
    else if (whichButtonClicked == "left") { // if the left button was pressed
      screenPage = "MenuThird"; // set the next page to be displayed to Menu 3 page
    }
  }
  
  if (screenPage == "MenuFifth") { // if Menu 5 page should be displayed
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(4, 0); // on first line starting with the 5th character
    lcd.print("Cha Siu bun"); // write
    lcd.setCursor(0, 1); // on second line starting with the 1st character
    lcd.print("<"); // write the indicator that user can go left in the menu selection
    lcd.setCursor(19, 1); // on second line starting with the 19th character
    lcd.print(">"); // write the indicator that user can go right in the menu selection
    lcd.setCursor(7, 3); // on fourth line starting with the 8th character
    lcd.print("Select"); // write
    FastLED.clear();  // clear previously turned-on LEDs
    for (int i = 6; i <= 7; i++) { // for the left side in the middle on the LED stripe
        leds[i] = CRGB (255, 0, 0); // set the LED to red
        FastLED.show(); // turn the LED to that color
        delay(40); // wait 40 miliseconds
    }
    for (int i = 34; i <= 35; i++) { // for the right side in the middle on the LED stripe
      leds[i] = CRGB (255, 0, 0); // set the LED to red
      FastLED.show(); // turn the LED to that color
      delay(40); // wait 40 miliseconds
    }
    
    delay(500); // wait 500 miliseconds so the system has the chance to notice button press
    whichButtonClicked = whichButton(); // check which button was pressed (including none)

    while (whichButtonClicked == "None") {// run until the right, middle, or left button is pressed
      whichButtonClicked = whichButton(); // check which button was pressed (including none)
    }
    
    if (whichButtonClicked == "right") { // if right button was pressed
      screenPage = "MenuSixth";  // set the next page to be displayed to Menu 6
    }
    else if (whichButtonClicked == "middle") { // if the middle button was pressed
      screenPage = "CheckoutCheck"; // set the next page to be displayed to Checkout confirmation page
    }
    else if (whichButtonClicked == "left") { // if the left button was pressed
      screenPage = "MenuFourth"; // set the next page to be displayed to Menu 4 page
    }
  }

  if (screenPage == "MenuSixth") { // if Menu 6 page should be displayed
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(4, 0); // on first line starting with the 5th character
    lcd.print("Pork Siu Mai"); // write
    lcd.setCursor(0, 1); // on second line starting with the 1st character
    lcd.print("<"); // write the indicator that user can go left in the menu selection
    lcd.setCursor(19, 1); // on second line starting with the 20th character
    lcd.print(">"); // write the indicator that user can go right in the menu selection
    lcd.setCursor(7, 3); // on fourth line starting with the 7th character
    lcd.print("Select"); // write
    FastLED.clear();  // clear previously turned-on LEDs
    for (int i = 6; i <= 7; i++) { // for the left side in the middle on the LED stripe
        leds[i] = CRGB (255, 0, 0); // set the LED to red
        FastLED.show(); // turn the LED to that color
        delay(40); // wait 40 miliseconds
    }
    for (int i = 34; i <= 35; i++) { // for the right side in the middle on the LED stripe
      leds[i] = CRGB (255, 0, 0); // set the LED to red
      FastLED.show(); // turn the LED to that color
      delay(40); // wait 40 miliseconds
    }
    
    delay(500); // wait 500 miliseconds so the system has the chance to notice button press
    whichButtonClicked = whichButton(); // check which button was pressed (including none)

    while (whichButtonClicked == "None") {// run until the right, middle, or left button is pressed
      whichButtonClicked = whichButton(); // check which button was pressed (including none)
    }
    
    if (whichButtonClicked == "right") { // if right button was pressed
      screenPage = "MenuSeventh";  // set the next page to be displayed to Menu 7
    }
    else if (whichButtonClicked == "middle") { // if the middle button was pressed
      screenPage = "CheckoutCheck"; // set the next page to be displayed to Checkout confirmation page
    }
    else if (whichButtonClicked == "left") { // if the left button was pressed
      screenPage = "MenuFifth"; // set the next page to be displayed to Menu 5 page
    }
  }

  if (screenPage == "MenuSeventh") { // if Menu 7 page should be displayed
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(7, 0); // on first line starting with the 8th character
    lcd.print("Ha Gao"); // write
    lcd.setCursor(0, 1); // on second line starting with the 1st character
    lcd.print("<"); // write the indicator that user can go left in the menu selection
    lcd.setCursor(19, 1); // on second line starting with the 20th character
    lcd.print(">"); // write the indicator that user can go right in the menu selection
    lcd.setCursor(7, 3); // on fourth line starting with the 7th character
    lcd.print("Select"); // write
    FastLED.clear();  // clear previously turned-on LEDs
    for (int i = 6; i <= 7; i++) { // for the left side in the middle on the LED stripe
        leds[i] = CRGB (255, 0, 0); // set the LED to red
        FastLED.show(); // turn the LED to that color
        delay(40); // wait 40 miliseconds
    }
    for (int i = 34; i <= 35; i++) { // for the right side in the middle on the LED stripe
      leds[i] = CRGB (255, 0, 0); // set the LED to red
      FastLED.show(); // turn the LED to that color
      delay(40); // wait 40 miliseconds
    }
    
    delay(500); // wait 500 miliseconds so the system has the chance to notice button press
    whichButtonClicked = whichButton(); // check which button was pressed (including none)

    while (whichButtonClicked == "None") {// run until the right, middle, or left button is pressed
      whichButtonClicked = whichButton(); // check which button was pressed (including none)
    }
    
    if (whichButtonClicked == "right") { // if right button was pressed
      screenPage = "MenuEight";  // set the next page to be displayed to Menu 8
    }
    else if (whichButtonClicked == "middle") { // if the middle button was pressed
      screenPage = "CheckoutCheck"; // set the next page to be displayed to Checkout confirmation page
    }
    else if (whichButtonClicked == "left") { // if the left button was pressed
      screenPage = "MenuSixth"; // set the next page to be displayed to Menu 7 page
    }
  }

  if (screenPage == "MenuEight") { // if Menu 8 page should be displayed
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(4, 0); // on first line starting with the 5th character
    lcd.print("Xiao long bao"); // write
    lcd.setCursor(0, 1); // on second line starting with the 1st character
    lcd.print("<"); // write the indicator that user can go left in the menu selection
    lcd.setCursor(7, 3); // on fourth line starting with the 8th character
    lcd.print("Select"); // write
    FastLED.clear();  // clear previously turned-on LEDs
    for (int i = 6; i <= 7; i++) { // for the left side in the middle on the LED stripe
        leds[i] = CRGB (255, 0, 0); // set the LED to red
        FastLED.show(); // turn the LED to that color
        delay(40); // wait 40 miliseconds
    }
    for (int i = 34; i <= 35; i++) { // for the right side in the middle on the LED stripe
      leds[i] = CRGB (255, 0, 0); // set the LED to red
      FastLED.show(); // turn the LED to that color
      delay(40); // wait 40 miliseconds
    }
    
    delay(500); // wait 500 miliseconds so the system has the chance to notice button press
    whichButtonClicked = whichButton(); // check which button was pressed (including none)

    while (whichButtonClicked == "None" || whichButtonClicked == "right") {// run until the middle or left button is pressed
      whichButtonClicked = whichButton(); // check which button was pressed (including none)
    }
    
    if (whichButtonClicked == "middle") { // if the middle button was pressed
      screenPage = "CheckoutCheck"; // set the next page to be displayed to Checkout confirmation page
    }
    else if (whichButtonClicked == "left") { // if the left button was pressed
      screenPage = "MenuSeventh"; // set the next page to be displayed to Menu 7 page
    }
  }

  if (screenPage == "Checkout") { // if Checkout page should be displayed
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(2, 1); // on first line starting with the 3th character
    lcd.print("Order successful"); // write

    ServoHealth.write(85); // turning the servo motor to message position

    delay(10000); // wait for 10 seconds before ending the current ordering session
    
    ServoHealth.write(160); // turn the servo motor to the initial position

    screenPage = "Start"; // reset the program
    whichButtonClicked = "None"; // reset the last presssed button to None
  }

  if (screenPage == "CheckoutCheck") { // if Checkout confirmation page should be displayed
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(3, 1); // on first line starting with the 4th character
    lcd.print("Are you sure?"); // write
    lcd.setCursor(0, 3); // on fourth line starting with the 1st character
    lcd.print("Go back"); // write
    lcd.setCursor(13, 3); // on fourth line starting with the 14th character
    lcd.print("Confirm"); // write

    ServoMeat.write(100); // start turning the servo motor
    delay(350); // wait for 1.25 second
    ServoMeat.write(95); // stop the rotation of the servo motor

    delay(500); // wait 200 miliseconds so the system has the chance to notice button press
    whichButtonClicked = whichButton(); // check which button was pressed (including none)

    while (whichButtonClicked == "None" || whichButtonClicked == "middle") {// run until the left or right button is pressed
      whichButtonClicked = whichButton(); // check which button was pressed (including none)
    }
    
    if (whichButtonClicked == "left") { // if the left button was pressed
      screenPage = "MenuFirst"; // set the next page to be displayed to the first menu option
      ServoMeat.write(88); // start turning the servo motor backwards
      delay(400); // wait for 1.25 second
      ServoMeat.write(95); // stop the rotation of the servo motor
    }

    if (whichButtonClicked == "right") { // if the right button was pressed
      screenPage = "Checkout Meat"; // set the next page to be displayed to Checkout page
    }
  }

  if (screenPage == "Checkout Meat") { // if Checkout page after buying meat should be displayed
    lcd.clear(); // clear the previous content of the LCD screen
    lcd.setCursor(2, 1); // on first line starting with the 3th character
    lcd.print("Order successful"); // write

    ServoMeat.write(88); // start turning the servo motor backwards
    delay(400); // wait for 400 miliseconds
    ServoMeat.write(95); // stop the rotation of the servo motor

    delay(10000); // wait for 10 seconds before ending the current ordering session

    screenPage = "Start"; // reset the program
    whichButtonClicked = "None"; // reset the last presssed button to None
  }
}
