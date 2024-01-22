/**
 * @file Packet.cpp
 * @author NightStar
 * @brief Packet library
 * @version 0.1
 * @date 2024-01-22
 *
 * @copyright Copyright (c) 2024 NightSky Studio
 * @license MIT License (MIT)
 */
#include "packet.h"

/**
 * @brief Construct a new Packet:: Packet object
 *
 * @param Stream      Object to stram (Serial, SoftwareSerial, ...)
 * @param size        Data size (default 10)
 * @param starter     Packet starter (default 0x0A)
 * @param terminator  Packet terminator (default 0x0B)
 * @param emptydata   Packet empty data (default 0x00)
 * @param timeout     Stream timeout (default 1000)
 */
Packet::Packet(Stream &Stream, uint8_t size,
               uint8_t starter, uint8_t terminator, uint8_t emptydata,
               uint16_t timeout) : isData(false), length(0),
                                   _Stream(&Stream), _starter(starter), _terminator(terminator), _emptydata(emptydata),
                                   _datalength(size + 1)
{
    _Stream->setTimeout(timeout);
    delete[] data;
    data = new uint8_t[size + 1];
    datainit();
}

/**
 * @brief Set the packet starter
 *
 * @param starter Starter symbol
 */
void Packet::setstarter(uint8_t starter)
{
    _starter = starter;
}
/**
 * @brief Set the packet terminator
 *
 * @param terminator Terminator symbol
 */
void Packet::setterminator(uint8_t terminator)
{
    _terminator = terminator;
}
/**
 * @brief Set the packet starter and terminator
 *
 * @param starter Starter symbol
 * @param terminator Terminator symbol
 */
void Packet::setting(uint8_t starter, uint8_t terminator)
{
    _starter = starter;
    _terminator = terminator;
}

/**
 * @brief Data initialization (clear data)
 */
void Packet::datainit()
{
    for (uint8_t i = 0; i < _datalength; i++)
        data[i] = _emptydata;
}

/**
 * @brief Packet read
 */
bool Packet::read()
{
    if (!_Stream->available())
        return false;

    if (_Stream->peek() != _starter)
    {
        // clear the buffer
        while (_Stream->available())
            _Stream->read();
        return false;
    }

    _Stream->read(); // consume the _starter
    datainit();      // clear the read buffer
    _Stream->readBytesUntil(_terminator, data, _datalength);
    length = findlength();

    if (length == _datalength && data[length] != _terminator)
        return false;

    isData = true;
    return true;
}

/**
 * @brief Packet write
 *
 * @param data Write data
 * @param length Data length
 */
void Packet::write(uint8_t *data, uint8_t length)
{
    uint8_t buffer[length + 3];
    buffer[0] = _starter;
    buffer[1] = length;
    buffer[length + 2] = _terminator;
    for (uint8_t i = 0; i < length; i++)
        buffer[i + 2] = data[i];

    _Stream->write(buffer, length + 3);
}

/**
 * @brief Find data length
 *
 * @return uint8_t Data length
 */
uint8_t Packet::findlength()
{
    for (uint8_t i = 0; i < _datalength - 1; i++)
    {
        if (data[i] == _emptydata || data[i] == _terminator)
        {
            length = i;
            return length;
        }
    }
    return _datalength - 1;
}

/**
 * @brief Output log
 *
 * @param str Stream
 * @param clear Clear data availability (default true)
 * @param isHex HEX Show (default false)
 */
void Packet::outlog(Stream &str, bool clear, bool isHex)
{
    Stream *target = &str;
    target->println(F("Discover available data"));

    target->print(F("Data: "));
    for (uint8_t i = 0; i < length; i++)
    {
        if (isHex)
            target->print(data[i], HEX);
        else
            target->print(data[i]);
        target->print(F(" "));
    }
    target->println();

    target->print(F("Length: "));
    target->println(length);

    if (clear)
        isData = false;
}
