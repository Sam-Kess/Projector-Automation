/**
 * ESP32 BLE‑Mouse – single/​double/​triple click demo
 * requires the T‑vK “ESP32‑BLE‑Mouse” library.
 */
#include <BleMouse.h>

BleMouse bleMouse;

#define CLICK     digitalRead(0) == LOW
#define DE_BOUNCE digitalWrite(2, HIGH);delay(80);digitalWrite(2, LOW);delay(580);
#define _DE_BOUNCE delay(200);
#define FLASH digitalWrite(2, HIGH);delay(40);digitalWrite(2, LOW);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  pinMode(0, INPUT_PULLUP);      // GPIO0 with the BOOT button
  pinMode(2, OUTPUT);            // on‑board LED

  bleMouse.begin();
}

void flash_led(int pin, int times , int ms_delta) {
  while (times > 0) {
    digitalWrite(pin, HIGH);
    delay(ms_delta);
    digitalWrite(pin, LOW);
    delay(ms_delta);
    times -=1;
  }
}

void loop() {

  int click_count = 0;

  // Detect the number of clicks
  if (CLICK) { // First
    DE_BOUNCE;
    if (!bleMouse.isConnected()) {
      Serial.println("No host detected!!");
      delay(200);
      return;
    }
    click_count++;

    while (1) {
      if (CLICK) {
        DE_BOUNCE;
        click_count++;
      }
      else break;
    }

  }
  /* ---------- action ---------- */
  switch (click_count) {
    case 1:
      // tap to awaken screen, tap to unlock, center the mouse at the projector button, and finally click
      hold(1100);
      FLASH;
      hold(1200);
      FLASH;
      move_mouse_into_place_from_wherever();
      FLASH;
      click();
      FLASH;
      move_left();
      break;
      
    case 2:
      // After it's turned on and the curson is in position, you can click again to turn it off
      click();
      break;

    case 3:
      Serial.println("Centering Cursor...");
      move_mouse_into_place_from_wherever();           // your own function here
      break;

    case 4:
      Serial.println("Unlocking Screen...");
      hold(1200);
      break;





    default:
      break;
    
  }
}



/* ---------- helpers ---------- */


void hold(int mil_secs) {
  bleMouse.press(MOUSE_LEFT);
  delay(mil_secs);
  bleMouse.release(MOUSE_LEFT);
  delay(500);
}

void click() {
  Serial.println("Left Click!!");
  bleMouse.click(MOUSE_LEFT);
  delay(500);
}


void move_left() {
    Serial.println("Move mouse pointer left");
    int startTime = millis();
    while( millis() < startTime+1000 ) {
      bleMouse.move(-80,0);
      delay(50);
    }
}


void move_mouse_into_place_from_wherever() {
      unsigned long startTime;

      Serial.println("Move mouse pointer up");
      startTime = millis();
      while(millis()<startTime+400) {
        bleMouse.move(0,-80);
        delay(50);
      }
    delay(100);

    Serial.println("Move mouse pointer left");
    startTime = millis();
    while( millis() < startTime+1000 ) {
      bleMouse.move(-80,0);
      delay(50);
    }

    Serial.println("Move mouse pointer down");
    startTime = millis();
    while(millis()<startTime+200) {
      bleMouse.move(0,80);
      delay(50);
    }
    delay(500);

    Serial.println("Move mouse pointer right");
    startTime = millis();
    while(millis()<startTime+200) {
      bleMouse.move(80,0);
      delay(100);
    }


    delay(500);

}