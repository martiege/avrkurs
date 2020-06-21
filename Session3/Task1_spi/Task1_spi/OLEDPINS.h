#pragma once

// PD1 -> AN2 -> OLEDPIN3 
#define AN2PIN   1
#define AN2PORT  PORTD
#define AN2CTRL  PIN1CTRL
#define OLEDPIN3PIN  AN2PIN
#define OLEDPIN3PORT AN2PORT
#define OLEDPIN3CTRL AN2CTRL

// PD2 -> AN3 -> OLEDPIN4
#define AN3PIN   2 
#define AN3PORT  PORTD
#define AN3CTRL  PIN2CTRL
#define OLEDPIN4PIN  AN3PIN
#define OLEDPIN4PORT AN3PORT
#define OLEDPIN4CTRL AN3CTRL 

// PC3 -> RST2 -> OLEDPIN5
#define RST2PIN  3
#define RST2PORT PORTC
#define RST2CTRL PIN3CTRL
#define OLEDPIN5PIN  RST2PIN
#define OLEDPIN5PORT RST2PORT
#define OLEDPIN5CTRL RST2CTRL

// PC6 -> RST3 -> OLEDPIN6
#define RST3PIN  5
#define RST3PORT PORTC
#define RST3CTRL PIN5CTRL
#define OLEDPIN6PIN  RST3PIN
#define OLEDPIN6PORT RST3PORT
#define OLEDPIN6CTRL RST3CTRL

// PD4 -> PWM2 -> OLEDPIN7
#define PWM2PIN  4
#define PWM2PORT PORTD
#define PWM2CTRL PIN4CTRL
#define OLEDPIN7PIN  PWM2PIN
#define OLEDPIN7PORT PWM2PORT
#define OLEDPIN7CTRL PWM2CTRL

// PD5 -> PWM3 -> OLEDPIN8
#define PWM3PIN  5
#define PWM3PORT PORTD 
#define PWM3CTRL PIN5CTRL
#define OLEDPIN8PIN  PWM3PIN
#define OLEDPIN8PORT PWM3PORT
#define OLEDPIN8CTRL PWM3CTRL

// PC2 -> INT2 -> OLEDPIN9
#define INT2PIN  2
#define INT2PORT PORTC
#define INT2CTRL PIN2CTRL
#define OLEDPIN9PIN  INT2PIN
#define OLEDPIN9PORT INT2PORT
#define OLEDPIN9CTRL INT2CTRL

// PC6 -> CS2 -> OLEDPIN15 
#define CS2PIN  6 
#define CS2PORT PORTC 
#define CS2CTRL PIN6CTRL
#define OLEDPIN15PIN  CS2PIN
#define OLEDPIN15PORT CS2PORT
#define OLEDPIN15CTRL CS2CTRL

// PA4 -> MOSI -> OLEDPIN16
#define MOSIPIN  4
#define MOSIPORT PORTA
#define MOSICTRL PIN4CTRL
#define OLEDPIN16PIN  MOSIPIN
#define OLEDPIN16PORT MOSIPORT
#define OLEDPIN16CTRL MOSICTRL

// PA6 -> SCK -> OLEDPIN18
#define SCKPIN  6
#define SCKPORT PORTA
#define SCKCTRL PIN6CTRL
#define OLEDPIN18PIN  SCKPIN
#define OLEDPIN18PORT SCKPORT
#define OLEDPIN18CTRL SCKCTRL