#! /usr/bin/env python3

# The MIT License (MIT)
#
# Copyright (c) 2016 Charles Armstrap <charles@armstrap.org>
# If you like this library, consider donating to: http://bit.ly/pyvirtualbench
# Anything helps.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

from pyvirtualbench import PyVirtualBench, PyVirtualBenchException, I2cClockRate, I2cAddressSize

# This examples demonstrates how to master an I2C bus using the Digital
# lines on a VirtualBench.

try:
    # You will probably need to replace "myVirtualBench" with the name of your device.
    # By default, the device name is the model number and serial number separated by a hyphen; e.g., "VB8012-309738A".
    # You can see the device's name in the VirtualBench Application under File->About
    bus = "myVirtualBench/i2c/0"

    # For I2C wiring:
    # SCL (Serial Clock) output maps to Digital I/O Pin 6 on VirtualBench device
    # SDA (Serial Data) input/output maps to Digital I/O Pin 7 on VirtualBench device

    # Channel Configuration
    clock_rate = I2cClockRate.ONE_HUNDRED_KHZ # 100kHz

    # You will probably need to replace "0x50" address with the address for your
    # attached chip.  You can find the address by looking at the datasheet for
    # your attached chip.
    address = 0x50
    address_size = I2cAddressSize.SEVEN_BITS
    enable_pullups = True

    data_read_size = 256
    timeout = 5.0

    virtualbench = PyVirtualBench()
    i2c = virtualbench.acquire_inter_integrated_circuit(bus)
    i2c.configure_bus(clock_rate, address, address_size, enable_pullups)

    data_read = i2c.read(timeout, data_read_size)

    # Dump data that we just read
    print("Read %d bytes from address 0x%02x:" % (len(data_read), address))
    for i in range(len(data_read)):
        print("%d (0x%02x) = %d (0x%02x)" % (i, i, data_read[i], data_read[i]))

    i2c.release()
except PyVirtualBenchException as e:
    print("Error/Warning %d occurred\n%s" % (e.status, e))
finally:
    virtualbench.release()
