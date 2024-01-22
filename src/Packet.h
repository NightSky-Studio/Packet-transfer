/**
 * @file Packet.h
 * @author NightStar
 * @brief Packet library
 * @note This library provides a straightforward method for working with data packets.
 *       The packet format is simple [starter][length][data][terminator].
 *       and allows for reading and writing data to the stream.
 *       It also offers a straightforward method for working with data.
 * @version 0.1
 * @date 2024-01-22
 *
 * @copyright Copyright (c) 2024 NightSky Studio
 * @license MIT License (MIT)
 *
 */
#ifndef _PACKET_H_
#define _PACKET_H_
#include <Arduino.h>

class Packet
{
public:
    Packet(Stream &Stream, uint8_t size = 10, uint8_t starter = 0x0A, uint8_t terminator = 0x0B, uint8_t emptydata = 0x00, uint16_t timeout = 1000);

    void setstarter(uint8_t starter);
    void setterminator(uint8_t terminator);
    void setting(uint8_t starter, uint8_t terminator);

    bool read();
    void write(uint8_t *data, uint8_t length);

    void outlog(Stream &str, bool clear = true, bool ishex = false);

    uint8_t findlength();
    uint8_t *data;  // Data
    bool isData;    // Data Availability
    uint8_t length; // Data length

private:
    Stream *_Stream;      // Stream
    uint8_t _starter;     // Packet starter
    uint8_t _terminator;  // Packet terminator
    uint8_t _emptydata;   // Packet empty data
    uint16_t _datalength; // Data length

    void datainit();
};

#endif // _PACKET_H_
