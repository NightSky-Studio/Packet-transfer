/**
 * @file ReadData.cpp
 * @author NightStar
 * @brief Example of using the Packet library
 *        This example shows how to use the Packet library
 *        to read data from the stream and print it to the Serial
 * @version 0.1
 * @date 2024-01-22
 *
 * @copyright Copyright (c) 2024 NightSky Studio
 * @license MIT License (MIT)
 *
 */
#include <Arduino.h>

#include "Packet.h"
Packet packet(Serial, 10, 0xFA, 0xFB, 0x00, 200);

void setup()
{
    Serial.begin(9600); // Serial initialization
}

void loop()
{
    packet.read();     // Read data from stream
    if (packet.isData) // If data is available
    {
        packet.outlog(Serial, true, true); // Print data to Serial
    }
}
