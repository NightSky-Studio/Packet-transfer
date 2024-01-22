/**
 * @file WriteData.cpp
 * @author NightStar
 * @brief Example of using the Packet library
 *        This example shows how to use the Packet library
 *        to write data to the stream
 * @version 0.1
 * @date 2024-01-22
 *
 * @copyright Copyright (c) 2024 NightSky Studio
 * @license MIT License (MIT)
 *
 */
#include <Arduino.h>

#include "Packet.h"
Packet packet(Serial, 5, 0xFA, 0xFB, 0x00, 200);

uint8_t *data = new uint8_t[5]{0x48, 0x65, 0x6C, 0x6C, 0x6F}; // Data

void setup()
{
    Serial.begin(9600); // Serial initialization
}

void loop()
{
    packet.write(data, 5); // Write data to stream
    delay(1000);
}