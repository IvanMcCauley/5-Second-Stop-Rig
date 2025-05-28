# 🛑 5 Second Stop Rig – Reaction Timer Project

A precision-based embedded system built using Arduino to challenge users to stop a timer at **exactly 5.00 seconds**. Designed as part of my final year Mechatronics Engineering project, this rig blends real-time feedback, control logic, and human interaction.

## 🔧 Features

- 0.01s resolution reaction timer
- Real-time LCD feedback
- LED + buzzer indicators on success/failure
- Resettable with push-button interface
- Fully self-contained 3D-printed rig

## ⚙️ Technologies Used

- **Microcontroller**: Arduino Uno
- **Language**: Embedded C++ (Arduino IDE)
- **Components**: LCD, push button, buzzer, LED, resistors, 3D-printed enclosure
- **Software**: Arduino IDE, SolidWorks (design), TinkerCad (circuit)

## 🖼️ Photos

*(Upload these in a folder called `/images` and update the paths)*

![Final Build](images/device_photo.jpg)
![Circuit Diagram](images/circuit_diagram.jpg)

## 🧠 How It Works

1. Press the start button to begin the timer.
2. The system displays time in real-time.
3. User tries to stop it at **exactly 5.00 seconds**.
4. Success/failure is indicated via LED and buzzer logic.
5. Device resets for repeated use.

This was designed to challenge precision reaction timing, with exacting tolerances to test embedded logic and hardware integration.

## 📂 Files

- `5SecondStop.ino` – main Arduino code (logic + control)
- `images/` – photos, circuit diagrams
- `FYP_summary.pdf` – optional summary sheet of project overview

## 📘 What I Learned

- Real-time embedded programming
- Signal debouncing and input handling
- LCD interfacing and timing precision
- Hardware-software design + debugging

## 👨‍💻 Built By

Ivan McCauley — Mechatronics Engineering Graduate  
[LinkedIn](https://www.linkedin.com/in/ivan-mccauley-82b17a177)

