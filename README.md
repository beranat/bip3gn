# Beeper Engine (bip3gn)

This project generates simple sound synthesis using two independent pulse wave channels.

## Features

- Two independent pulse wave channels
- Supports basic note frequency table
- Compact design for small firmware footprint

## How It Works

The engine uses software-generated pulse waves (short impulses) to simulate simple audio tones. Each of the two voices can play a different note simultaneously by toggling speaker GPIO pins.

## Hardware Requirements

- Speaker or piezo buzzer
- STM32G030x microcontroller

## Quick Start

### Requirements

* GNU GCC for cross-compilation for arm-none-eabi target (15.1.0)
* Make (4.4.1)
* Newlib (4.5.0.20241231)
* OpenOCD (0.12.0)
* Eclipse IDE for C/C++ (2024-12 4.34.0)

### Installation

* make build
* make flash

## License

GNU GENERAL PUBLIC LICENSE Version 3. See LICENSE file for details.

