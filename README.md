
Arduino-based smart pothole detection and driver warning system using an HC-SR04 ultrasonic sensor and MPU6050.

Smart Pothole and Warning System Detection
An Arduino-based embedded system designed to detect road surface irregularities and provide real-time warnings to drivers.

📌 About the Project
Road potholes can cause vehicle damage and contribute to road accidents, especially when they are difficult to see at night or during bad weather.

The Smart Pothole and Warning System Detection uses an HC-SR04 ultrasonic sensor to measure changes in road surface distance and an MPU6050 sensor to detect sudden tilts or vibrations.

Sensor readings are processed by an Arduino Uno. When a possible pothole or dangerous road condition is detected, the system provides warnings through an LCD display, LED indicator, and buzzer.

🎯 Objectives
The project aims to develop an affordable pothole detection and warning system capable of monitoring road conditions in real time.

The system is designed to:

Detect changes in road surface distance using an HC-SR04 sensor.
Detect sudden movement or vibration using an MPU6050.
Process sensor information using an Arduino Uno.
Display the current road condition on a 16x2 LCD.
Activate a warning LED and buzzer when a pothole is detected.
Display a safe indicator when normal road conditions are detected.
Continuously monitor road conditions.

🧰 Hardware

Arduino Uno
HC-SR04 Ultrasonic Sensor
MPU6050 Gyroscope/Accelerometer
16x2 LCD Display
Active Piezo Buzzer
LED indicators
220Ω resistors
Breadboard
Jumper wires
USB cable / power supply

💻 Software
Arduino IDE
Arduino Serial Monitor
LiquidCrystal / LiquidCrystal_I2C
MPU6050-compatible Arduino library

⚙️ How It Works
The HC-SR04 continuously measures the distance between the system and the road surface.
The MPU6050 monitors movement, vibration, and changes in orientation.
The Arduino processes the sensor readings.
Normal readings indicate a safe road condition.
Abnormal readings trigger the warning system.
The LCD displays the road condition while the LED and buzzer warn the driver.

🔌 Block Diagram
Block Diagram

🔧 Circuit / Schematic Diagram
Schematic Diagram

📷 Prototype
Project development and testing photographs are available in the images folder.

🚀 Future Improvements
Future versions of the project may include:

GPS pothole location logging
ESP32 Wi-Fi connectivity
GSM communication
Cloud/database integration
Mobile application
SD card data logging
Camera-based pothole recognition
Improved sensor calibration and filtering

👥 Project Members
Mary Kimberly A. Aumentado
Gabriel Ian Fernandez
Camille D. Tesorero
Abeizer Benmarc Viejo

🎓 Academic Project
Developed as part of the Embedded Systems course.
Computer Engineering Students

Academic Year 2025–2026
