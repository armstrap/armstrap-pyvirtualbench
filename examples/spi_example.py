#! /usr/bin/env python3

# The MIT License (MIT)
#
# Copyright (c) 2015 Charles Armstrap <charles@armstrap.org>
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

from pyvirtualbench import PyVirtualBench, PyVirtualBenchException, Polarity, ClockPhase

# This examples demonstrates how to master a SPI bus using the Digital lines
# on a VirtualBench.

try:
    # Channel Configuration
    bus = "myVirtualBench/spi/0"
    clock_rate = 10000000.0 # 10MHz
    clock_polarity = Polarity.IDLE_LOW
    clock_phase = ClockPhase.FIRST_EDGE
    chip_select_polarity = Polarity.IDLE_HIGH

    # Data
    data_to_write = [ 0, 1, 2, 3, 4, 5, 6, 7 ]
    data_read_size = len(data_to_write)
    bytes_per_frame = -1

    virtualbench = PyVirtualBench()
    spi = virtualbench.acquire_serial_peripheral_interface(bus)

    spi.configure_bus(clock_rate, clock_polarity, clock_phase, chip_select_polarity)

    # Write and read from the bus.
    for i in range(10):
        data_read = spi.write_read(data_to_write, bytes_per_frame, data_read_size)

        print("Iteration %d:" % i)
        print("Wrote: %s" % data_to_write)
        print("Read: %s" % data_read)

    spi.release()
except PyVirtualBenchException as e:
    print("Error/Warning %d occurred\n%s" % (e.status, e))
finally:
    virtualbench.release()
