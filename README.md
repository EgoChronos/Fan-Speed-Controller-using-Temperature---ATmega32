# Fan Speed Controller Using Temperature – ATmega32 🌡️
👋 Hello, everyone!

This repository contains a mini project developed as part of my Embedded Software Basics Diploma at EDGES for Training.

📝 Project Summary
This project implements an automatic fan speed controller using the ATmega32 microcontroller. The fan’s speed changes dynamically based on the surrounding temperature, with speed adjustments occurring every 30°C increment.

🎯 The goal was to integrate analog sensor data with motor control using core embedded systems concepts.

🧰 Technologies & Components Used
Component/Feature	Description
🧠 MCU	ATmega32 Microcontroller
🌡️ Sensor	LM35 Temperature Sensor
🔁 Output	DC Motor (Fan) controlled via PWM
📺 Display	LCD to show current temperature & fan state
💡 Peripherals	GPIO, ADC, PWM, LCD Interface

⚙️ How It Works
🌡️ The LM35 sensor reads the ambient temperature.

🔁 The ADC (Analog-to-Digital Converter) on ATmega32 processes the sensor data.

⚙️ The PWM signal controls the DC fan speed.

📈 Fan speed is adjusted in steps:

OFF below 30°C

Low Speed at 30°C

Medium Speed at 60°C

High Speed at 90°C and above

📺 The current temperature and fan status are shown on an LCD display.

📄 Project Documentation
📎 Please refer to the attached file for full project requirements and specifications.

✅ Project Status
🎉 Completed
The system is fully functional and tested on hardware according to the project scope.
