# Fingerprint Recognition (Arduino Nano + Fingerprint Sensor)

This project is a simple **fingerprint recognition system** built with an **Arduino Nano** and a fingerprint sensor.  
It reads a fingerprint, searches for a match in the sensor’s stored templates, and returns whether the fingerprint is **recognized (authorized)** or **not recognized**.

---

## Features

- Capture fingerprint image from the sensor
- Convert the image to fingerprint template
- Fast search for a match in the sensor memory
- Returns a fingerprint ID when a match is found
- Serial output for debugging / monitoring

---

## Hardware Used

- Arduino Nano
- Fingerprint sensor module (commonly R305 / AS608 / similar)
- Jumper wires
- Breadboard (optional)
- 5V power (USB or external)

---

## Wiring (Typical)

> Exact pins may differ depending on your code and module.  
> Common wiring for Arduino Nano:

- Fingerprint **VCC** → **5V**
- Fingerprint **GND** → **GND**
- Fingerprint **TX** → Arduino **RX** (SoftwareSerial RX pin used in code)
- Fingerprint **RX** → Arduino **TX** (SoftwareSerial TX pin used in code)

⚠️ Some sensors work better with **3.3V logic** on RX. If your sensor is unstable, use a voltage divider on the sensor RX line.

---

## Libraries

This project uses the Adafruit fingerprint library:

- **Adafruit Fingerprint Sensor Library**
- **SoftwareSerial** (or HardwareSerial depending on your setup)

Install from Arduino IDE:
1. **Sketch → Include Library → Manage Libraries**
2. Search: **“Adafruit Fingerprint Sensor Library”**
3. Install

---

## How It Works (Logic)

1. The sensor tries to **read a fingerprint image**
2. Converts the image to a **template**
3. Searches the sensor database for a match
4. If a match is found:
   - returns **Fingerprint ID**
5. If no match is found:
   - returns **not recognized**

---

## How to Run

1. Open the `.ino` file in Arduino IDE
2. Select board:
   - **Tools → Board → Arduino Nano**
3. Select processor (if needed):
   - **Tools → Processor → ATmega328P (Old Bootloader)** (only if upload fails)
4. Select port:
   - **Tools → Port**
5. Upload the code
6. Open Serial Monitor:
   - **Tools → Serial Monitor**
7. Place a finger on the sensor and watch the output

---

## Enrolling Fingerprints (Important)

This project assumes fingerprints are already stored in the sensor memory.  
To enroll new fingerprints, use an enrollment sketch (example: `Enroll` from the Adafruit library examples) to add fingerprint templates to the sensor.

---


