#include <Wire.h>
#include <LiquidCrystal.h>

// this is the object used to interact with the lcd screen
LiquidCrystal lcd(5, 18, 19, 16, 17, 21);

// define the gpios for parking sensors
#define parking_1_sensor 23
#define parking_2_sensor 22
#define parking_3_sensor 14
#define parking_4_sensor 32
#define parking_5_sensor 15

// this is the total spots that are in the parking lot
const int total_spots_in_parking = 5;

// each spot will correspond to a sensor
// if the parking spot is occupied , spot# = 1
// if the parking spot is empty, spot# = 0
int spot1 = 0; 
int spot2 = 0; 
int spot3 = 0; 
int spot4 = 0; 
int spot5 = 0; 

// this variable represent how many spots are full
int total_full_spots = spot1 + spot2 + spot3 + spot4 + spot5;

// this variable represent how many spots are empty
int total_empty_spots = total_spots_in_parking - total_full_spots;
 
void setup() {
  Serial.begin(9600);
  // Initialize the GPIO pins to be inputs
  pinMode(parking_1_sensor, INPUT);
  pinMode(parking_2_sensor, INPUT);
  pinMode(parking_3_sensor, INPUT);
  pinMode(parking_4_sensor, INPUT);
  pinMode(parking_5_sensor, INPUT);
 
  // initialize screen and intro here
  lcd.begin(16,2);
  // print quick setup message
  lcd.setCursor(5, 0);
  lcd.print("WELCOME");
  delay(2000);
  lcd.setCursor(1, 1);
  lcd.print("Parking Counter");
  delay(3000);
  lcd.clear();
}
 
void loop() {
  // read all the sensor and update global vars
  read_sensors_and_update_values();
  // update the lcd screen with the new values
  update_lcd_screen();
  // do a small delay between each set - not needed 
  // we do not want things to break. "safety"
  delay(50);

}
 
void read_sensors_and_update_values() {
  // a million ways to do this
  // i think this might be the easiest

  // go ahead set all the values to be 0 
  // and then we will scan each sensor again
  spot1 = 0;
  spot2 = 0;
  spot3 = 0;
  spot4 = 0;
  spot5 = 0;
 
  // read all sensors 
  if (digitalRead(parking_1_sensor) == 0) 
  {
    spot1 = 1;
  }
  if (digitalRead(parking_2_sensor) == 0) 
  {
    spot2 = 1;
  }
  if (digitalRead(parking_3_sensor) == 0) 
  {
    spot3 = 1;
  }
  if (digitalRead(parking_4_sensor) == 0) 
  {
    spot4 = 1;
  }
  if (digitalRead(parking_5_sensor) == 0) 
  {
    spot5 = 1;
  }

  //update the total values
  total_full_spots = spot1 + spot2 + spot3 + spot4 + spot5;
  total_empty_spots = total_spots_in_parking - total_full_spots;

}

void update_lcd_screen() {
  // update lcd screen here.
  //clear screen 
  lcd.clear();
  //set the cursor in the top left corner
  lcd.setCursor(0,0);
  //print the following to show everything 
  lcd.print("Empty parking: ");
  lcd.print(total_empty_spots);

  // set the cursor in the bottom left corner
  lcd.setCursor(0,1);
  //print the following
  lcd.print("full parking: ");
  lcd.print(total_full_spots);

}

