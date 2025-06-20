# Projector-Automation
![My ESP with a big external button connected to GPIO0](https://github.com/user-attachments/assets/45d617b1-e624-4fb8-814d-af0f7ae95614)
My ESP with a big external button connected to GPIO0

ZTE-S-Pro projector is annying to turn off and off, so I decided to make a BLE mouse that works by doing the following:

### Turning the Project on
- Unlocks the lock screen (If applicable)
- Centers the cursor to the point where the projector ON button is (no matter where the cursor is, it still works)
- Clicks
- Moves away

### Turning the projector Off
- Does the same steps as turning on


You need an ESP32 and Arduino IDE t program it. On and Off are toggled by the BOOT button (GPIO 0)

Press the button once to toggle and wait until the blue LED on the ESP flashes 4 times to see the projector turn on.
