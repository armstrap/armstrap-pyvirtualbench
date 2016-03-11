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

from pyvirtualbench import PyVirtualBench, PyVirtualBenchException

# This examples demonstrates how to generate and read static digital signals
# using the Digital (Dig) lines on a VirtualBench.

try:
    # You will probably need to replace "myVirtualBench" with the name of your device.
    # By default, the device name is the model number and serial number separated by a hyphen; e.g., "VB8012-309738A".
    # You can see the device's name in the VirtualBench Application under File->About
    channels_to_write = "myVirtualBench/dig/0:3"
    channels_to_read ="myVirtualBench/dig/4:7"

    data_to_write = [True, False, True, True]

    virtualbench = PyVirtualBench()
    dio = virtualbench.acquire_digital_input_output(channels_to_write);

    for i in range(10):
        dio.write(channels_to_write, data_to_write)
        print("[%d] Wrote to  %s: %s" % (i, channels_to_write, data_to_write))
        print("[%d] Read from %s: %s" % (i, channels_to_read, dio.read(channels_to_read)))

    dio.release()
except PyVirtualBenchException as e:
    print("Error/Warning %d occurred\n%s" % (e.status, e))
finally:
    virtualbench.release()
