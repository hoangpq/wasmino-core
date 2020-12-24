/*
	HardwareSerial.cpp - Hardware serial library for Wiring
	Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
	
	Modified 23 November 2006 by David A. Mellis
	Modified 28 September 2010 by Mark Sproul
	Modified 14 August 2012 by Alarus
	Modified 3 December 2013 by Matthijs Kooijman
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

#include "HardwareSerial.h"

static ssize_t _write(int fd, const void *buf, size_t count) {
	return write(fd, buf, count);
}

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(unsigned long baud, byte config)
{
}

void HardwareSerial::end()
{
}

int HardwareSerial::available(void)
{
	return rxBufferSize - rxBufferCursor;
}

int HardwareSerial::peek(void)
{
	if (rxBufferCursor == rxBufferSize) {
		return -1;
	}
	return rxBuffer[rxBufferCursor];
}

int HardwareSerial::read(void)
{
	if (rxBufferCursor == rxBufferSize) {
		return -1;
	}
	return rxBuffer[rxBufferCursor++];
}

int HardwareSerial::availableForWrite(void)
{
	return SERIAL_TX_BUFFER_SIZE - txBufferCursor;
}

void HardwareSerial::flush()
{
	// flush to stdout.
	_write(1, txBuffer, SERIAL_TX_BUFFER_SIZE - txBufferCursor);
	txBufferCursor = 0;
}

size_t HardwareSerial::write(uint8_t c)
{
	if (txBufferCursor == SERIAL_TX_BUFFER_SIZE || txBuffer[txBufferCursor] == '\n') {
		flush();
	}
	txBuffer[txBufferCursor++] = c;
	return 1;
}
