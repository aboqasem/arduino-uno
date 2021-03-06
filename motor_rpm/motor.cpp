//
// Created by Mohammad Al Zouabi on 20/09/2020.
//
#include "motor.hpp"

volatile uint8_t interruptsCount = 0;

/**
 * Attaches motor to interrupt pin
 * @param pin
 */
void attachMotor(const uint8_t &pin) {
  // attach interrupt to increment interrupts_count on RISING signal on pin
  attachInterrupt(digitalPinToInterrupt(pin), []() { ++interruptsCount; }, RISING);
}

/**
 * Detaches motor from interrupt pin
 * @param pin
 */
void detachMotor(const uint8_t &pin) {
  detachInterrupt(pin);
}

/**
 * Calculates and returns the motor rounds per minute by counting
 * RISING edge for one second then converting it to RPM
 * @param pin
 * @return motor rounds per minute
 */
uint16_t getMotorRpm() {
  // time to start counting received interrupts
  volatile uint32_t startTime = millis();
  // reset number of interrupts
  interruptsCount = 0;
  // count received interrupts for one second
  while (millis() - startTime < 1000);
  // the motor rounds per minute =
  // interrupts / 2 (pulses per revolution) * 60 (seconds)
  return interruptsCount / 2 * 60;
}
