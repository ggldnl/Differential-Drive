# Differential Drive

## ⚠️ Work in Progress

This is a personal learning project and is not actively maintained beyond my own educational use. I might add small updates or improvements over time, but the main goal was to experiment and document results.

I'm not putting much effort into designing a clean 3D model for the chassis either. I uploaded the STL files and a basic layout, but the focus of the project is on control software and experimentation, not mechanical design.

## 🤖 Introduction

I created this simple differential drive platform to help me explore foundational concepts in mobile robotics, control, and especially the PID algorithm.

The goal of the project was to build a robot that is capable of maintaining the issued velocity on both wheels using a PID controller. No actuator is the same in reality and moving in a straight line in an open loop is impossible. After a short transient phase (dependent on how well the PID parameters are tuned) the robot is able to follow desired velocity commands with good precision.

## 🤝 Contribution

This is primarily a personal learning project, so I don’t expect or actively encourage contributions. However, if you’re curious or working on something similar, feel free to open an issue or get in touch.

## References

voltage divider: https://en.wikipedia.org/wiki/Voltage_divider
UART setup on bookworm: https://www.abelectronics.co.uk/kb/article/1035/serial-port-setup-in-raspberry-pi-os
UART communication: https://shepherdingelectrons.blogspot.com/2019/06/serial-uart-gpio-on-raspberry-pi-zero.html
shift register: https://dronebotworkshop.com/shift-registers/
RPI pinout: https://pinout.xyz/
